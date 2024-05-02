#ifndef MANAGE_H_
#define MANAGE_H_
#include <queue>
#include <curl/curl.h>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>
#include "sqlite.h"
#include "rabbitmq_handle.h"
#include "component-all.hpp"
#include "log.h" // new zjx9083

class Semaphore_ {
public:
    Semaphore_(int permits) : permits_(permits) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (permits_ == 0) {
            cv_.wait(lock);
        }
        --permits_;
    }

    bool try_acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (permits_ > 0) {
            --permits_;
            return true;
        }
        return false;
    }

    bool try_acquire_for(std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (permits_ == 0) {
            if (cv_.wait_for(lock, timeout) == std::cv_status::timeout) {
                return false;
            }
        }
        --permits_;
        return true;
    }

    void release() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++permits_;
        cv_.notify_one();
    }

    int available_permits() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return permits_;
    }

private:
    int permits_;
    mutable std::mutex mutex_;
    std::condition_variable cv_;
};

class MessageManage{
public:
    MessageManage(RabbitMQHandler* rabbitmq_, Sqlite* db_, int lengthQueueMax)
        :rabbitmq_(rabbitmq_), db_(db_), sem_(lengthQueueMax), stop(false), state(false){
        SLOGI("create table message");
        // db_->CUD("CREATE TABLE IF NOT EXISTS message (time TIMESTAMP PRIMARY KEY, msg TEXT, res TEXT, success BOOLEAN)"); 
    }
    
    // make thread to loop exe Add()
    void Start(){
        SLOGI("Start get rabbitmq message thread");
        // thread_ = std::make_shared<std::thread>(&MessageManage::RunThread, this);
        try {
             thread_ = std::make_shared<std::thread>(&MessageManage::RunThread, this);
        } catch (const std::exception& e) {
            // 异常处理
            std::cerr << "Exception caught in MessageManage::Start(): " << e.what() << std::endl;
            // 可以选择继续抛出异常或进行其他处理
        }
    }
    
    void RunThread(){
        while(1){
            if(stop) break;
            Add();
        }
    }

    // receive msg Through Semaphore_ management save to queue, then notify to handle msg
    void Add() {
        SLOGD("enter add");
        if(this->state){
            std::string task;
            SLOGD("enter receive message");
            int ret = rabbitmq_->receiveMessage(task);
            //xjf add 2024
            if (ret == -2) {
                stop = true;
            }
            SLOGD("out receive message");
            if(ret == 0 ) {
                SLOGD("enter sem acquire");
                sem_.acquire();
                SLOGD("out sem acquire");
                SLOGD("enter lock mutex");
                std::unique_lock<std::mutex> lock(mutex_);
                queue_.push(task);
                condNonEmpty_.notify_one();
                SLOGI("receive message from remote rabbitmq");
                SLOGD("out lock mutex");
            }
        }
        SLOGD("out add");
        // return ret;
    }

    // 
    void Del(std::string ret) {
        SLOGI("Task Done");
        std::unique_lock<std::mutex> lock(mutex_);
        std::string msg = queue_.front();
        queue_.pop();
        if(rabbitmq_->sendMessage(ret)){
            SLOGI("Success Get MSG:{} ==> Put MSG:{}", msg.c_str(), ret.c_str());
        }
        else{
            SLOGE("fail Get MSG:{} ==> Put MSG:{}", msg.c_str(), ret.c_str());
        }
        sem_.release();
    }

    /**
     * put res to remote rabbitmq, if put success save (msg, res, true) to db, else save (msg, res, false)
     */
    int Put(std::string msg, std::string res){
        // std::string sql = "INSERT INTO message (time, msg, res, success) VALUES (CURRENT_TIMESTAMP,'"+ msg + "','" + res + "',";
        int ret;
        SLOGD("enter send message");
        if(!(ret = rabbitmq_->sendMessage(res))){
        SLOGD("out send message");
            SLOGI("Success Get MSG:{} ==> Put MSG:{}", msg.c_str(), res.c_str());
            // sql += "true)";
        }
        else{
            SLOGE("fail Get MSG:{} ==> Put MSG:{}", msg.c_str(), res.c_str());
            // sql += "false)";
            // ret = -1;
        }
        // std::unique_lock<std::mutex> lock(mutex_2);
        // if(ret = db_->CUD(sql.c_str())){
        //     SLOGE("db_.CUD({}) fail", sql.c_str());
        // }
        // if(ret = db_.show()){
        //     SLOGE("db_.show() fail");
        // }
        return ret;
    }

    // 0 == 无等待直接返回 , 1 == 等待有值为止
    /**
     * get msg from remote rabbitmq
     * pre opt: enable()
     * isWait: Manage both modes
     * (0 : Do not wait for have msg to return msg, no msg returns "", 1 : wait for msg)
     */
    int Get(string & task, int isWait){ 
        if(isWait){
            std::unique_lock<std::mutex> lock(mutex_);
            condNonEmpty_.wait(lock, [this] {return !queue_.empty();});
            task = queue_.front();
            queue_.pop();
            sem_.release();
            return 0;
        }else{
            SLOGD("enter lock mutex");
            std::unique_lock<std::mutex> lock(mutex_);
            if(queue_.empty()){
                return -1;
            }else{
                task = queue_.front();
                queue_.pop();
                sem_.release();
                return 0; 
            }
            SLOGD("out lock mutex");
        }
        return 0;
    }

    void enable(){
        state  = true;
    }

    void disable(){
        state = false;
    }

    void Stop(){
        stop = true;
    }

    std::string getTime(){
        CURL *curl = curl_easy_init();
        if (curl) {
            // 设置要请求的 URL
            curl_easy_setopt(curl, CURLOPT_URL, "http://worldtimeapi.org/api/timezone/Asia/Shanghai");

            // 设置响应数据的回调函数
            std::string response_data;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char *data, size_t size, size_t nmemb, void *userdata) -> size_t {
                std::string *response_data = reinterpret_cast<std::string*>(userdata);
                response_data->append(data, size * nmemb);
                return size * nmemb;
            });
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

            // 发送 HTTP GET 请求并等待响应
            CURLcode res = curl_easy_perform(curl);
            if (res == CURLE_OK) {
                // 解析 JSON 响应并提取时间戳
                json j;
                try {
                    j = json::parse(response_data.c_str());
                } catch (json::parse_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    return "XXXX-XX-XX XX:XX:XX";
                }
                curl_easy_cleanup(curl);
                return  get_json_value<string>(j, "datetime");
            } else {
                curl_easy_cleanup(curl);
                return "XXXX-XX-XX XX:XX:XX";
            }
        }
        return "XXXX-XX-XX XX:XX:XX";
    }

    int queuelen(){
        return queue_.size();
    }

    ~MessageManage(){
        Stop();
        disable();
        std::string msg ;
        while(Get(msg, 0)==0){ //异常结束时，如果队列有数据，将执行保存数据库与发送到信息队列
            std::string res = "ret: -1, msg: "+ msg + ", content: kill to msg loss";
            // Put(msg, res);
            SLOGI("remain message:{}", res.c_str());
        }
        thread_->join();
    }
private:
    Sqlite *db_;
    RabbitMQHandler *rabbitmq_;
    Semaphore_ sem_;
    std::queue<std::string> queue_;
    mutable std::mutex mutex_;
    mutable std::mutex mutex_2;
    std::shared_ptr<std::thread> thread_;
    std::condition_variable condNonEmpty_;
    bool stop;
    bool state;
};


#endif
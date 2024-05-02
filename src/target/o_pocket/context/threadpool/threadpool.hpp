#ifndef GF_THREAD_POOL_HPP 
#define GF_THREAD_POOL_HPP
#include "my-internal.h"
#include "semaphore.hpp"
#include "safe_queue.hpp"
#include "taskinfo.hpp"

#include "log.h"

GF_NAMESPACE_START(main_service)

/**
 *@brief accept in task, and generate taskinfo, and push to unit task list
 */
template<typename T_R>
using ShareTaskInfo = std::shared_ptr<TaskInfo<T_R>>;
template<typename T>
using ShareSafeQueue = std::shared_ptr<SafeQueue<T>>;


/**
 *@brief wrap thread that used by threadpool
 store thread info and threadpool info
 control thread action
 strip and recovery(shutdown)
 need show threadpool info from taskinfo
 TEST LIST:
1、2023/05/31 add change_ method not verify, no test
2、2023/05/30 add task enqueue prioriy, complex testcase not pass
 */
template <typename T>
class Threadpool;
class Worker {
public:
    //only used for threadpool
    template<typename T>
    friend class Threadpool;
    using EachRunEntity = std::function<void()>;
    using ShareThread = std::shared_ptr<std::thread>;
    using StampPoint = std::chrono::time_point<std::chrono::system_clock>;
    
    void launch() {
        std::unique_lock<std::mutex> ul(thread_mutex_);
        if (thread_)
            return;
        is_stop_run_.store(false);
        is_block_run_.store(false);
        thread_ = std::make_shared<std::thread>([&]() {
            while (true) {
                if (is_stop_run_.load())
                    return;
                condition_thread_block_.wait(ul, [&]() {return (false == is_block_run_.load());});
                each_run_entity_();
            }
            });
        if (thread_ != nullptr)
            unique_thread_id_ = get_unique_thread_id_(thread_.get()->get_id());
        seiral_in_obj_ = get_obj_serial_();
        stamp_start = std::chrono::system_clock::now();
    }
    void block() {
        bool expect = false;
        is_block_run_.compare_exchange_strong(expect, true);
    }
    void unblock() {
        bool expect = true;
        is_block_run_.compare_exchange_strong(expect, false);
        condition_thread_block_.notify_all();
    }
    void shutdown_sync() {
        shutdown_async();
        shutdown_wait();
    }
    void shutdown_async() {
        is_stop_run_.store(true);
        is_block_run_.store(false);
    }
    void shutdown_wait() {
        if (thread_.get()->joinable())
            thread_.get()->join();
    }
    const StampPoint& get_start_stamp() {
        return stamp_start;
    }
    Worker(EachRunEntity&& run_entity, const unsigned int serial_in_threadpool, const std::string& tag = "threadworker") :
        tag_(tag), serial_in_threadpool_(serial_in_threadpool) , is_stop_run_(true), is_block_run_(true), each_run_entity_(std::move(run_entity)){
        
    };
    virtual ~Worker(){};
    GF_CLASS_DELETE_COPY(Worker);
private:
    size_t get_unique_thread_id_(const std::thread::id& id) {
        std::hash<std::thread::id> hashCvt;
        size_t hash_id = hashCvt(id);
        return hash_id;
    }
    static unsigned int get_obj_serial_() {
        static std::mutex obj_id_mutex;
        static unsigned int obj_serial= 0;
        std::lock_guard<std::mutex> lg(obj_id_mutex);
        return ++obj_serial;
    }
    ShareThread thread_;
    std::mutex thread_mutex_;
    std::atomic_bool is_stop_run_;
    std::atomic_bool is_block_run_;
    std::condition_variable condition_thread_block_;
    EachRunEntity each_run_entity_;
    std::string tag_;
    size_t unique_thread_id_;
    unsigned int serial_in_threadpool_;
    unsigned int seiral_in_obj_;
    StampPoint stamp_start;
};

template<typename T_task, typename T_task_R>
inline ShareTaskInfo<T_task_R>  MakeAndRegisterTaskInfo(T_task&& task, const std::string& tag, ShareSafeQueue<ShareTaskInfo<T_task_R>> bind_task_info_list) {
    ShareTaskInfo<T_task_R> taskinfo = std::make_shared<TaskInfo<T_task_R>>(std::forward<T_task>(task), tag);
    if (bind_task_info_list)
        bind_task_info_list->push_async(taskinfo);
    else
        std::cout << "not bind task info list" << std::endl;
    return taskinfo;
}
/**
 *@brief threadpool 
 enqueuet task
 bind monitor by taskinfo_list or monitor_obj
 provide queue interface to control, clear
 need set task priority when enqueue task, implemented
 need set task delay run when enqueue task
 need set task timer run(timestamp run) when enqueue task
 need dynamic contorl queue length, and worker number: operation step:
1\queue length modify: directly call the set method of inner task queue
2\work length modify:

 * @tparam T_task_R 
 */
template<typename T_task_R>
class Threadpool {
public:
    using T_task = std::function<T_task_R()>;
    // using T_task_pair = std::pair<T_task, int>;
    using T_task_tuple = std::tuple<T_task, int, std::string>; // 任务、优先级、标签
    using TaskQueue = std::shared_ptr<SafeQueue<T_task_tuple>>;
    using WorkerList = std::list<std::shared_ptr<Worker>>;
    using StampPoint = std::chrono::time_point<std::chrono::system_clock>;
    // using ShareTaskInfo = std::shared_ptr<TaskInfo<T_task_R>>;
    //using WorkerEntity = std::function<\>;
    
    void enqueue_task_sync(const T_task& intask, const int priority = 0, std::string tag = "") {
        task_queue_->insert_sync(std::make_tuple(intask, priority, tag), [=](T_task_tuple& cur_list_task) {
            if (std::get<1>(cur_list_task) >= priority)
                return true;
            return false;
        });
    }
    void enqueue_task_sync(T_task&& intask, const int priority = 0, std::string tag = "") {
        task_queue_->insert_sync(std::make_tuple(intask, priority, tag), [=](T_task_tuple& cur_list_task) {
            if (std::get<1>(cur_list_task) >= priority)
                return true;
            return false;
        });
    };
    int enqueue_task_async(const T_task& intask, const int priority = 0, std::string tag = "") {
        return task_queue_->insert_async(std::make_tuple(intask, priority, tag), [=](T_task_tuple& cur_list_task) {
            if (std::get<1>(cur_list_task) >= priority)
                return true;
            return false;
        });
    };
    int enqueue_task_async(T_task&& intask, const int priority = 0, std::string tag = "") {
        return task_queue_->insert_async(std::make_tuple(intask, priority, tag), [=](T_task_tuple& cur_list_task) {
            if (std::get<1>(cur_list_task) >= priority)
                return true;
            return false;
        });
    };
    int enqueue_task_try(const T_task& intask, const long timeout_ms, const int priority = 0, std::string tag = "") {
        return task_queue_->try_insert(std::make_tuple(intask, priority, tag), timeout_ms, [=](T_task_tuple& cur_list_task) {
            if (std::get<1>(cur_list_task) >= priority)
                return true;
            return false;
        });
    };
    int enqueue_task_try(T_task&& intask, const long timeout_ms, const int priority = 0, std::string tag = "") {
        return task_queue_->try_insert(std::make_tuple(intask, priority, tag), timeout_ms, [=](T_task_tuple& cur_list_task) {
            if (std::get<1>(cur_list_task) >= priority)
                return true;
            return false;
        });
    };
    void work_each_entity() {
        //taske task from queue
        T_task_tuple task_tuple;
        task_queue_->pop_sync(task_tuple);
        // auto& task = task_pair.first;
        auto& task = std::get<0>(task_tuple);
        std::string tag = std::get<2>(task_tuple);

        //fixed bug, when pop_sync blocked by queue, then stop queue, will awake current pointer code, and package empty task 
        //right way is to check task if empty, if true to return;
        if (!task)
            return;
        //generate and register taskinfo
        // std::string tag("worker:");
        ShareTaskInfo<T_task_R> taskinfo = MakeAndRegisterTaskInfo<T_task&, T_task_R>(task, tag, monitor_task_info_list_);
        //ShareTaskInfo taskinfo = std::make_shared<TaskInfo<T_task_R>>(task, "worker:" + std::to_string(i))
        //g_task_info_list.push_sync(taskinfo);

        //run task
        taskinfo->execute_task_();
    }
    void start_workers() {
        std::unique_lock<std::mutex> ul(work_list_mutex_);
        if (!worker_list_.empty())
            return;
        for (int i = 0;i < inital_worker_num_;i++) {
            std::shared_ptr<Worker> worker = std::make_shared<Worker>(
               std::bind(&Threadpool::work_each_entity, this), 
                i + 1, tag_ + ":" + std::to_string(i + 1)
            );
            worker_list_.push_back(worker);
            worker.get()->launch();
        };
        is_start_works_.store(true);
    };
    void stop_workers_sync() {
        std::unique_lock<std::mutex> ul(work_list_mutex_);
        if (worker_list_.empty())
            return;
        task_queue_->stop();
        for (auto worker : worker_list_) {
            worker->shutdown_async();
        }
        for (auto worker : worker_list_) {
            worker->shutdown_wait();
        }
    };
    void wait_task_empty_shutdown(const int loop_interval_ms=1000){
        while(!get_task_queue()->empty()){
            std::this_thread::sleep_for(std::chrono::milliseconds(loop_interval_ms));
        }
        stop_workers_sync();
    }
    //for debug
    const TaskQueue get_task_queue(){
        return task_queue_;
    }
    /**
     *@brief xjf2613 2023/05/31 add
     should sync change wait for thread life cylce finished!
    if use async, can't contorl threadpool action with independent work operation, that will bring unexpect
    eg.when work shutdown alone, threadpool close, the independent work action can't expect
     * @param
     */
    int change_works_num_sync(const int expect_num) {
        std::unique_lock<std::mutex> ul(work_list_mutex_);
        if (!is_start_works_.load() || expect_num == worker_list_.size() || expect_num < 0)
            return -1;
        /**
         *@brief if expect num < actual num, pop thread, and join pop work
         if expect > actual num, new thread work, and push to worklist
         */
        if (worker_list_.size() < expect_num) {
            int serial_in_thread = 0;
            std::shared_ptr<Worker> worker = std::make_shared<Worker>(
               std::bind(&Threadpool::work_each_entity, this), 
                serial_in_thread, tag_ + ":" + std::to_string(serial_in_thread)
            );
            worker_list_.push_back(worker);
            worker.get()->launch();
        }
        if (worker_list_.size() > expect_num) {
            /**
             *@brief iterate and strip worker by run time
             */
            StampPoint earliest_point = std::chrono::system_clock::now();
            WorkerList::iterator earliest_iterator;
            for (auto it = worker_list_.begin();it != worker_list_.end();) {
                auto& cur_worker = *(*it);
                if (cur_worker.get_start_stamp() < earliest_point) {
                    earliest_point = cur_worker.get_start_stamp();
                    earliest_iterator = it;
                }
            }
            if (earliest_iterator != worker_list_.end()) {
                /**
                 *@brief match work, wati and recovery
                 */
                //async
                // earliest_iterator->get()->shutdown_async();
                earliest_iterator->get()->shutdown_sync();
                worker_list_.erase(earliest_iterator);
            }
            else {
                /**
                 *@brief no work matched, wait work and recovery, directly pop first
                 */
                if (worker_list_.empty())
                    return 0;
                auto& cur_work = worker_list_.front();
                cur_work->shutdown_sync();
                worker_list_.pop_front();
            }
        }
        return 0;
    }
    int change_works_num_sync_increase(const int increase_num) {
        int cur_num = 0;
        {
            std::unique_lock<std::mutex> ul(work_list_mutex_);
            cur_num = worker_list_.size();
        }
        return change_works_num_sync(cur_num + increase_num);
    }
    int change_works_num_sync_reduce(const int reduce_num) {
        int cur_num = 0;
        {
            std::unique_lock<std::mutex> ul(work_list_mutex_);
            cur_num = worker_list_.size();
        }
        return change_works_num_sync(cur_num - reduce_num);
    }
    int change_task_limit_max_num_async(const int expect_num){
        if (!is_start_works_.load())
            return -1;
        /**
         *@brief  just call set method of task queue
         */
        SafeQueue<T_task_tuple>& queue = *task_queue_.get();
        queue.change_limit_len_max(expect_num);
        return 0;
    }

    void bind_monitor_list(ShareSafeQueue<ShareTaskInfo<T_task_R>> monitor_task_info_list=nullptr) {
        monitor_task_info_list_ = monitor_task_info_list;
        return;
    }
    Threadpool(const int initial_worker_num, const int inital_task_limit_max, 
    TaskQueue bind_queue = nullptr, const std::string& tag = "threadpool", 
    ShareSafeQueue<ShareTaskInfo<T_task_R>> monitor_task_info_list=nullptr) :
        tag_(tag), intask_count_(0), endtask_count_(0), inital_worker_num_(initial_worker_num), inital_task_limit_max_(inital_task_limit_max), monitor_task_info_list_(monitor_task_info_list), is_start_works_(false){
        if (bind_queue == nullptr)
            task_queue_ = std::make_shared<SafeQueue<T_task_tuple>>(inital_task_limit_max);
        else 
            task_queue_ = bind_queue;
            
        //need add safequeue modify limit len dynamic
    };
    virtual ~Threadpool(){};
    GF_CLASS_DELETE_COPY(Threadpool);
private:
    std::condition_variable condition_channel_control_;
    std::string tag_;
    size_t intask_count_, endtask_count_;
    TaskQueue task_queue_;
    WorkerList worker_list_;
    const int inital_worker_num_, inital_task_limit_max_;
    ShareSafeQueue<ShareTaskInfo<T_task_R>> monitor_task_info_list_;
    std::atomic_bool is_start_works_;
    std::mutex work_list_mutex_;
    //const SafeQueue<ShareTaskInfo<T_task_R>>& monitor_task_info_list_;
};
template<typename T_task_R>
using Monitor = std::function<bool(ShareTaskInfo<T_task_R>)>;

/**
 *@brief for loop check taskinfo
 * @tparam T_task_R 
 */
template<typename T_task_R>
class LoopMonitor {
public:
    LoopMonitor(){}
    LoopMonitor(Monitor<T_task_R>&& monitor, const unsigned int loop_interval_ms, 
    const size_t monitor_max_num) : monitor_(std::move(monitor)), loop_interval_ms_(loop_interval_ms)
    {
         loop_task_info_list_ = std::make_shared<SafeQueue<ShareTaskInfo<T_task_R>>>(monitor_max_num);
    }
    ShareSafeQueue<ShareTaskInfo<T_task_R>> start() {
        std::thread([&]() {
            std::list<ShareTaskInfo<T_task_R>> cur_task_list;
            // LOG_DEBUG("enter currrent loop list len:%d\n", cur_task_list.size());
            for (;;) {
                // LOG_DEBUG("enter for currrent loop list len:%d\n", cur_task_list.size());
                std::list<ShareTaskInfo<T_task_R>> take_list;
                //fix bug, should not use sync func, will block loop
                loop_task_info_list_->pop_async_list(take_list);
                if(take_list.size() != 0)
                    cur_task_list.splice(cur_task_list.end(), take_list);
                // LOG_DEBUG("enter currrent loop list len:%d, take_list:%d\n", cur_task_list.size(), take_list.size());
                for (auto it = cur_task_list.begin(); it != cur_task_list.end();) {
                    LOG_DEBUG("enter inner currrent loop list len:%d, take_list:%d\n", cur_task_list.size(), take_list.size());
                    SLOGD("enter inner currrent loop list len: {}, take_list: {}\n", cur_task_list.size(), take_list.size());
                    //check one task status
                    //task end and processed
                    bool is_erase = (monitor_)(*it);
                    if (is_erase)
                        it = cur_task_list.erase(it);
                    else
                        it++;
                    SLOGD("out inner currrent loop list len: {}, take_list: {}\n", cur_task_list.size(), take_list.size());
                    LOG_DEBUG("out inner currrent loop list len:%d, take_list:%d\n", cur_task_list.size(), take_list.size());
                }
                // LOG_DEBUG("out currrent loop list len:%d, take_list:%d\n", cur_task_list.size(), take_list.size());
                std::this_thread::sleep_for(std::chrono::milliseconds(loop_interval_ms_));
            }
        }).detach();
        return loop_task_info_list_;
        }
private:
    ShareSafeQueue<ShareTaskInfo<T_task_R>> loop_task_info_list_;
    Monitor<T_task_R> monitor_;
    const unsigned int loop_interval_ms_;
};


GF_NAMESPACE_END(main_service)

#endif
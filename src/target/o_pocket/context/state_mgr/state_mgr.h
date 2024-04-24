#pragma once
#include <functional>
#include <string>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "http_body_cvt.h"
#include "signal_handle.h"
#include "threadloop_base.h"

extern std::map<int, std::string> g_post_err_map;

enum STATE_ENUM
{
    STATE_FREE,
    STATE_BUSY,

    TASK_UPDATE,
    TASK_REBOOT,
    TASK_RUN_OBJECTIVE,
};

struct PostState
{
    int post_task = 0;
    int err_code = 0;
    std::string err_msg;
};

class StateSuit
{
public:
    struct state_lock
    {
        state_lock(StateSuit& in_state_suit) : state_suit_ref_(in_state_suit) { state_suit_ref_.to_busy(); SLOGI("state lock to busy"); };
        ~state_lock() { state_suit_ref_.to_free(); SLOGI("state lock to free"); };
        StateSuit& state_suit_ref_;
    };
    virtual bool is_free() { return cur_state_ == STATE_FREE; };
    virtual bool is_busy() { return cur_state_ == STATE_BUSY; };
    virtual bool is_out_terminate_signal() { return SignalHandle::ins().signal_status_SIGINT() || to_stop_; };
    
protected:
    virtual void to_busy() { cur_state_ = STATE_BUSY; };
    virtual void to_free() { cur_state_ = STATE_FREE; };
    virtual void to_stop() { to_stop_ = true; };
    
    int cur_state_ = STATE_FREE;
    bool to_stop_ = false;
};


//main loop
//objective: down-> update -> down -> run  -> update -> main 


//记录一下全局的任务记录
//不同业务逻辑继承后主要封装自己的静态函数，以及存储上下文数据, 用于在post任务时被lambada表达式复用
//以及task filter, 以及task 业务逻辑
//state suit用于不同threadpool之间同步, 以及单个threadpool内进行同步

//为什么state suit参数化，有可能存在场景，多个threadpool之间同步状态
//状态驱动: 已经类似于状态机了，不同点在于当前业务并没有复杂的状态转变需求
//所有业务逻辑的call以及状态转化都集中在这里
class TaskSuitBase
{
public:

    struct TaskReturn
    {
        std::string code_msg = "";
        int32_t code_value = 0;
        int32_t task_type = 0;
    };

    TaskSuitBase(StateSuit* in_state_suit = nullptr)
        : state_suit_ref_(in_state_suit ? in_state_suit : new StateSuit{}) {};

    ~TaskSuitBase() = default;

    //post lambda
    //填写任务类型，依次在threadloop中执行, 最好在TAsksuit内封装对应的静态函数，到时候post只是包装现有静态函数+参数
    //为什么拆分一个task entity和task type，而不是一个task即可，核心的目的就是把所有的状态转换都暴露在，在这个threadloop
    //里面只关注状态转变, 而所有任务需要的上下文都包括在
    virtual int post_task(int task, std::function<TaskReturn()> task_entity);
    virtual bool task_filter();
    virtual bool to_stop_signal();

protected:

    //或使用环形队列 只持有固定数量的最新任务, 当前用不着
    virtual bool wait_task_();

    bool to_stop_ = false;
    std::mutex mtx_;
    std::condition_variable cv_;

    StateSuit* state_suit_ref_;
    std::function<TaskReturn()> task_entity_;
    int32_t task_type_;
    TaskReturn last_task_return_;
};

class TaskSuitObjective : public TaskSuitBase {
public:

    TaskSuitObjective() = default;
    ~TaskSuitObjective() = default;

    virtual bool task_filter() override{
        SLOGD("enter task fiter");
        bool is_to_terminate = false;
        is_to_terminate = TaskSuitBase::wait_task_();
        if (is_to_terminate) {
            SLOGW("after wait task accept stop, do task will return");
            is_to_terminate = true;
            return is_to_terminate;
        }

        TaskReturn task_return;
        task_return.task_type = TaskSuitBase::task_type_;
        switch (TaskSuitBase::task_type_)
        {
        case TASK_UPDATE:
            SLOGW("do update");
            // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            task_return = TaskSuitBase::task_entity_();
            TaskSuitBase::task_entity_ = nullptr;
            task_return.code_value= 0;
            task_return.code_msg = "run 5000 ms success";
            SLOGW("end update");
            break;
        
        default:
            SLOGE("current task not support, task type:{}", TaskSuitBase::task_type_);
            break;
        }

        is_to_terminate = false;
        return is_to_terminate;
    }
};

//1. 把谁做成单例, 最后对外暴露: 继承ThreadlooperBase，作为对外暴露的单例类, 只进行threadloop的流程控制和执行，以及对外全局接口的包装
//2. 业务逻辑放在哪, 组合逻辑放在哪: Tasksuit 负责实现每次threadloop执行的任务轮询
//3.哪些东西是被设计为复用的，哪些东西是被设计为继承覆写的
class ThreadloopObjectiveFSM : public ThreadlooperBase {
public:

    ~ThreadloopObjectiveFSM() = default;
    static ThreadloopObjectiveFSM& ins() {
        static ThreadloopObjectiveFSM static_ins;
        return static_ins;
    }

    TaskSuitBase* task_suit() {
        return task_suit_;
    };

protected:

    virtual bool do_init() override {
        SLOGW("enter ThreadloopObjectiveFSM do init");
        return false;
    };
    virtual bool do_release() override {
        SLOGW("enter ThreadloopObjectiveFSM do release");
        task_suit_->to_stop_signal();
        return false;
    };

    virtual bool do_once() override {
        SLOGW("enter ThreadloopObjectiveFSM do once");
        bool is_to_terminate = task_suit_->task_filter();
        return is_to_terminate;
    };

private:

    ThreadloopObjectiveFSM() = default;
    TaskSuitBase* task_suit_ = new TaskSuitObjective{};
};

class StateMgr
{
    struct state_lock
    {
        state_lock() { StateMgr::ins().busy(); StateMgr::ins().begin_task();SLOGI("state lock to busy"); };
        ~state_lock() { StateMgr::ins().free(); StateMgr::ins().end_task(); SLOGI("state lock to free"); };
    };
    class Threadlooper_I30_Qnx700 : public ThreadlooperBase
    {
    public:
        virtual bool do_init() override {};
        virtual bool do_release() override {};
        virtual bool do_once() override;
    };
public:
    ~StateMgr() = default;
    static StateMgr& ins() {
        static StateMgr static_ins;
        return static_ins;
    }
    //for outside: http server
    // void post_task_info(int task_type, ns::UpdateTaskInfo info){
        
    // }
    // void get_state(int& out_busy_or_free, PostState& out_cur_task, PostState& out_last_task){
        
    // }
    //for outside: main thread
    // void launch_i30_threadloop() {
        
    // }
    // void to_stop_i30_threadloop(){
    //     StateMgr::ins().post_task(-1);
    // }
    // void join_i30_threadloop() {

    // }
    // void detach_i30_threadloop(){

    // }
    //for inner
    // void to_busy();
    // void to_free();
    // bool is_free();
    // bool is_busy();
    // bool is_out_terminate_signal();
    // bool post_task(int task);
    // bool wait_task();
    


    
    //check state  and post task update task busy, when task done, to update task free
    void busy() { cur_state_ = STATE_BUSY; };
    void free() { cur_state_ = STATE_FREE; };
    bool is_free() { return (cur_state_ == STATE_FREE); }
    bool is_busy() { return (cur_state_ == STATE_BUSY); }
    PostState get_come_task() { return come_task; }
    PostState& get_on_task() { return on_task; };
    bool is_to_stop_();

    //update taskinfo
    void post_task_info(int task_type, ns::UpdateTaskInfo info);

    bool post_task(const int task);
    bool wait_task();

    void begin_task();
    void end_task();

private:
    StateMgr() = default;

    bool is_task_come = false;
    int cur_state_ = STATE_FREE;
    bool to_stop_ = false;

    PostState come_task;
    PostState on_task ;

    std::mutex mtx_;
    std::condition_variable cv_;

    ns::UpdateTaskInfo update_task_info_;
};



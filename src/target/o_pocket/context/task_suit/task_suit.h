#pragma once
#include "state_suit.h"

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
        TaskReturn(int32_t incode_value, const std::string& incode_msg,  int32_t intask_type)
            : code_msg(incode_msg), code_value(incode_value), task_type(intask_type) {};
        TaskReturn()
            : code_msg("success"), code_value(0), task_type(TASK_NONE) {};
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


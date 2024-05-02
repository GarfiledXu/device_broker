#pragma once
//tool
#include "filesystem_impl.inl"

//task suit
#include "state_suit.h"
#include "task_suit.h"

//custom component
#include "threadpool.hpp"
#include "safe_queue.hpp"
#include "message_bus.hpp"
#include "rabbitmq_handle.h"
#include "message_manager.h"
#include "samba_transfer.h"

//testbed
#include "testbed_param.h"
#include "testbed_cmd_parse.h"
#include "task_status.h"
#include "logic_impl_http_service_objective.h"

extern std::map<int, std::string> g_post_err_map;

class TaskSuitObjective : public TaskSuitBase {
public:

    TaskSuitObjective() = default;
    ~TaskSuitObjective() = default;

    virtual bool task_filter() override;
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

    TaskSuitBase* task_suit() ;
    void to_stop_singal();

protected:

    virtual bool do_init() override {
        SLOGW("enter ThreadloopObjectiveFSM do init");
        return false;
    };
    virtual bool do_release() override {
        SLOGW("enter ThreadloopObjectiveFSM do release");
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



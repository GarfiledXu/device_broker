#include "task_suit.h"

bool TaskSuitBase::to_stop_signal()
{
    struct tmp_stop {
        tmp_stop(std::condition_variable& incv) : cv(incv) {};
        ~tmp_stop() { cv.notify_all(); SLOGW("to_stop_signal cv to notify all"); };
        std::condition_variable& cv;
    };
    tmp_stop{ cv_ };
    return SignalHandle::ins().signal_status_SIGINT() || to_stop_;
}

int TaskSuitBase::post_task(int task, std::function<TaskReturn()> task_entity)
{
    if (task_entity_ != nullptr) {
        SLOGW("task entity is not nullptr, will return, post task not accept");
        return -1;
    }
    task_type_ = task;
    task_entity_ = std::move(task_entity);
    cv_.notify_all();
    return 0;
}

bool TaskSuitBase::wait_task_()
{
    SLOGW("wait for task");
    bool is_to_termiate = false;

    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [&] { return (task_entity_ != nullptr) || to_stop_signal(); });

    if (to_stop_signal()) {
        SLOGW("wait task, get to stop state");
        is_to_termiate = true;
        return is_to_termiate;
    }

    //get task
    SLOGW("get task");
    // on_task = come_task;
    SLOGD("out wait task");
    is_to_termiate = false;
    return is_to_termiate;
}

bool TaskSuitBase::task_filter()
{
    SLOGD("enter task fiter");
    bool is_to_terminate = false;
    is_to_terminate = wait_task_();
    if (is_to_terminate) {
        SLOGW("after wait task accept stop, do task will return");
        is_to_terminate = true;
        return is_to_terminate;
    }

    TaskReturn task_return;
    task_return.task_type = task_type_;
    switch (task_type_)
    {
    case TASK_UPDATE:
        SLOGW("do update, 5000 ms");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        task_return.code_value= 0;
        task_return.code_msg = "run 5000 ms success";
        SLOGW("end update, 5000 ms");
        break;
    
    default:
        SLOGE("current task not support, task type:{}", task_type_);
        break;
    }

    is_to_terminate = false;
    return is_to_terminate;
}

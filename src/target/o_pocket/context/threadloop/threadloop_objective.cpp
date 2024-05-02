#include "threadloop_objective.h"


extern std::map<int, std::string> g_post_err_map =
{
    {-1, "device is busy, task reject"},
    {-2, "input task param error"}
};

//状态驱动
//所有的状态都最后 post 回流到task filter进行统一处理
bool TaskSuitObjective::task_filter()
{
    SLOGD("enter task fiter");
    bool is_to_terminate = false;
    is_to_terminate = TaskSuitBase::wait_task_();
    if (is_to_terminate) {
        SLOGW("after wait task accept stop, do task will return");
        is_to_terminate = true;
        return is_to_terminate;
    }

    TaskSuitBase::TaskReturn task_return;
    task_return.task_type = TaskSuitBase::task_type_;

    switch (TaskSuitBase::task_type_)
    {

    case TASK_UPDATE:
        SLOGW("do update");
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        task_return = TaskSuitBase::task_entity_();
        SLOGW("end update, code value:{}, code msg:{}, task type:{}"
            , task_return.code_value, task_return.code_msg, task_return.task_type);
        break;

    case TASK_RUN_OBJECTIVE:
        SLOGW("do run objective");
        task_return = TaskSuitBase::task_entity_();
        SLOGW("end run objective");
        break;

    case TASK_REBOOT:
        SLOGW("do device reboot");
        task_return = TaskSuitBase::task_entity_();
        SLOGW("end device reboot");
        break;

    case TASK_FILE_OPT_FILE_PULL:
        SLOGW("do file opt file pull");
        task_return = TaskSuitBase::task_entity_();
        SLOGW("end file opt file pull");
        break;

    case TASK_FILE_OPT_FILE_CLEAR:
        SLOGW("do file opt file clear");
        task_return = TaskSuitBase::task_entity_();
        SLOGW("end file opt file clear");
        break;


    default:
        SLOGE("current task not support, task type:{}", TaskSuitBase::task_type_);
        break;
    }

    TaskSuitBase::task_entity_ = nullptr;

    is_to_terminate = false;
    return is_to_terminate;
}

TaskSuitBase* ThreadloopObjectiveFSM::task_suit()
{
    return task_suit_;
}

void ThreadloopObjectiveFSM::to_stop_singal()
{
    task_suit_->to_stop_signal();
}




#include "threadloop_i30_qnx700.h"
//option1
//check status
//post lambda task which using logic func
//return code
//option2
//using state machine, post enum only, and return by same function
//option3
//post task to threadloop, when task finished update value to global info which reference by http query state
bool Threadlooper_I30_Qnx700::do_init()
{
    SLOGW("enter do init");
    return false;
}

//query task: current and 
bool Threadlooper_I30_Qnx700::do_once()
{
    bool ret = StateMgr::ins().wait_task();
    SLOGI("enter do once, loop count:[{}] >>>>", loop_counter_);
    state_lock after_wait_state_lock{};
    if (!ret) {
        SLOGW("after wait task accept stop, do task will return");
        return false;
    }

    //current free
    auto& on_task = StateMgr::ins().get_on_task();
    switch (on_task.post_task)
    {
    case TASK_UPDATE:
        SLOGW("do update, 5000 ms");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        on_task.err_code = 0;
        on_task.err_msg = "run 5000 ms success";
        SLOGW("end update, 5000 ms");
        break;
    
    default:
        SLOGE("current task not support, task type:{}", on_task.post_task);
        break;
    }
    
    SLOGI("out do once, loop count:[{}] <<<<", loop_counter_);
    return false;
}

bool Threadlooper_I30_Qnx700::do_release()
{
    SLOGW("enter do release");
    return false;
}

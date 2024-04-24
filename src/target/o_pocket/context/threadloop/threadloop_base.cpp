#include "threadloop_base.h"

int ThreadlooperBase::launch_front()
{
    SLOGI("enter launch front");
    if (is_running_) {
        return -1;
    }
    run_logic_();
    SLOGI("out launch front");
    return 0;
}

int ThreadlooperBase::launch_back()
{
    SLOGI("enter launch back");
    if (is_running_) {
        return -1;
    }
    work_ = std::thread([&]() {
        run_logic_();
        });
    SLOGI("out launch back");
    return 0;
}

void ThreadlooperBase::join()
{
    SLOGI("enter join");
    if (work_.joinable()) {
        work_.join();
    }
    SLOGI("out join");
    return;
}

void ThreadlooperBase::detach()
{
    SLOGI("enter detach");
    if (work_.joinable()) {
        work_.detach();
    }
    SLOGI("out detach");
    return;
}

bool ThreadlooperBase::is_running()
{
    return is_running_;
}

void ThreadlooperBase::signal_stop()
{
    SLOGI("signal stop");
    to_stop_ = true;
    return;
}

void ThreadlooperBase::run_logic_()
{
    SLOGI("enter run logic");
    loop_counter_ = 0;
    is_running_ = true;
    to_stop_ = false;
    //init
    if (do_init()) {
        to_stop_ = true;
        is_running_ = false;
    }
    //loop
    for (;!to_stop_ && !SignalHandle::ins().signal_status_SIGINT();) {
        loop_counter_++;
        if (do_once()) {
            to_stop_ = true;
            break;
        }
    }
    //uninit
    do_release();
    to_stop_ = true;
    is_running_ = false;
    SLOGI("out run logic");
}
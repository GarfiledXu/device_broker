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
#include "log.h"

enum STATE_ENUM
{
    STATE_FREE,
    STATE_BUSY,

    TASK_UPDATE,
    TASK_REBOOT,
    TASK_RUN_OBJECTIVE,
    TASK_FILE_OPT_FILE_PULL,
    TASK_FILE_OPT_FILE_CLEAR,
    TASK_NONE,
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



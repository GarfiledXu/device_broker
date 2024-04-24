#pragma once
#include "threadloop_base.h"
#include "state_mgr.h"

//override switch state logic
class Threadlooper_I30_Qnx700 : public ThreadlooperBase
{
public:
    struct state_lock
    {
        state_lock() { StateMgr::ins().busy(); StateMgr::ins().begin_task();SLOGI("state lock to busy"); };
        ~state_lock() { StateMgr::ins().free(); StateMgr::ins().end_task(); SLOGI("state lock to free"); };
    };
    Threadlooper_I30_Qnx700() = default;
    ~Threadlooper_I30_Qnx700() = default;

    virtual bool do_init() override;
    virtual bool do_once() override;
    virtual bool do_release() override;

    void to_stop() {
        StateMgr::ins().post_task(-1);
    }
};


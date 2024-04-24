#pragma once
#include <functional>
#include <string>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "signal_handle.h"
#include "log.h"

//multiple threadlooper shader the state of device busy or free and on_task()
//the task required data managed by thread looper, it's the entry of data set and ref
class ThreadlooperBase
{
public:
    ThreadlooperBase() = default;
    ~ThreadlooperBase() = default;

    int launch_front();
    int launch_back();

    void join();
    void detach();

    bool is_running();
    void signal_stop();

protected:
    virtual bool do_init() = 0;
    virtual bool do_once() = 0;
    virtual bool do_release() = 0;


protected:
    void run_logic_();
    long loop_counter_ = 0;
    bool is_backend_ = true;
    bool is_running_ = false;
    bool to_stop_ = true;
    std::thread work_;
};
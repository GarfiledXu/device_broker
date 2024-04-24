#pragma once
#include <memory>
#include <atomic>
#include <functional>
#include <thread>
#include <string>
#include "filesystem_test.hpp"
#include "log.h"

// if update expired time when time tick is running
// return false to indicate update false, the time tick is running
class TimeTick {
public:
    TimeTick(const long in_expired_time_ms);
    virtual ~TimeTick();

    virtual bool start();
    virtual bool update_expired_time(const long in_expired_time_ms);
    virtual void set_expired_callback(std::function<void(const long in_expired_time_ms)>);
    virtual bool is_expired();
private:
    long time_ms_;
    std::atomic_bool is_expired_;
    std::atomic_bool is_running_;
    std::function<void(const long)> expired_callback_;
};

//flow is inline implementation
inline TimeTick::TimeTick(const long in_expired_time_ms)
    : time_ms_(in_expired_time_ms)
    , is_expired_(false)
    , is_running_(false)
    , expired_callback_([](const long) {;}) {
}

inline TimeTick::~TimeTick() {
}

inline bool TimeTick::start() {
    bool opt_success = true;
    std::thread thread_back([&]() {
        SLOGD("timetick start!");
        is_running_.store(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(time_ms_));
        is_expired_.store(true);
        is_running_.store(false);
        SLOGD("will enter expired callback");
        expired_callback_(time_ms_);
        // SLOGD("will out expired callback");
        SLOGD("timetick out!");
    });
    thread_back.detach();
    return opt_success;
}

inline bool TimeTick::update_expired_time(const long in_expired_time_ms) {
    bool opt_success = true;
    if (is_running_.load()) {
        SLOGE("time tick is running, can't update expired current time:{}, to dst time:{}", time_ms_, in_expired_time_ms);
        return false;
    }
    time_ms_ = in_expired_time_ms;
    return opt_success;
}

inline void TimeTick::set_expired_callback(std::function<void(const long in_expired_time_ms)> in_callback) {
    expired_callback_ = std::move(in_callback);
}

inline bool TimeTick::is_expired() {
    if (is_expired_.load()) {
        // SLOGW("time tick is expired!");
    }
    return is_expired_.load();
}

#pragma once
#include <chrono>
#include <iostream>

template<typename T_clock = std::chrono::steady_clock>
class TimeInterval {
public:
    TimeInterval() { update_start_time(); };
    virtual ~TimeInterval() {};

    void update_start_time() {
        start_time_ = T_clock::now();
    }
    long long get_interval_ns() {
        return get_interval<std::chrono::nanoseconds>();
    }
    long long get_interval_us() {
        return get_interval<std::chrono::microseconds>();
    }
    long long get_interval_ms() {
        return get_interval<std::chrono::milliseconds>();
    }
    long long get_interval_s() {
        return get_interval<std::chrono::seconds>();
    }

private:
    template<typename T_duration>
    long long get_interval() const {
        auto end_time = T_clock::now();
        auto duration = std::chrono::duration_cast<T_duration>(end_time - start_time_).count();
        return duration;
    }
    typename T_clock::time_point start_time_;
};


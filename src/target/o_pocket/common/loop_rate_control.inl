#pragma once
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>

//1.只对小于目标耗时的帧进行延迟，超出的直接忽略
//2.添加控制整体耗时，超出的限时的帧同样直接忽略，但小于目标耗时的帧具体延时要根据当前进度进行计算(最粗暴的就是一旦发现落后于当前进度，直接不进行延迟，直到赶上当前进度，缺点不够平滑)
template<typename T_clock = std::chrono::steady_clock>
class LoopRateControl {
    using CbOutLimit = std::function<void(const long limit_interval_us, const typename T_clock::time_point& last_time_point)>;
    using CbNonOutLimitBeforeSleep = std::function<void(const long limit_interval_us, const typename T_clock::time_point& last_time_point)>;

public:
    LoopRateControl(CbOutLimit input_cb1 = nullptr, CbNonOutLimitBeforeSleep input_cb2 = nullptr);
    virtual ~LoopRateControl() = default;

    //limit interval time
    //template argument indict the time unit
    void update_limit_time(const long new_limit_interval_us);
    //convert fps to limit interval us
    void update_limit_fps(const float new_fps);
    bool is_out_limit_time(long& out_reduce);
    void control_point();

    //get interval last point
    long long get_last_interval_ns();
    long long get_last_interval_us();
    long long get_last_interval_ms();
    long long get_last_interval_s();

    //for test
    static void unit_test();

private:
    template<typename T_duration>
    long long get_interval_() const;

    //for convert to interval
    float fps_;
    std::atomic<uint32_t> limit_interval_us_;
    typename T_clock::time_point last_time_point_;
    //record first control point
    bool is_fist_enter_control_;

    //callback
    CbOutLimit cb_out_limit_;
    CbNonOutLimitBeforeSleep cb_non_out_limit_before_sleep;
};

//fllowing implementation
template<typename T_clock>
inline LoopRateControl<T_clock>::LoopRateControl(CbOutLimit input_cb1, CbNonOutLimitBeforeSleep input_cb2)
    : cb_out_limit_(std::move(input_cb1))
    , cb_non_out_limit_before_sleep(std::move(input_cb2))
    , limit_interval_us_(0)
    , fps_(0.0f)
    , is_fist_enter_control_(true)
{
}

template<typename T_clock>
inline void LoopRateControl<T_clock>::update_limit_time(const long new_limit_interval) {
    if(new_limit_interval < 1000){
        std::string msg = std::string("LoopRateControl obj call member: update_limit_time fail, new_limit_interval < 1000, the time unit is us brother, you input too little, value:") + std::string(std::to_string(new_limit_interval));
        throw std::logic_error(msg);
    }
    limit_interval_us_.store(new_limit_interval);
}

template<typename T_clock>
inline void LoopRateControl<T_clock>::update_limit_fps(const float new_fps) {
    if(new_fps < 0){
        std::string msg = std::string("LoopRateControl obj call member: update_limit_fps fail, new_fps < 0, the time unit is float brother, you input too little, value:") + std::string(std::to_string(new_fps));
        throw std::logic_error(msg);
    }
    fps_ = new_fps;
    limit_interval_us_.store(1000000.0f / new_fps);
}

template<typename T_clock>
inline bool LoopRateControl<T_clock>::is_out_limit_time(long& out_reduce) {
    out_reduce = limit_interval_us_ - get_last_interval_us();
    if (out_reduce > 0) {
        return false;
    }
    return true;
}

template<typename T_clock>
inline void LoopRateControl<T_clock>::control_point() {
    if (limit_interval_us_ == 0) {
        throw std::logic_error("LoopRateControl obj call member: control_point fail, limit_interval_us is 0, try to call: update_limit_time or update_limit_fps");
    }
    
    //first enter only to update time point
    if (is_fist_enter_control_) {
        printf("enter first\n");
        is_fist_enter_control_ = false;
        last_time_point_ = T_clock::now();
        return;
    }
    
    //out limit, do noting
    long reduce = 0;
    if (is_out_limit_time(reduce)) {
        // printf("enter outlimit reduce:%ld ms\n", reduce/1000);
        if (cb_out_limit_) {
            cb_out_limit_(limit_interval_us_, last_time_point_);
        }
        last_time_point_ = T_clock::now();
        return;
    }
    // printf("will sleep for reduce:%ld ms\n", reduce/1000);
    if(reduce < 0){
        throw std::logic_error("LoopRateControl obj call member: control_point fail, sleep reduce < 0");
    }
    //non limit, to sleep duration of reduce and to set last time point
    if (cb_non_out_limit_before_sleep) {
        cb_non_out_limit_before_sleep(limit_interval_us_, last_time_point_);
    }
    std::this_thread::sleep_for(std::chrono::microseconds(reduce));
    last_time_point_ = T_clock::now();
    return;
}

template<typename T_clock>
inline long long LoopRateControl<T_clock>::get_last_interval_ns() {
    return get_interval_<std::chrono::nanoseconds>();
}

template<typename T_clock>
inline long long LoopRateControl<T_clock>::get_last_interval_us() {
    return get_interval_<std::chrono::microseconds>();
}

template<typename T_clock>
inline long long LoopRateControl<T_clock>::get_last_interval_ms() {
    return get_interval_<std::chrono::milliseconds>();
}

template<typename T_clock>
inline long long LoopRateControl<T_clock>::get_last_interval_s() {
    return get_interval_<std::chrono::seconds>();
}

template<typename T_clock>
template<typename T_duration>
inline long long LoopRateControl<T_clock>::get_interval_() const {
    auto end_time = T_clock::now();
    auto duration = std::chrono::duration_cast<T_duration>(end_time - last_time_point_).count();
    return duration;
}

//unit test
#if 0
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#endif
template<typename T_clock>
inline void LoopRateControl<T_clock>::unit_test() {
    #if 0
    LoopRateControl<> ccc{
        [](const long limit_interval_us, const typename std::chrono::steady_clock::time_point& last_time_point) {printf("enter out limit\n");},
        [](const long limit_interval_us, const typename std::chrono::steady_clock::time_point& last_time_point) {printf("enter non out limit\n");}
    };
    //ccc.update_limit_fps(0.10f);
    ccc.update_limit_time(10*1000);
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(ms));
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(ms) - seconds);
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        std::tm* ptm = std::localtime(&tt);
        char buffer[32];
        std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", ptm);
        std::cout << buffer << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << std::endl;
        ccc.control_point();
    }
    #endif
    return;
}


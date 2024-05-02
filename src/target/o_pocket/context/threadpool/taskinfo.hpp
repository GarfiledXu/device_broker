#ifndef GF_TASK_HPP
#define GF_TASK_HPP
#include "my-internal.h"
GF_NAMESPACE_START(main_service)
/**
 *@brief provide task time info and basic status:
if task finished!
run time duraction
duration between task start to current timepoint
 * @tparam T_task_R
 */
template<typename T_task_R>
class TaskInfo;
template<typename T_task_R>
class TaskTimer {
public:
    friend class TaskInfo<T_task_R>;
    using StampPoint = std::chrono::time_point<std::chrono::system_clock>;

    TaskTimer() : is_start_(false), is_end_(false), stamp_start_(get_now()), stamp_end_(get_now()){};
    virtual ~TaskTimer(){};
    GF_CLASS_DELETE_COPY(TaskTimer);

    long long get_elapsed_ms() {
        if (!is_start_)
            return 0;
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(get_now() - stamp_start_).count(); 
        return elapsed_ms;
    };
    long long get_end_elapsed_ms() {
        if (!is_end_)
            return 0;
        return run_elapsed_ms_;
    };
    bool is_end() {
        return is_end_;
    }
    bool is_start(){
        return is_start_;
    }
private:
    void start() {
        if (is_start_)
            return;
        stamp_start_ = get_now();
        is_start_ = true;
    };
    void end() {
        if (is_end_)
            return;
        stamp_end_ = get_now();
        run_elapsed_ms_ = std::chrono::duration_cast<std::chrono::milliseconds>(stamp_end_ - stamp_start_).count();
        is_end_ = true;
    };
    StampPoint get_now() {
        return std::chrono::system_clock::now();
    };
    StampPoint stamp_start_, stamp_end_;
    long long run_elapsed_ms_;
    bool is_end_, is_start_;
};

template<typename T_task_R>
class Threadpool;
template<typename T_task_R>
class TaskInfo {
public:
    friend class Threadpool<T_task_R>;
    //using Future_ = std::future<T_task_R>;
    //using Future__ = std::shared_ptr<future_>;
    using Future = std::shared_future<T_task_R>;
    using TaskPkg = std::packaged_task<T_task_R()>;
    //using TaskPkg = std::shared_ptr<TaskPkg_ >;
    using Task = std::function<T_task_R()>;
    using Timer = std::shared_ptr<TaskTimer<T_task_R>>;

    //TaskInfo(Task& task, const std::string& tag = "taskinfo"):tag_(tag), obj_serial_(obj_count_++), task_pkg_(task){};
    template<typename T>
    TaskInfo(T&& task, const std::string& tag = "taskinfo") :tag_(tag), obj_serial_(obj_count_++), task_pkg_(std::forward<T>(task)) {
        future_ = task_pkg_.get_future();
        timer_ = std::make_shared<TaskTimer<T_task_R>>();
    }
    virtual ~TaskInfo(){};
    GF_CLASS_DELETE_COPY(TaskInfo);

    Timer get_timer() {
        return timer_;
    };
    size_t get_obj_serial() {
        return obj_serial_;
    }
    size_t get_obj_count() {
        return obj_count_.load();
    }
    Future get_future() {
        return future_;
    }
    std::string get_tag()const{
        return tag_;
    }
    
private:
    Timer timer_;
    const std::string tag_;
    const size_t obj_serial_;
    static std::atomic<size_t> obj_count_;
    TaskPkg task_pkg_;
    Future future_;
    void execute_task_() {
        timer_.get()->start();
        task_pkg_();
        timer_.get()->end();
    };
};
template<typename T_task_R>
std::atomic<size_t> TaskInfo<T_task_R>::obj_count_{0};




GF_NAMESPACE_END(main_service)


#endif
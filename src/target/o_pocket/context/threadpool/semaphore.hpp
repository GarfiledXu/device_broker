#ifndef GF_FRAME_WRAPPER_HPP
#define GF_FRAME_WRAPPER_HPP
#include "my-internal.h"

class Semaphore{
public:
    int try_acquire(const int permit_num, const long timeout_ms) {
        std::unique_lock<std::mutex> ul(mutex_);
        if (condition_var_.wait_for(ul, std::chrono::milliseconds(timeout_ms), [&]() {return (permit_available_ >= permit_num);})) {
            permit_available_ -= permit_num;
            return 0;
        }
        return -1;
    }
    int acquire_sync(const int permit_num) {
        std::unique_lock<std::mutex> ul(mutex_);
        condition_var_.wait(ul, [&]() {return (permit_available_ >= permit_num);});
        permit_available_ -= permit_num;
        return 0;
    }
    int acquire_async(const int permit_num) {
        std::unique_lock<std::mutex> ul(mutex_);
        if(permit_available_ < permit_num)
            return -1;
        permit_available_ -= permit_num;
        return 0;
    }
    int release(const int permit_num) {
        std::unique_lock<std::mutex> ul(mutex_);
        permit_available_ += permit_num;
        if (permit_available_ > permit_limit_max_)
            permit_available_ = permit_limit_max_;
        condition_var_.notify_all();
        return 0;
    }
    int release_all() {
        std::unique_lock<std::mutex> ul(mutex_);
        if(permit_available_ < permit_limit_max_){
            permit_available_ = permit_limit_max_;
            condition_var_.notify_all();
        }
        return 0;
    }
    int query_available_permit() {
        std::unique_lock<std::mutex> ul(mutex_);
        return permit_available_;
    }

    Semaphore  (const size_t permit_limit_max) : permit_available_(permit_limit_max_), permit_limit_max_(permit_limit_max){ };
    ~Semaphore () {};

private:
    const size_t permit_limit_max_;
    int permit_available_;
    std::condition_variable condition_var_;
    std::mutex mutex_;
};
template<typename T_semaphore>
class SemaGuardSync {
public:
    GF_CLASS_DELETE_COPY(SemaGuardSync);
    GF_CLASS_DELETE_MOVE(SemaGuardSync);
    SemaGuardSync(T_semaphore& in_semaphore, const int permit_num) : permit_num_(permit_num), semaphore_(in_semaphore), is_call_success_(false) {
        if (!semaphore_.acquire_sync(permit_num_))
            is_call_success_ = true;
    };
    virtual ~SemaGuardSync() {
        if (is_call_success_)
            semaphore_.release(permit_num_);
    }
private:
    T_semaphore& semaphore_;
    bool is_call_success_;
    const int permit_num_;
};
template<typename T_semaphore>
class SemaGuardTry {
public:
    GF_CLASS_DELETE_COPY(SemaGuardTry);
    GF_CLASS_DELETE_MOVE(SemaGuardTry);
    SemaGuardTry(T_semaphore& in_semaphore, const int permit_num, const long timeout_ms) : permit_num_(permit_num), semaphore_(in_semaphore), is_call_success_(false) {
        if (!semaphore_.try_acquire(permit_num_, timeout_ms))
            is_call_success_ = true;
    };
    virtual ~SemaGuardTry() {
        if (is_call_success_)
            semaphore_.release(permit_num_);
    }
private:
    T_semaphore& semaphore_;
    bool is_call_success_;
    const int permit_num_;
};
template<typename T_semaphore>
class SemaGuardAsync {
public:
    GF_CLASS_DELETE_COPY(SemaGuardAsync);
    GF_CLASS_DELETE_MOVE(SemaGuardAsync);
    SemaGuardAsync(T_semaphore& in_semaphore, const int permit_num) : permit_num_(permit_num), semaphore_(in_semaphore), is_call_success_(false) {
        if (!semaphore_.acquire_async(permit_num_))
            is_call_success_ = true;
    };
    virtual ~SemaGuardAsync() {
        if (is_call_success_)
            semaphore_.release(permit_num_);
    }
private:
    T_semaphore& semaphore_;
    bool is_call_success_;
    const int permit_num_;
};;
inline int semaphore_test_all() {
    return 0;
}
#endif
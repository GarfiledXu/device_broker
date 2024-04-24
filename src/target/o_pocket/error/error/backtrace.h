#pragma once
#include <atomic>
#include <mutex>
#include <functional>

class Backtrace {
public:
    ~Backtrace() = default;
    static Backtrace& ins() {
        static Backtrace static_ins;
        return static_ins;
    }
    //enable/disable
    void enable(size_t size);
    void disable();
    bool enable() const;
    void push_back();
    bool empty() const;



private:
    Backtrace() = default;


};
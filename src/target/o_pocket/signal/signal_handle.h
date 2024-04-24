#pragma once
#include <csignal>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <mutex>

//关于信号处理
//首先信号处理绑定的必须是全局函数，也就是最终还是要实现在一个全局函数中，让所有对象去暴露相关引用给全局函数显然不可能，
//因为对象有局部的和全局的, 让全局函数去持有局部对象的引用将会复杂化
//换个思路，设置全局对象给全局处理函数持有，将信号与全局对象关联，然后再让 需要处理信号的对象去进行引用绑定，响应
//每一个模块去持有全局信号的引用，自己处理自己的信号需求，同时也可以暴露stop接口给其他模块，要注意多线程多stop的情况
#define REGISTER_SIGINT_HANDLE() std::signal(SIGINT, SignalHandle::signal_come);

#define SIGNAL_STORE_INCREASE(signal_name) \
if (signal_name == SIGINT) {\
    std::lock_guard<std::mutex> lg(SignalHandle::ins().signal_mutex_##signal_name##_); \
    {\
        SignalHandle::ins().signal_status_##signal_name##_++;\
    }\
}

#define SIGNAL_AND_FUNC_DEFINE(signal_name) \
public: const int& signal_status_##signal_name() const {\
    std::lock_guard<std::mutex> lg(SignalHandle::ins().signal_mutex_##signal_name##_); \
    return signal_status_##signal_name##_ ; \
} \
private: int signal_status_##signal_name##_ = 0; \
private: std::mutex signal_mutex_##signal_name##_;

class SignalHandle {
public:

    virtual ~SignalHandle() = default;
    static SignalHandle& ins() {
        static SignalHandle static_ins;
        return static_ins;
    }
    
    static void signal_come(int signal) {
        printf("enter signal come\n");
        SIGNAL_STORE_INCREASE(SIGINT);
    }
    SIGNAL_AND_FUNC_DEFINE(SIGINT)

    friend void signal_come(int signal);
private:
    SignalHandle() = default;
};

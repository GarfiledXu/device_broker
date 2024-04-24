#pragma once
#include <memory>
#include <atomic>
#include <functional>
#include <thread>
#include <string>
#include "filesystem_test.hpp"
#include "log.h"
#include "time_interval.inl"

struct MonitorCommandStr {
    static std::string gen_android_top_cmd_with_grep(const std::string& cmd_grep_str);
    static std::string gen_qnx_hogs_cmd_with_grep(const std::string& cmd_grep_str);
    static std::string gen_qnx_pidin_cmd_with_pid(const int pid);
};

class SystemCall {
public:
    SystemCall(const std::string& in_cmd_str);
    virtual ~SystemCall();

    virtual int execute();
    virtual bool is_running();
    virtual int get_output_ret();
    virtual bool get_output_str(std::string& out_output_str);
    virtual std::string get_run_cmd();

private:
    int run_cmd_and_output(const std::string& cmd_str, std::string& output_str);
    int filter_system_call_ret(const int in_ret);

    std::string cmd_str_;
    std::atomic_bool is_running_;
    int output_ret_;
    std::string output_str_;
};

class RecordBackend {
public:
    RecordBackend(std::function<bool()> is_stop, const std::string& record_cmd, const std::string& record_path, const int interval_ms);
    virtual ~RecordBackend();

    void to_stop();
    void launch();
    void join();
private:
    virtual int prepare_dir(const std::string& target_file);
    std::thread thread_back_;
    std::function<bool()> is_stop_;
    std::atomic_bool is_to_stop_;
    std::string record_cmd_;
    std::string record_path_;
    int interval_ms_;
};
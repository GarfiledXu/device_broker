#include "system_call.h"

//MonitorCommandStr
std::string MonitorCommandStr::gen_android_top_cmd_with_grep(const std::string& cmd_grep_str)
{
    return fmt::format("top -n 1 | grep {}", cmd_grep_str);
}

std::string MonitorCommandStr::gen_qnx_hogs_cmd_with_grep(const std::string& cmd_grep_str)
{
    return fmt::format("hogs -i 1 | grep {}", cmd_grep_str);
}

std::string MonitorCommandStr::gen_qnx_pidin_cmd_with_pid(const int pid)
{
    return fmt::format("pidin -p {}", pid);
}

//SystemCall
SystemCall::SystemCall(const std::string& in_cmd_str)
    : is_running_(false)
    , output_ret_(0)
    , cmd_str_(in_cmd_str)
    , output_str_(""){
}

SystemCall::~SystemCall() {
}

int SystemCall::execute() {
    is_running_.store(true);
    int ret = 0;
    if (cmd_str_ == "") {
        SLOGE("error cmd_str_ is empty");
    }
    // SLOGD("start execute! commond:\n{}", cmd_str_);
    ret = run_cmd_and_output(cmd_str_, output_str_);
    int filter_ret = filter_system_call_ret(ret);
    if(filter_ret){
        SLOGE("end execute! ret:{}, after filter ret:{}, commond:\n{}", ret, filter_ret, cmd_str_);
    }
    // SLOGD("end execute! ret:{}, after filter ret:{}, commond:\n{}", ret, filter_ret, cmd_str_);
    is_running_.store(false);
    return filter_ret;
}

bool SystemCall::is_running() {
    return is_running_.load();
}

int SystemCall::get_output_ret() {
    if (is_running()) {
        throw std::logic_error("system call is running, no ret generated!\n");
        return -1;
    }
    return output_ret_;
}

bool SystemCall::get_output_str(std::string& out_output_str) {
    if (is_running()) {
        throw std::logic_error("system call is running, no ret generated!\n");
        return false;
    }
    out_output_str = output_str_;
    return true;
}

std::string SystemCall::get_run_cmd() {
    return cmd_str_;
}

int SystemCall::run_cmd_and_output(const std::string& cmd_str, std::string& output_str) {
    output_str.clear();
    std::array<char, 256> buffer1;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd_str.c_str(), "r"), pclose);
    if (!pipe) {
        return -1000;
    }
    while (fgets(buffer1.data(), buffer1.size(), pipe.get()) != nullptr) {
        output_str += buffer1.data();
    }
    int ret = pclose(pipe.get());
    if (output_str == "") {
        SLOGE("run cmd no output, ret:{}, cmd str:{}, output:{}", ret, cmd_str, output_str);
    }
    // SLOGD("run and record output, pclose ret:{}\noutput_str:[ {} ]\ncmd_str:[ {} ]", ret, output_str, cmd_str);
    return ret;
}

int SystemCall::filter_system_call_ret(const int ret) {
    const int ret_in = ret;
    // SLOGD("filter system call ret, src ret:{}", ret_in);
    if (-1 == ret) {
        SLOGE("filter in ret:{} to out ret:{}", ret_in, -100);
        return -100;
    }
    if (WIFEXITED(ret)) {
        // SLOGD("filter in ret:{} to out ret:{}", ret_in, ret);
        return WEXITSTATUS(ret);
    }
    else if (WIFSIGNALED(ret)) {
        SLOGE("filter in ret:{} to out ret:{}", ret_in, -200);
        return -200;
    }
    else {
        SLOGE("filter in ret:{} to out ret:{}", ret_in, -300);
        return -300;
    }
    return -1000;
}

//RecordBackend
RecordBackend::RecordBackend(
    std::function<bool()> is_stop, const std::string& record_cmd
    , const std::string& record_path, const int interval_ms)
    : is_stop_(std::move(is_stop))
    , is_to_stop_(false)
    , interval_ms_(interval_ms)
    , record_cmd_(record_cmd)
    , record_path_(record_path) {
}

RecordBackend::~RecordBackend() {
    to_stop();
    join();
}

void RecordBackend::to_stop() {
    if (is_stop_()) {
        return;
    }
    is_to_stop_.store(true);
}

void RecordBackend::launch() {
    static int static_record_count = 0;
    if (prepare_dir(record_path_)) {
        std::string msg = fmt::format("record target file can't be create, path:{}", record_path_);
        throw std::logic_error(msg);
    }
    thread_back_ = std::thread([&]() {
        static_record_count++;
        SLOGI("enter back thread! run cmd:{}, record path:{}\n", record_cmd_, record_path_);
        int count = 0;
        TimeInterval<> time_interval_total{};
        while (!is_stop_() || is_to_stop_.load()) {
            TimeInterval<> time_interval{};
            // SLOGD("on back thread! count:{}", count++);
            std::string output_str;
            SystemCall sys_call{record_cmd_};
            int ret = sys_call.execute();
            if (!ret) {
                sys_call.get_output_str(output_str);
                // SLOGW("get output str:{}", output_str);
                std::ofstream ofm(record_path_, std::ios::app);
                ofm << output_str << std::endl;
                ofm.close();
            }
            else {
                SLOGD("execute program fail! ret: {}, cmd: {}", ret, sys_call.get_run_cmd());
                break;
            }
            int interval = time_interval.get_interval_ms();
            int redu = interval_ms_ - interval;
            // SLOGW("redu time:{}, interval_ms_:{}, interval:{}", redu, interval_ms_, interval);
            if (redu > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(redu));
            }
        }
        SLOGW("out back thread! run cmd:{}, record path:{}, record count:{}, record interval:{}, static record count:{}\n", record_cmd_, record_path_, count, time_interval_total.get_interval_ms(), static_record_count);
    });
}

void RecordBackend::join() {
    if (thread_back_.joinable()) {
        thread_back_.join();
    }
}

int RecordBackend::prepare_dir(const std::string& target_file) {
    fs::path root_path = fs::path(target_file).parent_path();
    if (!fs::exists(root_path)) {
        try {
            fs::create_directories(root_path);
            SLOGI("create directory path:{}", root_path.string());
        } catch (const std::exception& e) {
            throw std::runtime_error("fail to create directory: " + root_path.string());
        }
    } else {
        #if 0
        for (const auto& entry : fs::directory_iterator(parentPath)) {
            if (fs::is_regular_file(entry) || fs::is_directory(entry)) {
                fs::remove_all(entry.path());
            }
        }
        SLOGW("clean the directory");
        #endif
        if (fs::is_regular_file(target_file)) {
            fs::remove(target_file);
            SLOGW("remove the target file:{}", target_file);
        }
    }
    return 0;
}
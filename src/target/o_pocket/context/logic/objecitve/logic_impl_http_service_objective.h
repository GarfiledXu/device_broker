#pragma once
#include "filesystem_impl.inl"

//task suit
#include "state_suit.h"
#include "task_suit.h"

//custom component
#include "threadpool.hpp"
#include "safe_queue.hpp"
#include "message_bus.hpp"
#include "rabbitmq_handle.h"
#include "message_manager.h"
#include "samba_transfer.h"

//testbed
#include "testbed_param.h"
#include "testbed_cmd_parse.h"
#include "task_status.h"

//ref logic
#include "logic_impl_file_opt.h"

#define COMPONENT_ENABLE 1

using namespace main_service;
using namespace ns;

extern main_service::TaskStatus g_task_state;

class ObjectiveComponentManager {
public:
    friend class RunningLock;

    ~ObjectiveComponentManager() = default;
    static ObjectiveComponentManager& ins() {
        static ObjectiveComponentManager static_ins;
        return static_ins;
    }

    void launch_subtask_monitor();
    TaskSuitBase::TaskReturn reboot();
    TaskSuitBase::TaskReturn objective_update_device_testbed(UpdateTaskInfo update_task_info);
    TaskSuitBase::TaskReturn run_objective(ObjectiveRabbitmqTaskInfo objective_rabbitmq_taskinfo);
    int terminate_objective(TaskObjectiveTerminate terminate_info, bool is_front_or_back);
    bool to_stop_signal();

private:
    ObjectiveComponentManager() = default;

    void set_rabbitmq_info_(const std::string& rabbitmq_js_str);
    void set_samba_info_(const std::string& smb_usr, const std::string& smb_passwd);

    int all_component_load_();
    int all_component_unload_();

    void all_task_end_();
    std::string get_cur_stamp_();
    bool check_msg_serial_to_clean_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg);
    bool is_to_terminate_msg_poll_();
    std::string get_subtask_upload_url(RabbitmqMsgTaskInfo subtask_info);
    void rabbitmq_msg_poll_();
    int cvt_system_return_(int ret); 

    TaskSuitBase::TaskReturn subtask_download_entity_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg);
    TaskSuitBase::TaskReturn subtask_run_entity_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg);
    TaskSuitBase::TaskReturn subtask_upload_entity_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg);

    void terminate_impl_();
    int kill_testbed_progress_(const std::string& process_identify);

    bool subtask_monitor_(ShareTaskInfo<TaskSuitBase::TaskReturn> taskinfo);

    //threadpool: down run upload
    Threadpool<TaskSuitBase::TaskReturn>* threadpool_down = nullptr;
    Threadpool<TaskSuitBase::TaskReturn>* threadpool_run_testbed = nullptr;
    Threadpool<TaskSuitBase::TaskReturn>* threadpool_upload = nullptr;

    MessageBus<int, TaskSuitBase::TaskReturn> message_bus;
    ShareSafeQueue<ShareTaskInfo<TaskSuitBase::TaskReturn>> loop_list;

    MessageManage* rabbimq_msg_mg = nullptr;
    SafeSambaTrasfer* smb_mg = nullptr;

    std::string rabbitmq_js_str_;
    std::string smb_usr_;
    std::string smb_passwd_;

    // bool manage_mq_thread_exit = false;
    bool restartThreadpool = false;
    ObjectiveRabbitmqTaskInfo objective_rabbitmq_taskinfo_;
    std::string objective_rabbitmq_taskinfo_str_;


    int num_init = 0;
    int g_task_end = 0;
    int updated_cnt = 0;
    // int objective_task_id = -1;
    int remain_num_ = 0;

    bool is_running_ = false;
    bool to_task_terminate_ = false;
    bool is_terminating_ = false;
    std::mutex terminate_mtx_;
    std::condition_variable terminate_cv_;

    struct RunningLock
    {
        RunningLock() {

            SLOGW("run_objective running lock");
            ObjectiveComponentManager::ins().is_running_ = true;
            ObjectiveComponentManager::ins().to_task_terminate_ = false;
            
        };
        ~RunningLock() {

            SLOGW("run_objective running unlock, will unload component, notify wait for terminate_cv");

        #if COMPONENT_ENABLE
            ObjectiveComponentManager::ins().all_component_unload_();
        #endif

            ObjectiveComponentManager::ins().is_running_ = false;
            ObjectiveComponentManager::ins().terminate_cv_.notify_all();

        };
    };

};

//block method running on main threadloop
inline TaskSuitBase::TaskReturn ObjectiveComponentManager::run_objective(ObjectiveRabbitmqTaskInfo objective_rabbitmq_taskinfo)
{

    g_task_state.replace_device_state(BUSY);

    TaskSuitBase::TaskReturn task_return;
    task_return.task_type = TASK_RUN_OBJECTIVE;

    g_task_state.replace_device_state(BUSY);
    objective_rabbitmq_taskinfo_ = objective_rabbitmq_taskinfo;

    //init all component
    json js_rabbitmq_info_str = objective_rabbitmq_taskinfo;
    set_rabbitmq_info_(js_rabbitmq_info_str.dump());
    set_samba_info_(objective_rabbitmq_taskinfo.username_smb, objective_rabbitmq_taskinfo.password_smb);
    remain_num_ = objective_rabbitmq_taskinfo_.metrial_number;

    //reset flag and trigger lock
    RunningLock cur_running_lock{};

    //load all componet
    int ret = all_component_load_();
    if (ret) {
        task_return.code_value = ret;
        task_return.code_msg = "all_component_load_ fail";
        return task_return;
    }

    g_task_state.replace_task_state(RABBITMQ_SUCCESS);

    //here, only record error, not throw
    rabbitmq_msg_poll_();


    //indicate task finished, not indicate the task all success
    task_return.code_value = 0;
    task_return.code_msg = "run_objective end";

    g_task_state.replace_task_state(DIVORCED);
    g_task_state.replace_device_state(FREE);

    return task_return;

}

inline int ObjectiveComponentManager::terminate_objective(TaskObjectiveTerminate terminate_info, bool is_front_or_back)
{

#if COMPONENT_ENABLE

    //check taskid
    bool is_same_taskid = true;
    if (objective_rabbitmq_taskinfo_.parent_task_id != terminate_info.task_id) {
        SLOGE("terminate objective wrong, task id not correct, cur taskid:{}, input taskid:{}"
            , objective_rabbitmq_taskinfo_.parent_task_id, terminate_info.task_id);
        return -1;
    }

    //check running
    if (!is_running_) {
        SLOGW("terminating... current post request not effective, no objective is running! but will reset state");
        g_task_state.replace_task_state(DIVORCED);
        g_task_state.replace_device_state(FREE);
        return 0;
    }

    //check if terminating
    if (is_terminating_) {
        SLOGW("terminating... current post request not effective");
        return -3;
    }
    is_terminating_ = true;

    //launch thread
    std::thread terminate_thread = std::thread(
        [&]() {
            terminate_impl_();
            is_terminating_ = false;
        }
    );

    //for join or deteach to implementation front or backend launc thread
    if (terminate_thread.joinable()) {

        //front to block the caller, back will async
        if (is_front_or_back) {
            terminate_thread.join();
        }
        else {
            terminate_thread.detach();
        }

    }

    return 0;

#else

    if (is_front_or_back) {
        SLOGW("terminate_objective start wai");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        SLOGW("terminate_objective end return");
    }
    else {
        SLOGW("terminate_objective return");
        return 0;
    }

#endif

}

inline bool ObjectiveComponentManager::to_stop_signal()
{
    struct tmp_stop {
        tmp_stop(std::condition_variable& incv) : cv(incv) {};
        ~tmp_stop() { cv.notify_all(); SLOGW("to_stop_signal cv to notify all"); };
        std::condition_variable& cv;
    };
    tmp_stop{ terminate_cv_ };
    return SignalHandle::ins().signal_status_SIGINT() || is_running_;
}

inline void ObjectiveComponentManager::launch_subtask_monitor()
{
    //noting to do
}

inline TaskSuitBase::TaskReturn ObjectiveComponentManager::reboot()
{

    int ret = 0;
    std::string cmd = "shutdown -S reboot";
    SLOGW("enter reboot, will call reboot command:[{}]", cmd);

    g_task_state.replace_device_state(BUSY | REBOOTING);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    ret = system(cmd.c_str());
    ret = cvt_system_return_(ret);
    if (ret) {
        SLOGE("error! call reboot fail! command str:[{}]", cmd);
        return TaskSuitBase::TaskReturn{-1, "call reboot command fail", TASK_REBOOT};
    }

    return TaskSuitBase::TaskReturn{-1, "call reboot command fail", TASK_REBOOT};

}

inline TaskSuitBase::TaskReturn ObjectiveComponentManager::objective_update_device_testbed(UpdateTaskInfo update_task_info)
{

    int ret = 0;
    
    ret = update_testbed_and_replace(update_task_info.testbed_pkg_path
        , "/var/TESTBED/testbed_objective", "/var/TESTBED/tmp", {});

    if (ret) {

        SLOGE("update testbed and replace fail! file url: {}, ret: {}", update_task_info.testbed_pkg_path, ret);
        return TaskSuitBase::TaskReturn{-1, "update testbed and replace fail", TASK_UPDATE};

    }

    ret = down_file_and_replace(update_task_info.license_file_url
        , "/var/TESTBED/testbed_objective", "/var/TESTBED/tmp");

    if (ret) {

        SLOGE("update testbed and replace fail! file url: {}, ret: {}", update_task_info.license_file_url, ret);
        return TaskSuitBase::TaskReturn{-2, "update testbed and replace fail", TASK_UPDATE};

        g_task_state.replace_device_state(LICENSE_CHECK_FAIL);
        g_task_state.replace_task_state(DIVORCED);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        g_task_state.replace_device_state(FREE | UPDATED | LICENSE_CHECK_FAIL | UPDATE_FAIL);

    }

    g_task_state.replace_device_state(FREE | UPDATED | UPDATE_SUCCESS);
    g_task_state.replace_task_state(DIVORCED);

    return TaskSuitBase::TaskReturn{0, "update testbed and replace success", TASK_UPDATE};

}
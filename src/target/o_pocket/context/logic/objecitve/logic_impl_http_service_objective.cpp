#include "logic_impl_http_service_objective.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

extern main_service::TaskStatus g_task_state(STATE_TASK::DIVORCED, STATE_DEVICE::FREE);

void ObjectiveComponentManager::set_rabbitmq_info_(const std::string& rabbitmq_js_str)
{
    rabbitmq_js_str_ = rabbitmq_js_str;
    return;
}

void ObjectiveComponentManager::set_samba_info_(const std::string& smb_usr, const std::string& smb_passwd)
{
    smb_usr_ = smb_usr;
    smb_passwd_ = smb_passwd;
    return;
}

int ObjectiveComponentManager::all_component_load_()
{

#if COMPONENT_ENABLE

    try{

        if (NULL == threadpool_down) {
            threadpool_down = new Threadpool<TaskSuitBase::TaskReturn>(1, 3, nullptr, "thread down update", nullptr);;
            threadpool_down->bind_monitor_list(loop_list);
            threadpool_down->start_workers();
        }

        if (NULL == threadpool_run_testbed) {
            threadpool_run_testbed = new Threadpool<TaskSuitBase::TaskReturn>(1, 2, nullptr, "thread run testbed", nullptr);
            threadpool_run_testbed->bind_monitor_list(loop_list);
            threadpool_run_testbed->start_workers();
        }

        if (NULL == threadpool_upload) {
            threadpool_upload = new Threadpool<TaskSuitBase::TaskReturn>(1, 3, nullptr, "thread upload", nullptr);
            threadpool_upload->bind_monitor_list(loop_list);
            threadpool_upload->start_workers();
        }

        RabbitMQHandler my_mq(rabbitmq_js_str_);
        if(my_mq.state()){
            SLOGE("RabbitMQHandler init fail");
            g_task_state.replace_device_state(FREE);
            g_task_state.replace_task_state(RABBITMQ_FAIL);
            throw std::logic_error("rabbitmq handle init fail!");
        }

        rabbimq_msg_mg = new MessageManage(&my_mq, NULL, 5);

        smb_mg = new SafeSambaTrasfer(smb_usr_, smb_passwd_);

    }
    catch (std::exception& e) {

        SLOGE("all_component_load_ fail! what:{}", e.what());
        return -1;

    }

    return 0;

#else

    return 0;

#endif
}

int ObjectiveComponentManager::all_component_unload_()
{
    #if 0

    threadpool_down->wait_task_empty_shutdown();
    threadpool_run_testbed->wait_task_empty_shutdown();
    threadpool_upload->wait_task_empty_shutdown();

    if (threadpool_down) {
        delete threadpool_down;
        threadpool_down = nullptr;
    }
    if (threadpool_run_testbed) {
        delete threadpool_run_testbed;
        threadpool_run_testbed = nullptr;
    }
    if (threadpool_upload) {
        delete threadpool_upload;
        threadpool_upload = nullptr;
    }

    if (rabbimq_msg_mg) {
        delete rabbimq_msg_mg;
        rabbimq_msg_mg = nullptr;
    }
    if (smb_mg) {
        delete smb_mg;
        smb_mg = nullptr;
    }

    return 0;
    #else
    return 0;

    #endif

}

void ObjectiveComponentManager::all_task_end_()
{
    g_task_state.is_contain_task_state(RABBITMQ_END);

    json js_return_root;
    js_return_root["code"] = 0;
    js_return_root["msg"] = std::to_string(objective_rabbitmq_taskinfo_.parent_task_id);

    json js_sub_content;
    js_sub_content["content"] = "end";
    js_return_root["data"] = js_sub_content;
    
    int res = rabbimq_msg_mg->Put("end", js_return_root.dump().c_str());

    SW_FF(REC_MQ_MSG,
        "type:send mq, task_id:{}, res:{}, msg:{}, stamp:{}",
                            objective_rabbitmq_taskinfo_.parent_task_id, res, js_return_root.dump(), get_cur_stamp_());
    SLOGI("成功上传{}个结果, 失败{}个,一共{}个", updated_cnt, num_init - updated_cnt, num_init);

    g_task_state.replace_task_state(RABBITMQ_END);
    g_task_state.replace_device_state(FREE);
}

std::string ObjectiveComponentManager::get_cur_stamp_()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), "%Y-%m-{} %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

//return true, mean the last task
bool ObjectiveComponentManager::check_msg_serial_to_clean_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg)
{

    bool is_last_task = false;

    // 如果当前的msg是最后一个，就修改状态码，移除所有素材产生的文件
    testbed_param param(subtask_msg);
    if(g_task_end == num_init){

        g_task_state.replace_task_state(RABBITMQ_END);
        g_task_state.replace_device_state(FREE);

        SLOGD("mq end, execute msg number : {}", objective_rabbitmq_taskinfo_.metrial_number);
        SLOGI("delete mq metrial dir\n");

        FsImpl::clean_folder(param.get_metrial_dir());

        is_last_task = true;
        return is_last_task;
    }

    is_last_task = false;
    return is_last_task;

}

bool ObjectiveComponentManager::is_to_terminate_msg_poll_()
{
    return remain_num_ < 1 || to_task_terminate_;
}

std::string ObjectiveComponentManager::get_subtask_upload_url(RabbitmqMsgTaskInfo subtask_info)
{
    return subtask_info.upload_result_dir_path;
}

//only record error, not throw
void ObjectiveComponentManager::rabbitmq_msg_poll_()
{

#if COMPONENT_ENABLE
    // enable rabbitmq
    rabbimq_msg_mg->Start();
    rabbimq_msg_mg->enable();

    while (!is_to_terminate_msg_poll_()) {

        //second param if equal 1, mean block take
        std::string cur_subtask_msg = "";
        int ret = rabbimq_msg_mg->Get(cur_subtask_msg, 0);

        g_task_state.replace_task_state(RABBITMQ_ING);

        if (cur_subtask_msg == "" || ret != 0) {
            continue;
        }

        remain_num_--;
        try {
            json js_root = json::parse(cur_subtask_msg);

            RabbitmqMsgTaskInfo cur_subtask_info{js_root};

            js_root["upload_result_dir_path"] = get_subtask_upload_url(cur_subtask_info);
            SW_FF(REC_MQ_MSG,
                "type:receive mq, task_id:{}, sub_id:{}, msg:{}, stamp:{}",
                    cur_subtask_info.parent_task_id, cur_subtask_info.msg_id, js_root.dump(), get_cur_stamp_());

            std::string tag = fmt::format("parent_id:{:<5} sub_task_id:{:<5} task_type:{:<15}", cur_subtask_info.parent_task_id, cur_subtask_info.msg_id, "down_metiral");                        
            threadpool_down->enqueue_task_sync([=] () {
                    return subtask_download_entity_(cur_subtask_info, cur_subtask_msg);
                }, 1, tag);
        }
        catch (std::exception& e) {
            SLOGE("parse rabbitmq message to json, fail! msg:{}, error content:{}", cur_subtask_msg, e.what());
            continue;
        }

    }

    return;

#else

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    return;

#endif

}

int ObjectiveComponentManager::cvt_system_return_(int ret)
{

    if (-1 == ret) {
        SLOGE(" system() call ,cmd subprocess launched fail!\n");
        return -100;
    }
    if (WIFEXITED(ret)) {
        SLOGI(" system() call, cmd subprocess normally exited, exit status ret:{}", WEXITSTATUS(ret));
        return WEXITSTATUS(ret);
    }
    else if (WIFSIGNALED(ret)) {
        SLOGE(" system() call, cmd subprocess abnormally exited, signal number:{}", WTERMSIG(ret));
        return -200;
    }
    else {
        SLOGE(" system() call, cmd subprocess abnormally exited, can't analysis return ret:{}", ret);
        return -300;
    }

    return 0;

}

TaskSuitBase::TaskReturn ObjectiveComponentManager::subtask_download_entity_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg)
{
    SLOGD("{}", fmt::format("enter subtask_download_entity_, parent task id:{}, sub task id:{}", subtask_info.parent_task_id, subtask_info.msg_id).c_str());
    
    testbed_param param(objective_rabbitmq_taskinfo_str_);

    json js_subtask_return_message;
    json js_addtion_data;

    int ret;
    for (int i = 0;i < 3;i++) {  
        ret = smb_mg->DownloadOne(param.get_metrial_path_url(), param.get_metrial_path());
        if (!ret) break;
        sleep(1);
        SLOGE("smb download fail, ret:{}, count:{}", ret, i);
    }

    TaskSuitBase::TaskReturn taskreturn;
    taskreturn.code_value = ret; 
    js_subtask_return_message["code"] = taskreturn.code_value;
    taskreturn.task_type = TASK_TYPE_SUB_DOWN;

    // 根据任务返回码，发送对应的msg
    if (taskreturn.code_value != 0){
        
        js_subtask_return_message["msg"] = "fail";
        js_addtion_data["content"] = "smb download fail";
        js_addtion_data["metrial_path_url"] = param.get_metrial_path_url();
        js_subtask_return_message["data"] = js_addtion_data;

        SLOGD("enter rabbimq_msg_mg put");
        int res = rabbimq_msg_mg->Put(subtask_msg, js_subtask_return_message.dump().c_str());// Singleton<MessageManage>::GetInstance().Put(msg, js_subtask_return_message.dump().c_str());
        SLOGD("out rabbimq_msg_mg put");

        string str = fmt::format("type:send mq, task_id:{}, sub_id:{}, res:{}, msg:{}, stamp:{}\n",
                    subtask_info.parent_task_id, subtask_info.msg_id, res, js_subtask_return_message.dump(), get_cur_stamp_());
        SW_FF(REC_MQ_MSG, "{}", str);
        
        g_task_end++;
        check_msg_serial_to_clean_(subtask_info, subtask_msg);
        taskreturn.code_msg = "smb download fail";
        return taskreturn;

    } else{ 

        updated_cnt++;
        js_subtask_return_message["msg"] = "success";
        js_addtion_data["content"] = "non";
        js_addtion_data["metrial_path_url"] = param.get_metrial_path_url();
        js_subtask_return_message["data"] = js_addtion_data;

        int res = rabbimq_msg_mg->Put(subtask_msg, js_subtask_return_message.dump().c_str());// Singleton<MessageManage>::GetInstance().Put(msg, js_subtask_return_message.dump().c_str());
        string str = fmt::format("type:send mq, task_id:{}, sub_id:{}, res:{}, msg:{}, stamp:{}\n",
                    subtask_info.parent_task_id, subtask_info.msg_id, res, js_subtask_return_message.dump(), get_cur_stamp_());
        SW_FF(REC_MQ_MSG, "{}", str);

    }
    SLOGI("g_task_end: {}", g_task_end);

    std::string tag = fmt::format("parent_id:{:<5} sub_task_id:{:<5} task_type:{:<15}", subtask_info.parent_task_id, subtask_info.msg_id, "download");        
    threadpool_run_testbed->enqueue_task_sync([=]() {
        return subtask_run_entity_(subtask_info, subtask_msg);
    }, 0, tag);

    SLOGI("out subtask_download_entity_!\n");
    taskreturn.code_msg = "smb download success";

    return taskreturn;
}

TaskSuitBase::TaskReturn ObjectiveComponentManager::subtask_run_entity_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg)
{
    SLOGD("{}", fmt::format("enter subtask_run_entity_, parent task id:{}, sub task id:{}", subtask_info.parent_task_id, subtask_info.msg_id).c_str());
    
    testbed_param param(objective_rabbitmq_taskinfo_str_);

    json js_subtask_return_message;
    json js_addtion_data;

    int ret;
    for (int i = 0;i < 10;i++) {  
        ret = cvt_system_return_(system(param.get_run_cmd().c_str()));  
        if (!ret)
            break;

        std:this_thread::sleep_for(std::chrono::milliseconds(300));
        SLOGE("run testbed fail, ret:{}, count:{}", ret, i);
    }

    TaskSuitBase::TaskReturn taskreturn;
    taskreturn.code_value = ret; 
    js_subtask_return_message["code"] = taskreturn.code_value;
    taskreturn.task_type = TASK_TYPE_SUB_RUNNING;

    // 根据任务返回码，发送对应的msg
    if (taskreturn.code_value != 0){
        
        js_subtask_return_message["msg"] = "fail";
        js_addtion_data["content"] = "testbed run fail";
        js_addtion_data["metrial_path_url"] = param.get_metrial_path_url();
        js_subtask_return_message["data"] = js_addtion_data;

        SLOGD("enter rabbimq_msg_mg put");
        int res = rabbimq_msg_mg->Put(subtask_msg, js_subtask_return_message.dump().c_str());// Singleton<MessageManage>::GetInstance().Put(msg, js_subtask_return_message.dump().c_str());
        SLOGD("out rabbimq_msg_mg put");

        string str = fmt::format("type:send mq, task_id:{}, sub_id:{}, res:{}, msg:{}, stamp:{}\n",
                    subtask_info.parent_task_id, subtask_info.msg_id, res, js_subtask_return_message.dump(), get_cur_stamp_());
        SW_FF(REC_MQ_MSG, "{}", str);

        g_task_end++;
        check_msg_serial_to_clean_(subtask_info, subtask_msg);
        taskreturn.code_msg = "run testbed fail";
        return taskreturn;

    } else{ 

        updated_cnt++;
        js_subtask_return_message["msg"] = "success";
        js_addtion_data["content"] = "non";
        js_addtion_data["metrial_path_url"] = param.get_metrial_path_url();
        js_subtask_return_message["data"] = js_addtion_data;

        int res = rabbimq_msg_mg->Put(subtask_msg, js_subtask_return_message.dump().c_str());// Singleton<MessageManage>::GetInstance().Put(msg, js_subtask_return_message.dump().c_str());
        string str = fmt::format("type:send mq, task_id:{}, sub_id:{}, res:{}, msg:{}, stamp:{}\n",
                    subtask_info.parent_task_id, subtask_info.msg_id, res, js_subtask_return_message.dump(), get_cur_stamp_());
        SW_FF(REC_MQ_MSG, "{}", str);

    }
    SLOGI("g_task_end: {}", g_task_end);

    std::string tag = fmt::format("parent_id:{:<5} sub_task_id:{:<5} task_type:{:<15}", subtask_info.parent_task_id, subtask_info.msg_id, "run testbed");        
    threadpool_run_testbed->enqueue_task_sync([=]() {
        return subtask_upload_entity_(subtask_info, subtask_msg);
    }, 0, tag);

    taskreturn.code_msg = "run testbed success";
    SLOGI("out subtask_download_entity_!\n");

    return taskreturn;
}

TaskSuitBase::TaskReturn ObjectiveComponentManager::subtask_upload_entity_(RabbitmqMsgTaskInfo subtask_info, const std::string& subtask_msg)
{
    SLOGD("{}", fmt::format("enter func_task_upload, parent task id:{}, sub task id:{}", subtask_info.parent_task_id, subtask_info.msg_id).c_str());
    
    testbed_param param(objective_rabbitmq_taskinfo_str_);

    json js_subtask_return_message;
    json js_addtion_data;

    int ret;
    for (int i = 0;i < 3;i++) {  
        ret = smb_mg->UploadAll(param.get_upload_result_dir_path(), param.get_result_dir_path()); 
        if (!ret) break;
        sleep(1);
        SLOGE("UploadAll fail, ret:{}, count:{}", ret, i);
    }

    TaskSuitBase::TaskReturn taskreturn;
    taskreturn.code_value = ret; 
    js_subtask_return_message["code"] = taskreturn.code_value;
    taskreturn.task_type = TASK_TYPE_UPLOAD;

    // 根据任务返回码，发送对应的msg
    if (taskreturn.code_value != 0){
        
        js_subtask_return_message["msg"] = "fail";
        js_addtion_data["content"] = "testbedRun upload fail";
        js_addtion_data["metrial_path_url"] = param.get_metrial_path_url();
        js_subtask_return_message["data"] = js_addtion_data;

        SLOGD("enter rabbimq_msg_mg put");
        int res = rabbimq_msg_mg->Put(subtask_msg, js_subtask_return_message.dump().c_str());// Singleton<MessageManage>::GetInstance().Put(msg, js_subtask_return_message.dump().c_str());
        SLOGD("out rabbimq_msg_mg put");

        string str = fmt::format("type:send mq, task_id:{}, sub_id:{}, res:{}, msg:{}, stamp:{}\n",
                    subtask_info.parent_task_id, subtask_info.msg_id, res, js_subtask_return_message.dump(), get_cur_stamp_());
        SW_FF(REC_MQ_MSG, "{}", str);

        g_task_end++;
        check_msg_serial_to_clean_(subtask_info, subtask_msg);
        taskreturn.code_msg = "result upload fail";
        return taskreturn;

    } else{ 

        updated_cnt++;
        js_subtask_return_message["msg"] = "success";
        js_addtion_data["content"] = "non";
        js_addtion_data["metrial_path_url"] = param.get_metrial_path_url();
        js_subtask_return_message["data"] = js_addtion_data;

        int res = rabbimq_msg_mg->Put(subtask_msg, js_subtask_return_message.dump().c_str());// Singleton<MessageManage>::GetInstance().Put(msg, js_subtask_return_message.dump().c_str());
        string str = fmt::format("type:send mq, task_id:{}, sub_id:{}, res:{}, msg:{}, stamp:{}\n",
                    subtask_info.parent_task_id, subtask_info.msg_id, res, js_subtask_return_message.dump(), get_cur_stamp_());
        SW_FF(REC_MQ_MSG, "{}", str);
        
    }

    g_task_end++;
    SLOGI("g_task_end: {}", g_task_end);

    check_msg_serial_to_clean_(subtask_info, subtask_msg);
    taskreturn.code_msg = "upload success";

    SLOGI("out func_task_upload!\n");
    return taskreturn;

}

void ObjectiveComponentManager::terminate_impl_()
{
    //kill testbed
    std::string kill_name1 = "TESTBED_MAIN";
    std::string kill_name2 = "TESTBED_PLATFORM";

    try {
        kill_testbed_progress_(kill_name1);
        kill_testbed_progress_(kill_name2);
    }
    catch (std::exception& e) {
        SLOGE("kill testbed cache the error, what:{}, kill name1:{}, kill name2:{}", e.what(), kill_name1, kill_name2);
    }
    SLOGW("start stop mq thread");
    
    // trigger stop get msg from rabbitmq, and post lambda task
    to_task_terminate_ = true;
    
    // just wait for run thread finished or receive kill signal to notify
    SLOGW("start wait for run objective finished");
    {
        std::unique_lock<std::mutex> lock(terminate_mtx_);
        terminate_cv_.wait(lock,
            [&] {return !is_running_ || to_stop_signal();}
        );
    }

    //g state update
    g_task_state.replace_task_state(DIVORCED);
    g_task_state.replace_device_state(FREE);

    SLOGI("end wait for run objective finished");
    return;

}

int ObjectiveComponentManager::kill_testbed_progress_(const std::string& process_identify){
    std::string cmd_out;
    std::string cmd = "hogs -i 1 | grep " + process_identify;
    SLOGI("task kill run: {}", cmd.c_str());

    // 获取命令返回值
    std::array<char, 256> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        SLOGE("error! query process hogs info fail!");
        return -1;
        //throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        cmd_out += buffer.data();
    }
    if (cmd_out.empty()) {
        SLOGI("now have no TESTBED_MAIN process!");
        return 0;
    }
    auto get_pid_vec = [](const std::string& cmd_out)->std::vector<int> {
        std::vector<std::string> ret_vec;
        std::vector<int> vec_pid;
        int idx = 0;
        std::string line;
        char c_last;
        for (int i = 0;i < cmd_out.size();i++) {
            //printf("cmd_out iterator:%d, %c\n", i, cmd_out[i]);
            char c_cur = cmd_out[i];
            line.push_back(c_cur);
            if ((c_cur=='\n')){
                ret_vec.push_back(line);
                line.clear();
                c_last = c_cur;
                continue;
            }    
            c_last = c_cur;
        }
        for (auto& itm : ret_vec) {
            
            int pid = -1;
            std::string pid_str;
            char c_last=' ';
            for (int i = 0;i < itm.size();i++) {
                char c = itm[i];
                if (isdigit(c_last) && (c == ' ')) 
                    break;
                if (isdigit(c)) 
                    pid_str.push_back(c);
                c_last = c;
            }
            printf("pid:%d correspond:%s\n", std::stoi(pid_str), itm.c_str());
            // printf("%s get pid int:%d \n", itm.c_str(), std::stoi(pid_str));
            vec_pid.push_back(std::stoi(pid_str));
        }
        return vec_pid;
    };
    std::vector<int> vec_query = get_pid_vec(cmd_out);
    //loop kill
    for (auto& query_ret : vec_query) {
        SLOGI("kill process:{}", query_ret);
        std::string cmd = "kill " + std::to_string(query_ret);
        int ret = system(cmd.c_str());
        ret = cvt_system_return_(ret);
        if (ret) {
            // SLOGE("kill error!\n");
            return -3;
        }
    }
    return 0;
}

using namespace main_service;
using TASK = std::function<TaskSuitBase::TaskReturn()>;

inline bool ObjectiveComponentManager::subtask_monitor_(ShareTaskInfo<TaskSuitBase::TaskReturn> taskinfo)
{
    bool is_erase = false;
    auto timer = taskinfo->get_timer();
    auto future = taskinfo->get_future();
    
    SLOGW(
        "get message:{} "
        "get elapsed ms:{} "
        "get elapsed end ms:{} "
        "get obj serial:{} "
        "get obj count:{} "
        "is end:{} ",
        taskinfo->get_tag().c_str(),
        timer->get_elapsed_ms(),
        timer->get_end_elapsed_ms(),
        taskinfo->get_obj_serial(),
        taskinfo->get_obj_count(),
        timer->is_end()
        );

    if (timer->is_end()) {
        //fetach task return value
        unsigned long task_obj_serial = taskinfo->get_obj_serial();
        try{
            TaskSuitBase::TaskReturn ret = future.get();
            SW_FF(REC_TASK_RESULT,"{} ret:{:<5} duration:{:<10} stamp:{}\n\n", taskinfo->get_tag(), ret.code_value, timer->get_end_elapsed_ms(), get_cur_stamp_())
        }
        catch (std::exception& e) {
            SLOGE("task catch: {}, task obj serial:{}", e.what(), task_obj_serial);
            SLOGI("end exception!");
        }
    }
    // return is_erase;
    return timer->is_end();
}


#include "http_service_handle_objective.h"
#include "threadloop_objective.h"
#include "http_file_opt_request.h"

static std::vector<MatchItem> g_vec_match_item =
{
    {"/device_service/device/status", "", handle_status},
    {"/device_service/update/testbed_metiral", "", handle_update},
    {"/device_service/task/terminate", "", handle_terminate},
    {"/handler_rabbitmq_info", "", handle_run_objective},
    {"/device_service/log", "", handle_log},
    {"/device_service/test", "", handle_test},
    {"/device_service/file_opt/file_pull", "", handle_file_pull},
    {"/device_service/file_opt/file_clear", "", handle_file_clear},
};

void http_server_objective_callback(struct mg_connection* c, int ev, void* ev_data)
{
    if (ev == MG_EV_HTTP_MSG) {

        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        RequestInfo tmp_request_info;
        ResponseInfo tmp_reponse_info{ 0, "", "" };
        request_info_load(tmp_request_info, hm, c);

        int icx = 0;
        for (auto& cur_match_item : g_vec_match_item) {
            bool is_match = true;
            icx++;

            if (((cur_match_item.uri != "") && ((cur_match_item.uri) != tmp_request_info.uri))
                || ((cur_match_item.method != "") && ((cur_match_item.method) != tmp_request_info.method)) ){
                is_match = false;
            }
            if (is_match && cur_match_item.handle != nullptr) {
                cur_match_item.handle(tmp_request_info, tmp_reponse_info);
                mg_http_reply(c, tmp_reponse_info.errcode, tmp_reponse_info.header.c_str(), tmp_reponse_info.body.c_str());
                break;
            }
        }

    }
    return ;
}

static void handle_status(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_status");
    TimeInterval<> time_interval_total{};
    std::string addtion_err_msg = "";
    int post_ret = 0;
    int response_code = 0;
    int cur_task_id = -1;
    std::string response_code_msg = "success";

    try {
        
        json js_request_body = json::parse(request_info.body);
        ns::TaskDeviceState task_info =  js_request_body ; 

        cur_task_id = task_info.task_id;
        
        //post lambda
        SLOGI("enter post task, type:{}", (int)TASK_REBOOT);

        if (task_info.reboot) {
        
            post_ret = ThreadloopObjectiveFSM::ins().task_suit()->post_task(TASK_REBOOT,
                [=]() -> TaskSuitBase::TaskReturn {
                    return ObjectiveComponentManager::ins().reboot();
            });
        
            if (post_ret) {
                response_code = -1;
                response_code_msg = "fail";
            }

        }
        
        SLOGI("out post task, type:{}, cost time:{}", (int)TASK_UPDATE, time_interval_total.get_interval_ms());
    }
    catch (std::exception& e) {
        SLOGE("handle update, parse json fail! what:{}, request data body:{}", e.what(), request_info.body);
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    
    json js_response_body = {
        {"code", response_code},
        {"data", {
            ns::TaskDeviceStateResponse{
                g_task_state.get_device_state(), g_task_state.get_device_state_str()
                , cur_task_id, g_task_state.get_task_state(), g_task_state.get_task_state_str()
                , "adddtion_err_msg", response_code
            }
        }
        },
        {"msg", response_code_msg}
    };

    return_reponse.body = js_response_body.dump(4);
}

static void handle_update(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_update");
    TimeInterval<> time_interval_total{};
    std::string addtion_err_msg = "";
    int post_ret = 0;
    int response_code = 0;
    std::string response_code_msg = "success";
    int cur_task_id = -1;

    try {
        json js_request_body = json::parse(request_info.body);
        ns::UpdateTaskInfo task_info = js_request_body;

        cur_task_id = task_info.task_id;

        //post lambda
        SLOGI("enter post task, type:{}", (int)TASK_UPDATE);

        post_ret = ThreadloopObjectiveFSM::ins().task_suit()->post_task(TASK_UPDATE,
            [=]() -> TaskSuitBase::TaskReturn {
                return ObjectiveComponentManager::ins().objective_update_device_testbed(task_info);
            });

        if (post_ret) {
            response_code = -1;
            response_code_msg = "fail";
        }
        else {
            g_task_state.replace_device_state(BUSY|UPDATINTG);
            g_task_state.replace_task_state(RUNNING);
        }

        SLOGI("out post task, type:{}, cost time:{}", (int)TASK_UPDATE, time_interval_total.get_interval_ms());
    }
    catch (std::exception& e) {
        SLOGE("handle update, parse json fail! what:{}", e.what());
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    
    json js_response_body = {
        {"code", response_code},
        {"data", {
            ns::TaskDeviceStateResponse{
                g_task_state.get_device_state(), g_task_state.get_device_state_str()
                , cur_task_id, g_task_state.get_task_state(), g_task_state.get_task_state_str()
                , "adddtion_err_msg", response_code
            }
        }
        },
        {"msg", response_code_msg}
    };

    return_reponse.body = js_response_body.dump(4);

}


static void handle_file_pull(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_file_pull");
    TimeInterval<> time_interval_total{};
    std::string addtion_err_msg = "";
    int post_ret = 0;
    int response_code = 0;
    std::string response_code_msg = "success";
    int cur_task_id = -1;

    try {
        json js_request_body = json::parse(request_info.body);
        ns::TaskFileOperation_FilePull task_info = js_request_body;

        cur_task_id = task_info.task_id;

        //post lambda
        SLOGI("enter post task, type:{}", (int)TASK_FILE_OPT_FILE_PULL);

        post_ret = ThreadloopObjectiveFSM::ins().task_suit()->post_task(TASK_FILE_OPT_FILE_PULL,
            [=]() -> TaskSuitBase::TaskReturn {
                TaskSuitBase::TaskReturn cur_return = file_operation_file_pull(task_info);
                if (cur_return.code_value) {
                    g_task_state.replace_device_state(FREE|FILE_PULL_FAIL);
                    g_task_state.replace_task_state(FREE);
                }
                else {
                    g_task_state.replace_device_state(FREE|FILE_PULL_SUCCESS);
                    g_task_state.replace_task_state(FREE);
                }
                
                return cur_return;
            });

        if (post_ret) {
            response_code = -1;
            response_code_msg = "fail";
            g_task_state.replace_device_state(BUSY|FILE_PULL_FAIL);
        }
        else {
            g_task_state.replace_device_state(BUSY|FILE_PULL);
            g_task_state.replace_task_state(RUNNING);
        }

        SLOGI("out post task, type:{}, cost time:{}", (int)TASK_UPDATE, time_interval_total.get_interval_ms());
    }
    catch (std::exception& e) {
        SLOGE("handle update, parse json fail! what:{}", e.what());
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    
    json js_response_body = {
        {"code", response_code},
        {"data", {
            ns::TaskDeviceStateResponse{
                g_task_state.get_device_state(), g_task_state.get_device_state_str()
                , cur_task_id, g_task_state.get_task_state(), g_task_state.get_task_state_str()
                , "adddtion_err_msg", response_code
            }
        }
        },
        {"msg", response_code_msg}
    };

    return_reponse.body = js_response_body.dump(4);

}

static void handle_file_clear(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_file_clear");
    TimeInterval<> time_interval_total{};
    std::string addtion_err_msg = "";
    int post_ret = 0;
    int response_code = 0;
    std::string response_code_msg = "success";
    int cur_task_id = -1;

    try {
        json js_request_body = json::parse(request_info.body);
        ns::TaskFileOperation_FileClear task_info = js_request_body;

        cur_task_id = task_info.task_id;

        //post lambda
        SLOGI("enter post task, type:{}", (int)TASK_FILE_OPT_FILE_CLEAR);

        post_ret = ThreadloopObjectiveFSM::ins().task_suit()->post_task(TASK_FILE_OPT_FILE_CLEAR,
            [=]() -> TaskSuitBase::TaskReturn {
                TaskSuitBase::TaskReturn cur_return = file_operation_file_clear(task_info);
                if (cur_return.code_value) {
                    g_task_state.replace_device_state(FREE|FILE_CLEAR_FAIL);
                    g_task_state.replace_task_state(FREE);
                }
                else {
                    g_task_state.replace_device_state(FREE|FILE_CLEAR_SUCCESS);
                    g_task_state.replace_task_state(FREE);
                }
                
                return cur_return;
            });

        if (post_ret) {
            response_code = -1;
            response_code_msg = "fail";
            g_task_state.replace_device_state(BUSY|FILE_CLEAR_FAIL);
        }
        else {
            g_task_state.replace_device_state(BUSY|FILE_CLEAR);
            g_task_state.replace_task_state(RUNNING);
        }

        SLOGI("out post task, type:{}, cost time:{}", (int)TASK_UPDATE, time_interval_total.get_interval_ms());
    }
    catch (std::exception& e) {
        SLOGE("handle update, parse json fail! what:{}", e.what());
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    
    json js_response_body = {
        {"code", response_code},
        {"data", {
            ns::TaskDeviceStateResponse{
                g_task_state.get_device_state(), g_task_state.get_device_state_str()
                , cur_task_id, g_task_state.get_task_state(), g_task_state.get_task_state_str()
                , "adddtion_err_msg", response_code
            }
        }
        },
        {"msg", response_code_msg}
    };

    return_reponse.body = js_response_body.dump(4);

}

static void handle_terminate(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_terminate");
    std::string addtion_err_msg = "";
    int response_code = 0;
    int cur_task_id = -1;
    std::string response_code_msg = "success";

    try {
        json js_request_body = json::parse(request_info.body);
        ns::TaskObjectiveTerminate task_info = js_request_body; 

        cur_task_id = task_info.task_id;

        //post lambda
        SLOGI("enter post task, type:{}", (int)TASK_RUN_OBJECTIVE);

        int ret = ObjectiveComponentManager::ins().terminate_objective(task_info, false);
        if (ret) {
            response_code = -1;
            response_code_msg = "fail";
        }

        SLOGI("out post task, type:{}", (int)TASK_RUN_OBJECTIVE);
    }
    catch (std::exception& e) {
        SLOGE("handle_terminate, parse json fail! what:{}", e.what());
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    

    json js_response_body = {
        {"code", response_code},
        {"data", {
            ns::TaskDeviceStateResponse{
                g_task_state.get_device_state(), g_task_state.get_device_state_str()
                , cur_task_id, g_task_state.get_task_state(), g_task_state.get_task_state_str()
                , "adddtion_err_msg", response_code
            }
        }
        },
        {"msg", response_code_msg}
    };

    return_reponse.body = js_response_body.dump(4);

}

static void handle_run_objective(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_run_objective");
    SLOGD("enter handle: handle_update");
    TimeInterval<> time_interval_total{};
    std::string addtion_err_msg = "";
    int post_ret = 0;
    int response_code = 0;
    int cur_task_id = -1;
    std::string response_code_msg = "success";

    try {
        
        json js_request_body = json::parse(request_info.body);
        ns::ObjectiveRabbitmqTaskInfo task_info = js_request_body;

        cur_task_id = task_info.parent_task_id;
        
        SLOGI("enter post task, type:{}", (int)TASK_RUN_OBJECTIVE);
        
        post_ret = ThreadloopObjectiveFSM::ins().task_suit()->post_task(TASK_RUN_OBJECTIVE,
            [=]() -> TaskSuitBase::TaskReturn {
                return ObjectiveComponentManager::ins().run_objective(task_info);
            });

        SLOGI("out post task, type:{}", (int)TASK_RUN_OBJECTIVE);

        if (post_ret) {
            response_code = -1;
            response_code_msg = "fail";
        }

        SLOGI("out post task, type:{}, cost time:{}", (int)TASK_UPDATE, time_interval_total.get_interval_ms());
    }
    catch (std::exception& e) {
        SLOGE("handle update, parse json fail! what:{}, request body:{}", e.what(), request_info.body);
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    
    json js_response_body = {
        {"code", response_code},
        {"data", {
            ns::TaskDeviceStateResponse{
                g_task_state.get_device_state(), g_task_state.get_device_state_str()
                , cur_task_id, g_task_state.get_task_state(), g_task_state.get_task_state_str()
                , "adddtion_err_msg", response_code
            }
        }
        },
        {"msg", response_code_msg}
    };

    return_reponse.body = js_response_body.dump(4);

}

static void handle_log(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_log");
}

static void handle_test(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_test");
}
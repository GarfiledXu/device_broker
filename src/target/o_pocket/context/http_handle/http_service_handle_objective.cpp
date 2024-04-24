#include "http_service_handle_objective.h"
#include "state_mgr.h"

static std::vector<MatchItem> g_vec_match_item =
{
    {"/device_service/device/status", "", handle_status},
    {"/device_service/update/testbed_metiral", "", handle_update},
    {"/device_service/task/terminate", "", handle_terminate},
    {"/handler_rabbitmq_info", "", handle_run_objective},
    {"/device_service/log", "", handle_log},
    {"/device_service/test", "", handle_test},
};

// void http_server_objective_callback(struct mg_connection* c, int ev, void* ev_data);
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
}

static void handle_update(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_update");
    std::string addtion_err_msg = "";
    try {
        json js_request_body = json::parse(request_info.body);
        ns::UpdateTaskInfo task_info{ js_request_body }; 

        #if 0
        SLOGD("json str dump:{}, \ntask_id:{}, testbed_pkg_path:{}, metiral_pkg_path:{}, license_file_url:{}, testbed_type:{}, ip:{}, createdTime:{}",
            js_request_body.dump(4),
            task_info.task_id, task_info.testbed_pkg_path, task_info.metiral_pkg_path, task_info.license_file_url, task_info.testbed_type, task_info.ip, task_info.createdTime);
        #endif

        //post
        // StateMgr::ins().post_task_info(TASK_UPDATE, task_info);
        // StateMgr::ins().post_task(100);
        SLOGW("enter post task, type:{}", (int)TASK_UPDATE);
        ThreadloopObjectiveFSM::ins().task_suit()->post_task(TASK_UPDATE,
            []() -> TaskSuitBase::TaskReturn {
                SLOGI("enter call task update 5000 ms");
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                SLOGI("out call task update 5000 ms");
            });
        SLOGW("out post task, type:{}", (int)TASK_UPDATE);
    }
    catch (std::exception& e) {
        SLOGE("handle update, parse json fail! what:{}", e.what());
        return_reponse.errcode = 200;
        addtion_err_msg = e.what();
    }
    

    json js_response_body = ns::TaskResponse{
            10, "device_status_msg", 200, -10, "task_status_msg", "adddtion_err_msg"
    };
}

static void handle_terminate(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_terminate");
}

static void handle_run_objective(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_run_objective");
}

static void handle_log(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_log");
}

static void handle_test(const RequestInfo& request_info, ResponseInfo& return_reponse)
{
    SLOGD("enter handle: handle_test");
}
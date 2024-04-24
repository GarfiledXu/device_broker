#pragma once
#include "http_server.h"
#include "http_handler.h"
#include "json.hpp"
using json = nlohmann::json;

namespace ns
{
    /**
     *@brief
    task_info.task_id = js_request_body["task_id"].template get<int>();
    task_info.testbed_type = js_request_body["testbed_type"].template get<int>();

    task_info.testbed_pkg_path = js_request_body["license_file_url"].template get<std::string>();
    task_info.metiral_pkg_path = js_request_body["ip"].template get<std::string>();
    task_info.license_file_url = js_request_body["createdTime"].template get<std::string>();
     */
    /*
    {
        "task_id": 3824,
        "testbed_pkg_path": "http://172.17.11.202//cabin_data//testbed/3824/Geely-CX11-DMS_PLATFORM_v1.0.5_build20240411.zip",
        "metiral_pkg_path": "x",
        "license_file_url": "http://172.17.11.202//cabin_data//license/88/CX11-A3.zip",
        "testbed_type": "2",
        "ip": "172.17.11.202",
        "createdTime": "2024-04-18 13:52:31"
    }
    */
    struct UpdateTaskInfo
    {
        int task_id = 0;
        std::string testbed_type = "0";
        std::string testbed_pkg_path = "";
        std::string metiral_pkg_path = "";
        std::string license_file_url = "";
        std::string ip = "";
        std::string createdTime = "";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(UpdateTaskInfo, task_id, testbed_type, testbed_pkg_path, metiral_pkg_path, license_file_url, ip, createdTime);// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UpdateTaskInfo, task_id, testbed_type, testbed_pkg_path, metiral_pkg_path, license_file_url, ip, createdTime);
    };

    /**
     *@brief
        {
			"device_status" : 41,
			"device_status_msg" : "41 FREE UPDATED UPDATE_FAIL ",
			"task_id" : 3823,
			"task_status" : 1,
			"task_status_msg" : "1 DIVORCED "
        }
     */
    struct TaskResponse
    {
        int device_status;
        std::string device_status_msg;
        int task_id;
        int task_status;
        std::string task_status_msg;
        std::string addtion_err_msg;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskResponse, device_status, device_status_msg, task_id, task_status, task_status_msg, addtion_err_msg);
    };

}

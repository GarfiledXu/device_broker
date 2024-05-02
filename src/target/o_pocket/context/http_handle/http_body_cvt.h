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

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(UpdateTaskInfo
            , task_id, testbed_type, testbed_pkg_path
            , metiral_pkg_path, license_file_url, ip, createdTime);// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UpdateTaskInfo, task_id, testbed_type, testbed_pkg_path, metiral_pkg_path, license_file_url, ip, createdTime);
    };

    /**
     *@brief
     {
        "createdTime": "2024-04-19 19:06:58",
        "exchange": "cabinplatform.exchange",
        "hostname": "172.17.11.189",
        "json_config": null,
        "metrial_number": 17,
        "parent_task_id": 3863,
        "password": "admin",
        "password_smb": "Yhw@2023@",
        "port": 5672,
        "receive_queue_name": "cabinplatform.3865",
        "receive_routing_key": "cabinplatform.3865.0",
        "send_queue_name": "cabinplatform_comolete.3865",
        "send_routing_key": "cabinplatform_comolete.3865.0",
        "testbed_type": "2",
        "upload_result_dir_path": "smb://172.17.11.202/objective_result/3863/3865",
        "username": "admin",
        "username_smb": "arcsoft-hz\\yhw9826",
        "vhost": "cabin_platform_vhost"
    }
     */
    struct ObjectiveRabbitmqTaskInfo
    {
        // int task_id = 0;
        int metrial_number = 0;
        int parent_task_id = 0;
        int port = 0;
        std::string createdTime = "";
        std::string exchange = "";
        std::string hostname = "";
        // std::string json_config = "";
        std::string password = "";
        std::string password_smb = "";
        std::string receive_queue_name = "";
        std::string receive_routing_key = "";
        std::string send_queue_name = "";
        std::string send_routing_key = "";
        std::string testbed_type = "";
        std::string upload_result_dir_path = "";
        std::string username = "";
        std::string username_smb = "";
        std::string vhost = "";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ObjectiveRabbitmqTaskInfo
            , metrial_number, parent_task_id, port
            , createdTime, exchange, hostname, password, password_smb
            , receive_queue_name, receive_routing_key, send_queue_name, send_routing_key
            , testbed_type, upload_result_dir_path, username, username_smb, vhost);// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UpdateTaskInfo, task_id, testbed_type, testbed_pkg_path, metiral_pkg_path, license_file_url, ip, createdTime);
    };
    /**
     *@brief
        {
            "material_type": "dms",
            "metrial_path_url": "smb://172.17.11.179/testlib_iot/smartcar/project/temp/#22994-geely-cx11-a3/03-testsample/db/material/obkective/yawn/corner/id21640_cx11_yawn_cornercaseid_001_000001_20240312132254399.mp4",
            "msg_id": 8,
            "parent_task_id": 3863,
            "upload_result_dir_path": "smb://172.17.11.202/objective_result/3863/3865"
        }
     */
    struct RabbitmqMsgTaskInfo
    {
        // int task_id = 0;
        int msg_id = 0;
        int parent_task_id = 0;
        std::string material_type = "";
        std::string metrial_path_url = "";
        std::string upload_result_dir_path = "";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RabbitmqMsgTaskInfo
            , msg_id, parent_task_id 
            , material_type, metrial_path_url, upload_result_dir_path);// NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UpdateTaskInfo, task_id, testbed_type, testbed_pkg_path, metiral_pkg_path, license_file_url, ip, createdTime);
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
    struct TaskDeviceStateResponse
    {
        int device_status;
        std::string device_status_msg;
        int task_id;
        int task_status;
        std::string task_status_msg;
        std::string addtion_err_msg;

        int code;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskDeviceStateResponse
            , device_status, device_status_msg, task_id, task_status, task_status_msg, addtion_err_msg, code);
    };

    /**
     *@brief
        {
        "task_id":110,
        "reboot":1
        }
     */
    struct TaskDeviceState
    {
        int task_id;
        int reboot;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskDeviceState, task_id, reboot);
    };

    /**
     *@brief
        {
        "task_id":110,
        "reboot":1
        }
     */
    struct TaskObjectiveTerminate
    {
        int task_id;
        int task_type;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskObjectiveTerminate, task_id, task_type);
    };
    /**
     *@brief 
        {
            "code" : 0,
            "data" : 
            [
                {
                    "task_id" : 3880
                }
            ],
            "msg" : "success"
        }
     */


     /**
      *@brief
        url: file_operation/file_pull
        {
            "task_id":110,
            "protocol":"smb/http/ftp",
            "dst_url":"xxx",
            "src_type":"core_file/log",
            "opt_type":"copy/move"
        }
        {
            "task_id":110,
            "src_type":"core_file/log"
        }
        {
            "task_id":110,
            "command":"file_pull/file_clear",
            "param_1":"core_file/core_file/log",
            "protocol":"smb/http/sftp/ftp"
        }
      */
    struct TaskFileOperation_FilePull {
        int task_id;
        std::string protocol;
        std::string dst_url;
        std::string src_type;
        std::string opt_type;

        std::string smb_usr;
        std::string smb_passwd;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskFileOperation_FilePull, protocol, dst_url, src_type, opt_type,
            smb_usr, smb_passwd);
    };
    struct TaskFileOperation_FileClear {
        int task_id;
        std::string src_type;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TaskFileOperation_FileClear, src_type);
    };
}

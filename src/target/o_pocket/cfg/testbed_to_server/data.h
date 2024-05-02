#pragma once
#include <string>
#include <vector>

struct cfg_testbed_to_server
{
    struct version_
    {
        std::string correspond_parse_version;
    };

    struct license_
    {
        bool if_update;
        bool if_update_false_to_continue;
        std::string update_file_or_dir_rename;
        std::string update_cp_to_dir;
    };

    struct must_
    {
        /* data */
        std::vector<std::string> check_file_or;
        std::vector<std::string> check_file_and;
    };

    struct performance_
    {
        /* data */
        int run_testbed_process_max;
    };

    struct server_to_exec_module_
    {
        /* data */
        bool enable;
        std::string cmd;
        std::string cmd_exe_name;
        int cmd_timeout_s;
        bool if_parallel;
        std::vector<int> cmd_result_right_value;
        int result_check_mode;
        int execute_condition;
    };

    std::string modify_date;
    version_ version;
    license_ license;
    must_ must;
    performance_ performance;
    std::vector<server_to_exec_module_> server_to_exec_dms;
    std::vector<server_to_exec_module_> server_to_exec_oms;
    std::vector<server_to_exec_module_> server_to_exec_face;
};
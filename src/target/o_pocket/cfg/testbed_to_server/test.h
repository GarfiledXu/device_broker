#pragma once
#include "toml_convert.h"

using namespace toml::literals::toml_literals;
inline void cfg_toml_testbed_to_server_test_1() {
    //full field cfg content convert to toml format 
    const auto full_field_content = u8R"(
        modify_date="2023/11/06"
        [version]
        correspond_parse_version="2.0.1"
        [license]
        if_update=true
        if_update_false_to_continue=false
        update_file_or_dir_rename="license.dat"
        update_cp_to_dir="./readonly/xx"
        [must]
        check_file_or=[
        ]
        check_file_and=[
        ]
        [performance]
        run_testbed_process_max=1
        [[server_to_exec_dms]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10
        if_parallel=false
        cmd_result_right_value=[0, -1, 2]
        result_check_mode=0
        execute_condition=0
        [[server_to_exec_oms]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10
        if_parallel=false
        cmd_result_right_value=[0, -1, 2]
        result_check_mode=0
        execute_condition=0
        [[server_to_exec_face]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10
        if_parallel=false
        cmd_result_right_value=[0, -1, 2]
        result_check_mode=0
        execute_condition=0
    )"_toml;
    toml::value full_field_content_2 = toml::value(toml::from<cfg_testbed_to_server>::from_toml(full_field_content));
    std::cout << "full field content >>>>>>>>: " << std::endl << toml::format(full_field_content) << std::endl;
    std::cout << "full field content_2 >>>>>>>>: " << std::endl << toml::format(full_field_content_2) << std::endl;
}
inline void cfg_toml_testbed_to_server_test_2() {
    auto only_table_name = u8R"(
        modify_date="2023/11/06"
        [version]
        correspond_parse_version="2.0.1"
        [license]
        if_update=true
        if_update_false_to_continue=false
        update_file_or_dir_rename="license.dat"
        update_cp_to_dir="./readonly/xx"
        [must]
        check_file_or=[
        ]
        check_file_and=[
        ]
        [performance]
        run_testbed_process_max=1
        [[server_to_exec_dms]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10
        if_parallel=false
        cmd_result_right_value=[0, -1, 2]
        result_check_mode=0
        execute_condition=0
        
        [[server_to_exec_oms]]

        [[server_to_exec_oms]]

        [[server_to_exec_face]]
    )"_toml;
    auto toml_to_stru = toml::from<cfg_testbed_to_server>::from_toml(only_table_name);
    toml::value only_table_name_2 = toml::value(toml_to_stru);
    toml::value only_table_name_3 = toml::value(toml::from<cfg_testbed_to_server>::from_toml(only_table_name_2));
    std::cout << "only_table_name >>>>>>>>: " << std::endl << toml::format(only_table_name) << std::endl;
    std::cout << "only_table_name_2 >>>>>>>>: " << std::endl << toml::format(only_table_name_2) << std::endl;
    std::cout << "only_table_name_3 >>>>>>>>: " << std::endl << toml::format(only_table_name_3) << std::endl;
}
inline void cfg_toml_testbed_to_server_test_3() {
    auto array_item_not_complete = u8R"(
        modify_date="2023/11/06"
        [version]
        correspond_parse_version="2.0.1"
        [license]
        if_update=true
        if_update_false_to_continue=false
        update_file_or_dir_rename="license.dat"
        update_cp_to_dir="./readonly/xx"
        [must]
        check_file_or=[
        ]
        check_file_and=[
        ]
        [performance]
        run_testbed_process_max=1
        [[server_to_exec_dms]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10
        if_parallel=false
        cmd_result_right_value=[0, -1, 2]
        result_check_mode=0
        execute_condition=0
        
        [[server_to_exec_oms]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10

        [[server_to_exec_oms]]

        [[server_to_exec_face]]
        enable=true
        cmd="xxx"
        cmd_exe_name="xxx"
        cmd_timeout_s=10
    )"_toml;
    toml::value array_item_not_complete2 = toml::value(toml::from<cfg_testbed_to_server>::from_toml(array_item_not_complete));
    toml::value array_item_not_complete3 = toml::value(toml::from<cfg_testbed_to_server>::from_toml(array_item_not_complete2));
    std::cout << "only_table_name >>>>>>>>: " << std::endl << toml::format(array_item_not_complete) << std::endl;
    std::cout << "only_table_name_2 >>>>>>>>: " << std::endl << toml::format(array_item_not_complete2) << std::endl;
    std::cout << "only_table_name_3 >>>>>>>>: " << std::endl << toml::format(array_item_not_complete3) << std::endl;
}

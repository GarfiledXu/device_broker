#pragma once
#include "toml_convert.h"

using namespace toml::literals::toml_literals;
inline void cfg_toml_init_to_server_1() {
    //full field cfg content convert to toml format 
    const auto full_field_content = u8R"(
        modify_date="2023/11/06"
        default_parse_version="2.0.1"

        [i30_network]
        listen_ip="172.168.17.2"
        listen_port=30
        upload_ip="172.168.2.3"
        upload_port=39
        upload_connect_timeout_ms=3000
        upload_connect_retry_max=6

        [objective_network]
        listen_ip="183.13.14.1"
        listen_port=72

        [log]
        level=3
        root_path="xxx"
        testbed_stdout_name="testbed_stdout"
        server_stdout_name="server_stdout"
        testbed_segmentation=true

        [cache]
        tmp_root_dir_path="xxx"
        i30_root_dir_path="xxx"
        objective_root_dir_path="xxx"
        
        ## xjf add new 2024/04/02, for set mv operation for testbed when testbed be loaded
        [[mv_testbed_file]]
        relative_to_testbed_root_path="./libarcsoft_vehicle_utils_skel.so"
        target_device_dst_file_path="/etc/images/dsp/libarcsoft_vehicle_utils_skel.so"
        [[mv_testbed_file]]
        relative_to_testbed_root_path="./libneat_1_1_skel.so"
        target_device_dst_file_path="/etc/images/dsp/libneat_1_1_skel.so"



        [objective_runtime]
        objective_run_testbed_process_max=3
        objective_download_thread_max=3
        objective_upload_thread_max=3
        objective_cache_video_max=4
    )"_toml;
    toml::value full_field_content_2 = toml::value(toml::from<cfg_init_to_server>::from_toml(full_field_content));
    std::cout << "full field content >>>>>>>>: " << std::endl << toml::format(full_field_content) << std::endl;
    std::cout << "full field content_2 >>>>>>>>: " << std::endl << toml::format(full_field_content_2) << std::endl;
}

inline void cfg_toml_init_to_server_2() {
    auto only_table_name = u8R"(
        modify_date="2023/11/06"
        default_parse_version="2.0.1"

        [i30_network]
        listen_ip="172.168.17.2"
        listen_port=30
        upload_ip="172.168.2.3"
        upload_port=39
        upload_connect_timeout_ms=3000
        upload_connect_retry_max=6

        [objective_network]
        listen_ip="183.13.14.1"
        listen_port=72

        [log]
        level=3
        root_path="xxx"
        testbed_stdout_name="testbed_stdout"
        server_stdout_name="server_stdout"
        testbed_segmentation=true

        [cache]
        tmp_root_dir_path="xxx"
        i30_root_dir_path="xxx"
        objective_root_dir_path="xxx"

        ## xjf add new 2024/04/02, for set mv operation for testbed when testbed be loaded
        [[mv_testbed_file]]
        relative_to_testbed_root_path="./libarcsoft_vehicle_utils_skel.so"
        target_device_dst_file_path="/etc/images/dsp/libarcsoft_vehicle_utils_skel.so"
        [[mv_testbed_file]]
        relative_to_testbed_root_path="./libneat_1_1_skel.so"
        target_device_dst_file_path="/etc/images/dsp/libneat_1_1_skel.so"



        [objective_runtime]
        
    )"_toml;
    auto toml_to_stru = toml::from<cfg_init_to_server>::from_toml(only_table_name);
    toml::value only_table_name_2 = toml::value(toml_to_stru);
    toml::value only_table_name_3 = toml::value(toml::from<cfg_init_to_server>::from_toml(only_table_name_2));
    std::cout << "only_table_name >>>>>>>>: " << std::endl << toml::format(only_table_name) << std::endl;
    std::cout << "only_table_name_2 >>>>>>>>: " << std::endl << toml::format(only_table_name_2) << std::endl;
    std::cout << "only_table_name_3 >>>>>>>>: " << std::endl << toml::format(only_table_name_3) << std::endl;
}

inline void cfg_toml_init_to_server_3() {
    auto array_item_not_complete = u8R"(
        modify_date="2023/11/06"
        default_parse_version="2.0.1"

        [i30_network]
        listen_ip="172.168.17.2"
        listen_port=30
        upload_ip="172.168.2.3"
        upload_port=39
        upload_connect_timeout_ms=3000
        upload_connect_retry_max=6

        [objective_network]
        listen_ip="183.13.14.1"
        listen_port=72

        [log]
        level=3
        root_path="xxx"
        testbed_stdout_name="testbed_stdout"
        server_stdout_name="server_stdout"
        testbed_segmentation=true

        [cache]
        tmp_root_dir_path="xxx"
        i30_root_dir_path="xxx"
        objective_root_dir_path="xxx"

        ## xjf add new 2024/04/02, for set mv operation for testbed when testbed be loaded
        [[mv_testbed_file]]
        relative_to_testbed_root_path="./libarcsoft_vehicle_utils_skel.so"
        target_device_dst_file_path="/etc/images/dsp/libarcsoft_vehicle_utils_skel.so"
        [[mv_testbed_file]]
        relative_to_testbed_root_path="./libneat_1_1_skel.so"
        target_device_dst_file_path="/etc/images/dsp/libneat_1_1_skel.so"



        [objective_runtime]
        objective_run_testbed_process_max=3
        objective_cache_video_max=4
    )"_toml;
    toml::value array_item_not_complete2 = toml::value(toml::from<cfg_init_to_server>::from_toml(array_item_not_complete));
    toml::value array_item_not_complete3 = toml::value(toml::from<cfg_init_to_server>::from_toml(array_item_not_complete2));
    std::cout << "only_table_name >>>>>>>>: " << std::endl << toml::format(array_item_not_complete) << std::endl;
    std::cout << "only_table_name_2 >>>>>>>>: " << std::endl << toml::format(array_item_not_complete2) << std::endl;
    std::cout << "only_table_name_3 >>>>>>>>: " << std::endl << toml::format(array_item_not_complete3) << std::endl;
}
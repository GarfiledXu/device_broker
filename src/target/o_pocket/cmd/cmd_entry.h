#pragma once
#include "cli11_base.h"
#include "logic_impl_file_opt_pkg.h"
#include "logic_impl_test_component_pkg.h"
#include "logic_impl_service_pkg.h"

inline int cmd_entry(int argc, char** argv) {
    CLI::App cli_root{""};
    cli_root.allow_extras();
    static std::vector<std::string> vec_sub_cmd_str;

    //注册功能调用: 包括功能函数, 启动的服务模块, 以及测试模块
    //更彻底的话，采用定义时静态自动注册方式,
    DEF_SUB_CMD(function, "call function directly",
        new Cli11Option_unzip_testbed, new Cli11Option_download_http,
        new Cli11Option_mv_file, new Cli11Option_http_filesize,
        new Cli11Option_mearsure_url_space, new Cli11Option_query_file_size,
        new Cli11Option_query_dir_remain_space, new Cli11Option_smb_download,
        new Cli11Option_test_http_server, new Cli11Option_test_http_objective_server,
        new Cli11Option_test_threadloop_back, new Cli11Option_test_threadloop_front, new Cli11Option_test_threadloop_back_detach, new Cli11Option_test_threadloop_back_join,
        new Cli11Option_test_http_server_with_state_manager, new Cli11Option_update_testbed_and_replace
        );

    DEF_SUB_CMD(service, "select one service",
        new Cli11Option_http_service_objective, new Cli11Option_http_service_i30,
        new Cli11Option_http_service_objective_i30, new Cli11Option_websocket_service_device_ping
        );

    try {
        SLOGD("enter CLI11 PARSE");
        CLI11_PARSE(cli_root, argc, argv);
        SLOGD("out CLI11 PARSE");
    }
    catch (std::exception& e) {
        SLOGE("cli11 parse error! {}\n will return main -1", e.what());
        return -1;
    }

    // FILTER_ALL_SUB_CMD();
    FILTER_SUB_CMD(cli_root, function);
    FILTER_SUB_CMD(cli_root, service);

    return 0;
}


#pragma once
#include <string>
#include <vector>

struct cfg_init_to_server
{
    struct i30_network_
    {
        std::string listen_ip;
        int listen_port;
        std::string upload_ip;
        int upload_port;
        int upload_connect_timeout_ms;
        int upload_connect_retry_max;
    };

    struct objective_network_
    {
        std::string listen_ip;
        int listen_port;
    };

    struct log_
    {
        /* data */
        //log output mode controled by commond line argument input
        int level;
        std::string root_path;
        std::string testbed_stdout_name;
        bool testbed_segmentation;
        //not required
        std::string server_stdout_name;
    };

    struct cache_
    {
        /* data */
        std::string tmp_root_dir_path;
        std::string i30_root_dir_path;
        std::string objective_root_dir_path;

    };

    struct objective_runtime_
    {
        /* data */
        int objective_run_testbed_process_max;
        int objective_download_thread_max;
        int objective_upload_thread_max;
        int objective_cache_video_max;
    };

    //xjf add new 2024/04/02
    struct mv_testbed_file_ {
        std::string relative_to_testbed_root_path;
        std::string target_device_dst_file_path;
    };

    std::string modify_date;
    std::string default_parse_version;

    log_ log;
    cache_ cache;
    objective_network_ objective_network;
    i30_network_ i30_network;
    objective_runtime_ objective_runtime;

    //xjf add new 2024/04/02
    std::vector<mv_testbed_file_> mv_testbed_file;
};
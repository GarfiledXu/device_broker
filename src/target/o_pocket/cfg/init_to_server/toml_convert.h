#pragma once
#include "../my_toml_macro.h"
#include "data.h"


DEFINE_FROM_TOML(cfg_init_to_server, in_v) {
    cfg_init_to_server out;
    GET_SUB_VALUE(v_, in_v, i30_network);
    GET_SUB_VALUE(v_, in_v, objective_network);
    GET_SUB_VALUE(v_, in_v, log);
    GET_SUB_VALUE(v_, in_v, cache);
    GET_SUB_VALUE(v_, in_v, objective_runtime);
    //xjf add new 2024/04/02
    #define FUNC_CONVERT_ARRAY(key_name, in_value, out) \
    { \
        auto is_exist = in_value.contains(#key_name) ; \
        if (is_exist) { \
            auto array_value = find(in_value, #key_name).as_array(); \
            for (auto& t_v : array_value) { \
                if(t_v.as_table().empty()){ \
                    continue; \
                } \
                cfg_init_to_server::mv_testbed_file_ cur_item{}; \
                FIND_VALUE_TO_ASSIGN(cur_item, t_v, relative_to_testbed_root_path, std::string); \
                FIND_VALUE_TO_ASSIGN(cur_item, t_v, target_device_dst_file_path, std::string); \
                out.key_name.push_back(cur_item); \
            } \
        } \
    }
    FUNC_CONVERT_ARRAY(mv_testbed_file, in_v, out);


    FIND_VALUE_TO_ASSIGN(out, in_v, default_parse_version, std::string);
    FIND_VALUE_TO_ASSIGN(out, in_v, modify_date, std::string);

    FIND_VALUE_TO_ASSIGN(out.i30_network, v_i30_network, listen_ip, std::string);
    FIND_VALUE_TO_ASSIGN(out.i30_network, v_i30_network, listen_port, int);
    FIND_VALUE_TO_ASSIGN(out.i30_network, v_i30_network, upload_ip, std::string);
    FIND_VALUE_TO_ASSIGN(out.i30_network, v_i30_network, upload_port, int);
    FIND_VALUE_TO_ASSIGN(out.i30_network, v_i30_network, upload_connect_timeout_ms, int);
    FIND_VALUE_TO_ASSIGN(out.i30_network, v_i30_network, upload_connect_retry_max, int);

    FIND_VALUE_TO_ASSIGN(out.objective_network, v_objective_network, listen_ip, std::string);
    FIND_VALUE_TO_ASSIGN(out.objective_network, v_objective_network, listen_port, int);

    FIND_VALUE_TO_ASSIGN(out.log, v_log, level, int);
    FIND_VALUE_TO_ASSIGN(out.log, v_log, root_path, std::string);
    FIND_VALUE_TO_ASSIGN(out.log, v_log, testbed_stdout_name, std::string);
    FIND_VALUE_TO_ASSIGN(out.log, v_log, testbed_segmentation, bool);
    FIND_VALUE_TO_ASSIGN(out.log, v_log, server_stdout_name, std::string);

    FIND_VALUE_TO_ASSIGN(out.cache, v_cache, tmp_root_dir_path, std::string);
    FIND_VALUE_TO_ASSIGN(out.cache, v_cache, i30_root_dir_path, std::string);
    FIND_VALUE_TO_ASSIGN(out.cache, v_cache, objective_root_dir_path, std::string);

    FIND_VALUE_TO_ASSIGN(out.objective_runtime, v_objective_runtime, objective_run_testbed_process_max, int);
    FIND_VALUE_TO_ASSIGN(out.objective_runtime, v_objective_runtime, objective_download_thread_max, int);
    FIND_VALUE_TO_ASSIGN(out.objective_runtime, v_objective_runtime, objective_upload_thread_max, int);
    FIND_VALUE_TO_ASSIGN(out.objective_runtime, v_objective_runtime, objective_cache_video_max, int);


    return out;
};

DEFINE_INTO_TOML(cfg_init_to_server, in_s) {
    auto mv_testbed_file = toml::array();
    for (auto& item: in_s.mv_testbed_file) {
        auto t_v = toml::value{
            {"relative_to_testbed_root_path", item.relative_to_testbed_root_path}, 
            {"target_device_dst_file_path", item.target_device_dst_file_path}, 
        }; 
        mv_testbed_file.push_back(t_v); 
    }

    return toml::value{
        INSERT_KEY_VALUE_BY_STRU(in_s, modify_date),
        INSERT_KEY_VALUE_BY_STRU(in_s, default_parse_version),
        //xjf add new 2024/04/02
        {"mv_testbed_file", mv_testbed_file},
        {
            "log",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.log, level),
                INSERT_KEY_VALUE_BY_STRU(in_s.log, root_path),
                INSERT_KEY_VALUE_BY_STRU(in_s.log, testbed_stdout_name),
                INSERT_KEY_VALUE_BY_STRU(in_s.log, testbed_segmentation),
                INSERT_KEY_VALUE_BY_STRU(in_s.log, server_stdout_name)
            }
        },
        {
            "objective_network",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.objective_network, listen_ip),
                INSERT_KEY_VALUE_BY_STRU(in_s.objective_network, listen_port)
            }
        },
        {
            "i30_network",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.i30_network, listen_ip),
                INSERT_KEY_VALUE_BY_STRU(in_s.i30_network, listen_port),
                INSERT_KEY_VALUE_BY_STRU(in_s.i30_network, upload_ip),
                INSERT_KEY_VALUE_BY_STRU(in_s.i30_network, upload_port),
                INSERT_KEY_VALUE_BY_STRU(in_s.i30_network, upload_connect_timeout_ms),
                INSERT_KEY_VALUE_BY_STRU(in_s.i30_network, upload_connect_retry_max)
            }
        },
        {
            "log",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.objective_runtime, objective_run_testbed_process_max),
                INSERT_KEY_VALUE_BY_STRU(in_s.objective_runtime, objective_download_thread_max),
                INSERT_KEY_VALUE_BY_STRU(in_s.objective_runtime, objective_upload_thread_max),
                INSERT_KEY_VALUE_BY_STRU(in_s.objective_runtime, objective_cache_video_max)
            }
        },
        {
            "cache",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.cache, tmp_root_dir_path),
                INSERT_KEY_VALUE_BY_STRU(in_s.cache, i30_root_dir_path),
                INSERT_KEY_VALUE_BY_STRU(in_s.cache, objective_root_dir_path)
            }
        }
    };
};

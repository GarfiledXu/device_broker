#pragma once
#include "../my_toml_macro.h"
#include "data.h"
#include <iostream>

//服务程序配置文件的解析策略
//最外层调用: 需获得结论，成功 or 失败
//内部解析: 必填字段，缺少key时应该直接抛出异常，让外部捕获
//是否有字段可选项检查?
DEFINE_FROM_TOML(cfg_testbed_to_server, in_v) {
    cfg_testbed_to_server out;
    //normal must input table
    GET_SUB_VALUE(v_, in_v, version);
    GET_SUB_VALUE(v_, in_v, license);
    GET_SUB_VALUE(v_, in_v, must);

    FIND_VALUE_TO_ASSIGN(out, in_v, modify_date, std::string);

    FIND_VALUE_TO_ASSIGN(out.version, v_version, correspond_parse_version, std::string);

    FIND_VALUE_TO_ASSIGN(out.license, v_license, if_update, bool);
    FIND_VALUE_TO_ASSIGN(out.license, v_license, if_update_false_to_continue, bool);
    FIND_VALUE_TO_ASSIGN(out.license, v_license, update_file_or_dir_rename, std::string);
    FIND_VALUE_TO_ASSIGN(out.license, v_license, update_cp_to_dir, std::string);

    FIND_VALUE_TO_ASSIGN(out.must, v_must, check_file_or, std::vector<std::string>);
    FIND_VALUE_TO_ASSIGN(out.must, v_must, check_file_and, std::vector<std::string>);

    //process server to exec module vector
    //1. check array name if exist by using contains function
    //2. check content if exist by using count function
    //3. check each field if exist, or to assign default by using find_or function
       //if non and empty(not contain any table), do noting
        //throw the pase error by find function no default value
    //the table of array, if check is empty, not throw exception, just to continue;
        // printf("%s, get count:%d, len:%d, if empty:%d\n", #key_name, in_value.count(#key_name), in_value.at(#key_name).as_array().size(), in_value.at(#key_name).as_array().empty()); 
#define FUNC_CONVERT_MODULE(key_name, in_value, out) \
    { \
        auto is_exist = in_value.contains(#key_name) ; \
        if (is_exist) { \
            auto array_value = find(in_value, #key_name).as_array(); \
            for (auto& t_v : array_value) { \
                if(t_v.as_table().empty()){ \
                    continue; \
                } \
                cfg_testbed_to_server::server_to_exec_module_ cur_exec{}; \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, enable, bool); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, cmd, std::string); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, cmd_exe_name, std::string); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, cmd_timeout_s, int); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, if_parallel, bool); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, cmd_result_right_value, std::vector<int>); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, result_check_mode, int); \
                FIND_VALUE_TO_ASSIGN(cur_exec, t_v, execute_condition, int); \
                out.key_name.push_back(cur_exec); \
            } \
        } \
    }
    
    FUNC_CONVERT_MODULE(server_to_exec_dms, in_v, out);
    FUNC_CONVERT_MODULE(server_to_exec_oms, in_v, out);
    FUNC_CONVERT_MODULE(server_to_exec_face, in_v, out);

    return out;
};

DEFINE_INTO_TOML(cfg_testbed_to_server, in_s) {
    auto array_exec_dms = toml::array();
    auto array_exec_oms = toml::array();
    auto array_exec_face = toml::array();
    #define ASSIGN_MODULE_INTO_TOML(in_module_name, out_array_name) \
    { \
        for (auto& item : in_s.in_module_name) { \
            auto t_v = toml::value{ \
                INSERT_KEY_VALUE_BY_STRU(item, enable), \
                INSERT_KEY_VALUE_BY_STRU(item, cmd), \
                INSERT_KEY_VALUE_BY_STRU(item, cmd_exe_name), \
                INSERT_KEY_VALUE_BY_STRU(item, cmd_timeout_s), \
                INSERT_KEY_VALUE_BY_STRU(item, if_parallel), \
                INSERT_KEY_VALUE_BY_STRU(item, cmd_result_right_value), \
                INSERT_KEY_VALUE_BY_STRU(item, result_check_mode), \
                INSERT_KEY_VALUE_BY_STRU(item, execute_condition), \
            }; \
            out_array_name.push_back(t_v); \
        } \
    }
    ASSIGN_MODULE_INTO_TOML(server_to_exec_dms, array_exec_dms);
    ASSIGN_MODULE_INTO_TOML(server_to_exec_oms, array_exec_oms);
    ASSIGN_MODULE_INTO_TOML(server_to_exec_face, array_exec_face);

    return toml::value{
        INSERT_KEY_VALUE_BY_STRU(in_s, modify_date),
        {
            "version",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.version, correspond_parse_version),
            }
        },
        {
            "license",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.license, if_update),
                INSERT_KEY_VALUE_BY_STRU(in_s.license, if_update_false_to_continue),
                INSERT_KEY_VALUE_BY_STRU(in_s.license, update_file_or_dir_rename),
                INSERT_KEY_VALUE_BY_STRU(in_s.license, update_cp_to_dir)
            }
        },
        {
            "must",
            {
                INSERT_KEY_VALUE_BY_STRU(in_s.must, check_file_or),
                INSERT_KEY_VALUE_BY_STRU(in_s.must, check_file_and),
            }
        },
        {"server_to_exec_dms", array_exec_dms},
        {"server_to_exec_oms", array_exec_oms},
        {"server_to_exec_face", array_exec_face},
    };
};

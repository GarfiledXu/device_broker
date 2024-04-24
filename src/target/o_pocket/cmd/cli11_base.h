#pragma once
#include "CLI11.hpp"
#include "log.h"
#include "fmt_test.h"

class Cli11OptionBase {
public:
    virtual  int to_add_option(CLI::App& inapp) = 0;
    virtual int call_funtion() = 0;
    virtual std::string get_sub_cmd_name() = 0;
};

#define DEF_SUB_CMD(name, descript, ...) \
auto* sub_cmd_##name= cli_root.add_subcommand(#name, descript); \
std::vector<Cli11OptionBase*> vec_option_##name{__VA_ARGS__}; \
for (auto& cur_option : vec_option_##name) { \
    cur_option->to_add_option(*sub_cmd_##name); \
} \



//遍历所有选项，判断子选项是否存在，存在则执行 
#define FILTER_SUB_CMD(inapp, name) \
if (inapp.got_subcommand(#name)) { \
        for (auto& cur_option : vec_option_##name) { \
            if (sub_cmd_##name->got_subcommand(cur_option->get_sub_cmd_name())) { \
                SLOGW("enter call: [{}]", cur_option->get_sub_cmd_name()); \
                cur_option->call_funtion(); \
            } \
        } \
    }



// #define DEF_SUB_CMD(name, name_str, descript, ...) \
// auto* sub_cmd_##name= cli_root.add_subcommand(name_str, descript); \
// std::vector<Cli11OptionBase*> vec_option_##name{__VA_ARGS__}; \
// for (auto& cur_option : vec_option_##name) { \
//     cur_option->to_add_option(*sub_cmd_##name); \
// } \
// vec_sub_cmd_str.push_back(name_str);


// //遍历所有选项，判断子选项是否存在，存在则执行 
// #define FILTER_SUB_CMD(inapp, name, name_str) \
// if (inapp.got_subcommand(name_str)) { \
//         for (auto& cur_option : vec_option_##name) { \
//             if (sub_cmd_##name->get_subcommand(cur_option->get_sub_cmd_name())) { \
//                 SLOGI("enter call: [{}]", cur_option->get_sub_cmd_name()); \
//                 cur_option->call_funtion(); \
//             } \
//         } \
//     }

// #define FILTER_ALL_SUB_CMD() \
// for(auto& name_str : vec_sub_cmd_str){ \
//     FILTER_SUB_CMD(cli_root, name_str); \
// }
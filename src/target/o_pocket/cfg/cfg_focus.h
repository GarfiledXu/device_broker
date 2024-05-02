//xjf add
//when configure compile, only include the cfg dir, not to include the specific cfg
#pragma once
#include "cfg_code_gen.h"
#include <mutex>
#include "my_toml_macro.h"
#include "init_to_server/toml_convert.h"
#include "task_to_server/toml_task_to_server.h"
#include "testbed_to_server/toml_convert.h"

CFG_FOCUS_BEGIN()

DECLARE_GET_SET(cfg_init_to_server);
DECLARE_GET_SET(cfg_testbed_to_server);

CFG_FOCUS_END()

template <typename T>
inline T CfgFocus::load_cfg_by_path(const std::string& in_path, const std::string& in_protocol) {
    if (in_protocol == "toml") {
        auto toml_from_txt = toml::parse(in_path);
        return toml::from<T>::from_toml(toml_from_txt);
    } 
    else {
        std::string msg = std::string("load_cfg_by_path, impl don't contain current protocol: ") + std::string(in_protocol);
        throw std::logic_error(msg);
    }
}


// template <>
// inline cfg_init_to_server CfgFocus::load_cfg_by_path(const std::string& in_path, const std::string& in_protocol) {
//     //for protocol toml
//     if (in_protocol == "toml") {
//         auto toml_from_txt = toml::parse(in_path);
//         return toml::from<cfg_init_to_server>::from_toml(toml_from_txt);
//     }   
//     else {
//         std::string msg = std::string("load_cfg_by_path, impl don't contain current protocol: ") + std::string(in_protocol);
//         throw std::logic_error(msg);
//     }
// }

#if 0
//sample code
int test_main() {
    CFG_INS.set_cfg_init_to_server(CfgFocus::load_cfg_by_path<cfg_init_to_server>("./toml", "toml"));
    //or directly way
    // CFG_INS.set_cfg_init_to_server("./toml", "toml");
}
#endif
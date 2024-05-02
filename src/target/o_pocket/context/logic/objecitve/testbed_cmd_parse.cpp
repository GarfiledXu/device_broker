#include "testbed_cmd_parse.h"


std::string TestbedCmdParser::gen_replaced_cmd(const std::string& src_cmd_str) {
    return cmd_var_replace_(src_cmd_str);
}

std::string TestbedCmdParser::cmd_var_replace_(const std::string& src_cmd) {
    std::string gen_cmd = src_cmd;
    for (auto& pair_item : replace_map_) {
        auto& key = pair_item.first;
        auto& value = pair_item.second;
        std::size_t pos = src_cmd.find(key);
        if (pos != std::string::npos) {
            gen_cmd.replace(pos, key.length(), value);
        }
    }
    SLOGI("cmd_buildin_var_replace: \nsrc cmd:{}\ngen cmd:{}", src_cmd, gen_cmd);
    return gen_cmd;
}

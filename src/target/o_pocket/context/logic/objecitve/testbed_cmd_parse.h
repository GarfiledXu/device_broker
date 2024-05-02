//xjf 2024/01/11
#pragma once
#include "any/any.h"
#include <list>
#include <map>
#include "log.h"

#define CVAR_LOCAL_MATERIAL_PATH "local_material_path"
#define CVAR_RESULT_DIR "result_dir"
#define CVAR_MATERIAL_URL "material_url"
#define CVAR_MSG_ID "msg_id"

//main modify point
#if 0
#define STATIC_BUILT_IN_VAR_INITIALIZER_LIST \
{ \
    TestbedCmdVar<std::string>{.enable = true, .var_name = CVAR_LOCAL_MATERIAL_PATH, .var_value = "",  .var_source = -1, \
    .tip_msg = "video or image path which input testbed"}, \
\
    TestbedCmdVar<std::string>{.enable = true, .var_name = CVAR_RESULT_DIR, .var_value = "",  .var_source = -1, \
    .tip_msg = "the folder path which input testbed and will store the result file"}, \
\
    TestbedCmdVar<std::string>{.enable = true, .var_name = CVAR_MATERIAL_URL, .var_value = "",  .var_source = -1, \
    .tip_msg = "the url path which input testbed for recording"}, \
\
    TestbedCmdVar<int>{.enable = false, .var_name = CVAR_MSG_ID, .var_value = 0,  .var_source = -1, \
    .tip_msg = "current execute testbed msg id"}, \
} 
#endif

//var_source:
//-1 : non input
//0: define default
//1:built-in assigned
//2:come from out cfg var
template<typename T>
struct TestbedCmdVar {
    bool enable;
    std::string var_name;
    T var_value;
    int var_source;
    std::string tip_msg;
};

//stt ==> server to testbed
//for use static data, so defined as singleton class
class TestbedCmdParser {
public:
    ~TestbedCmdParser() = default;
    TestbedCmdParser() = default;
    // static TestbedCmdParser& ins() {
    //     static TestbedCmdParser cur_ins;
    //     return cur_ins;
    // };
    //push var value
    // template<typename T>
    // void push_var_value(const bool is_enable, const std::string var_name, T var_value, const int var_source, const std::string& tip_msg);
    //update var list
    template<typename T>
    void push_buitin_var_value(const std::string& in_var_name, T in_var_value);

    //update var list
    template<typename T>
    void push_cfg_var_value(const std::string& in_var_name, T in_var_value);

    //output final command
    std::string gen_replaced_cmd(const std::string& src_cmd_str);

private:
    std::string cmd_var_replace_(const std::string& src_cmd);
    
    //define static built-in variable
    // std::list<Any> static_builtin_var_list = STATIC_BUILT_IN_VAR_INITIALIZER_LIST;
    // std::list<Any> static_cfg_var_list;

    std::map<std::string, std::string> replace_map_;
};

template<typename T>
void TestbedCmdParser::push_cfg_var_value(const std::string& in_var_name, T in_var_value) {
    replace_map_[fmt::format("<sin_{}>", in_var_name)] = fmt::format("{}", in_var_value);
    SLOGI("push one cfg var name-value:[{}-{}]", in_var_name, in_var_value);
    return;
}

template<typename T>
void TestbedCmdParser::push_buitin_var_value(const std::string& in_var_name, T in_var_value) {
    replace_map_[fmt::format("<sin_{}>", in_var_name)] = fmt::format("{}", in_var_value);
    SLOGI("push one builtin var name-value:[{}-{}]", in_var_name, in_var_value);
    return;
    //得修改为特化
    //类型判断本质上还是运行时的操作，但直接赋值是在编译器就会进行判断的，将一个泛型类型赋值必然会遇到编译问题，除非进行特化
    #if 0
    bool is_matched = false;
   for (auto& any_item : static_builtin_var_list) {
       if (any_item.is_type <TestbedCmdVar<std::string>>()) {
           auto& cast_item = any_item.any_cast<TestbedCmdVar<std::string>>();
           if (cast_item.var_name != in_var_name) {
               continue;
           }
           if (!cast_item.enable) {
               SLOGE("cast var, name-value: [{}-{}], type:{}, not enable, will skip replace", "string", cast_item.var_name, cast_item.var_value);
               continue;
           }
           //assigned
           cast_item.var_name = in_var_name;
           //for compile pass
           cast_item.var_value = static_cast<std::string>(in_var_value);
           cast_item.var_source = 1;
           //push
           replace_map_[fmt::format("<sin_{}>", cast_item.var_name)] = fmt::format("{}", cast_item.var_value);
           SLOGI("push cast var to replace map, name-value: [{}-{}], type:{}, source:{}", cast_item.var_name, cast_item.var_value, "string", cast_item.var_source);
           is_matched = true;
       }
       else if (any_item.is_type<TestbedCmdVar<int>>()) {
           auto& cast_item = any_item.any_cast<TestbedCmdVar<int>>();
            if (cast_item.var_name != in_var_name) {
               continue;
           }
            if (!cast_item.enable) {
               SLOGE("cast var, name-value: [{}-{}], type:{}, not enable, will skip replace", cast_item.var_name, cast_item.var_value, "int", cast_item.var_source);
               continue;
           }
            //assigned
           cast_item.var_name = in_var_name;
           //for compile pass
           cast_item.var_value = static_cast<int>(in_var_value);
           cast_item.var_source = 1;
            //push
           replace_map_[fmt::format("<sin_{}>", cast_item.var_name)] = fmt::format("{}", cast_item.var_value);
           SLOGI("push cast var to replace map, cast var, name-value: [{}-{}], type:{}", cast_item.var_name, cast_item.var_value, "int", cast_item.var_source);
           is_matched = true;
       }
    }
   if (!is_matched) {
       SLOGE("can't match input var name:{} in builtin list", in_var_name);
   }
    SLOGI("input var name:{} in builtin list, and push to the repaced map", in_var_name);
    return;
    #endif
}
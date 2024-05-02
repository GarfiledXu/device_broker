#ifndef TESTBED_PARAM_HPP
#define TESTBED_PARAM_HPP
#include <iostream>
#include "json.hpp"
#include "component-all.hpp"
#include "samba_transfer.h"
#include "log.h" // new zjx9083
#include "filesystem_test.hpp"
// #include <any>
#include "any/any.h"
#include "testbed_cmd_parse.h"
extern std::string testbed_cmd_append_str;

inline fs::path normal_path(const fs::path& in_input_file) {
    //check file if exist, if non, to exception
    fs::path input_file = in_input_file;
    if (!fs::exists(input_file)) {
        SLOGE("input file is not exist, path:{}", input_file.c_str());
        std::string msg = input_file.string() + " file not exist";
        throw std::runtime_error(msg);
    }
    if (fs::is_directory(input_file)) {
        SLOGD("input file:{}, is directory, will append file name to extract parent path for strip backlash", input_file.c_str());
        input_file /= fs::path("file.txt");
        input_file = input_file.lexically_normal();
        fs::path return_path = input_file.parent_path();
        SLOGD("get directory normal path:{}", return_path.c_str());
        return return_path;
    }
    if (fs::is_regular_file(input_file)) {
        // SLOGD("get regular file normal path:{}", input_file.c_str());
        fs::path return_path = input_file.lexically_normal();
        return return_path;
    }
    std::string msg = input_file.string() + " file not regular file or directory";
    throw std::runtime_error(msg);
}

inline std::string test_replace_file(const std::string& in_cfg_name = "_configurations.json", const std::string& in_cfg_absolute_dir = ".") {
    std::string extended_cmd_str = "";
    //name _configurations.json
    std::string testbed_cfg_file_path = fmt::format("{}/{}", in_cfg_absolute_dir, in_cfg_name);
    if (fs::exists(testbed_cfg_file_path)) {
        try {
            std::ifstream ifm(testbed_cfg_file_path);
            std::string cfg_content = "";
            std::string tmp_str = "";
            while (std::getline(ifm, tmp_str)) {
                cfg_content += tmp_str;
            }
            ifm.close();
            SLOGD("get the cfg file content:{}", cfg_content);
            json js_root = json::parse(cfg_content);
            json js_replace_array = json::array();
            SLOGD("enter parse field formattedInputs");
            extended_cmd_str = js_root.at("formattedInputs").get<std::string>();
            SLOGD("out parse field formattedInputs");
            SLOGD("enter parse field configPath");
            js_replace_array = js_root.at("configPath");
            SLOGD("out parse field configPath");
            fs::path origin_dir = fs::current_path();
            // 计算出相对路径的绝对路径
            fs::current_path(in_cfg_absolute_dir);
            SLOGD("enter iterate configPath value");
            for (auto& replace_pair : js_replace_array) {
                std::string file_name = replace_pair.at("file_name").get<std::string>();
                //此时传入的目标目录是相对目录，需要切换到当前目录
                
                std::string dst_dir = replace_pair.at("dst_dir").get<std::string>();
                std::string src_file = fmt::format("{}/{}", in_cfg_absolute_dir, file_name); 
                std::string dst_file = fmt::format("{}{}", dst_dir, file_name); ;
                SLOGD("src file:{}, src_file to normal:{}, src_file to absolute:{}, src_file_to normal and to absolute:{}", src_file, normal_path(src_file).string(), fs::absolute(src_file).string(),fs::absolute(normal_path(src_file)).string());
                SLOGD("src dst_file:{}, dst_file to normal:{}, dst_file to absolute:{}, dst_file normal and to absolute:{}", dst_file, normal_path(dst_file).string(), fs::absolute(dst_file).string(), fs::absolute(normal_path(dst_file)).string());
                if (fs::exists(src_file)) {
                    if (fs::absolute(src_file) == fs::absolute(normal_path(dst_file))) {
                        SLOGW("path same, src file:{}, dst file:{}", src_file, dst_file);
                    }
                    else{
                        SLOGW("src file exist, path:{}, will rename to path:{}", src_file, fs::absolute(normal_path(dst_file)).string());
                        fs::rename(src_file, fs::absolute(normal_path(dst_file)));
                    }
                }
                return extended_cmd_str;
            }
            fs::current_path(origin_dir);
        }
        catch (std::exception & e) {
            SLOGE("error, testbed cfg file:{} exist, but parse error! {}", testbed_cfg_file_path, e.what());
        }
    }
    else {
        SLOGW("auto establish configure file not exist!");
    }
    return "";
}

class testbed_param {
    #define PARSE_JSON_VALUE_STR(j, var, key, state_, log_success, log_error) \
        if (j.contains(key)) { \
            var = get_json_value<std::string>(j, key); \
            if(var[0]=='\"') var = var.substr(1, var.length() - 2);\
            SLOGI("{}{}",log_success, var.c_str()); \
        } else { \
            state_ = -1; \
            SLOGE("{}",log_error); \
        }
    #define PARSE_JSON_VALUE_INT(j, var, key, state_, log_success, log_error) \
        if (j.contains(key)) { \
            var = get_json_value<int>(j, key); \
            SLOGI("{}{}",log_success, var); \
        } else { \
            state_ = -1; \
            SLOGE("{}",log_error); \
        }
public:
    testbed_param(){};
    testbed_param(std::string req,
                std::string testbed_root_dir_path = "/var/TESTBED",
                std::string result_dir_name = "result",
                std::string metrial_dir_name = "metrial",
                std::string testbed_dir_name = "testbed_objective",
                std::string testbed_name = "TESTBED_MAIN"):
                testbed_root_dir_path(testbed_root_dir_path),
                result_dir_name(result_dir_name),
                metrial_dir_name(metrial_dir_name),
                testbed_dir_name(testbed_dir_name),
                material_type("dms"),
                testbed_name(testbed_name){
        status = 0;
        json j;
        try {
            j = json::parse(req);
            SLOGI("testbed_param vtor parse req success:{}", req.c_str());
        } catch (json::parse_error& e) {
            status = -1;
            SLOGE("error! testbed_param vtor parse req, content:{}", e.what());
        }

        // 解析json
        PARSE_JSON_VALUE_INT(j, parent_task_id, "parent_task_id", status, "testbedRun parser parent_task_id:\n", "testbedRun parser parent_task_id fail\n");
        PARSE_JSON_VALUE_INT(j, msg_id, "msg_id", status, "testbedRun parser msg_id:\n", "testbedRun parser msg_id fail\n");
        PARSE_JSON_VALUE_STR(j, upload_result_dir_path, "upload_result_dir_path", status, "testbedRun parser upload_result_dir_path:{}", "testbedRun parser upload_result_dir_path fail\n");
        PARSE_JSON_VALUE_STR(j, metrial_path_url, "metrial_path_url", status, "testbedRun parser metrial_path_url:{}", "testbedRun parser metrial_path_url fail\n");
        PARSE_JSON_VALUE_STR(j, material_type, "material_type", status, "testbedRun parser material_type:{}", "testbedRun parser material_type fail\n");

        // 判断 /var/TESTBED 是否存在
        if(access(this->testbed_root_dir_path.c_str(), 0)){
            status = -1;
            SLOGE("testbed_root_dir_path not exist: {}", this->testbed_root_dir_path.c_str());
        }
        // 判断 /var/TESTBED/testbed_objective 是否存在
        this-> testbed_path = this->testbed_root_dir_path + "/" + this->testbed_dir_name ;
        if(access(this->testbed_path.c_str(), 0)){
            status = -1;
            SLOGE("testbed_path not exist: {}", this->testbed_path.c_str());
        }
        // testbed_path = /var/TESTBED/testbed_objective
        SLOGI("testbed_path:{}", this-> testbed_path.c_str());

        // 创建路径 /var/TESTBED/testbed_objective/"parent_task_id"//msg_id/result
        this-> result_dir_path = this-> testbed_path + "/" + std::to_string(parent_task_id);
        if(access(this->result_dir_path.c_str(), 0)){
            #if 0
            if (system(std::string("mkdir " + this->result_dir_path).c_str())) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }else{
                SLOGI("mkdir {}", this->result_dir_path.c_str());
            }
            #else
            if (mkdir(this->result_dir_path.c_str(), 0755)) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }
            #endif
        }
        this-> result_dir_path = this-> result_dir_path + "/" + std::to_string(msg_id);
        if(access(this->result_dir_path.c_str(), 0)){
            #if 0
            if (system(std::string("mkdir " + this->result_dir_path).c_str())) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }else{
                SLOGI("mkdir {}", this->result_dir_path.c_str());
            }
            #else
            if (mkdir(this->result_dir_path.c_str(), 0755)) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }
            #endif
        }
        this-> result_dir_path = this-> result_dir_path + "/" + result_dir_name;
        if(access(this->result_dir_path.c_str(), 0)){
            #if 0
            if (system(std::string("mkdir " + this->result_dir_path).c_str())) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }else{
                SLOGI("mkdir {}", this->result_dir_path.c_str());
            }
            #else
            if (mkdir(this->result_dir_path.c_str(), 0755)) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }
            #endif
        }
        SLOGI("result_dir_path:{}", this-> result_dir_path.c_str());

        // 创建素材路径  /var/TESTBED/testbed_objective/"parent_task_id"/msg_id/metrial/
        this-> metrial_dir =  this-> testbed_path + "/" + std::to_string(parent_task_id) ;
        this-> metrial_path =  this-> metrial_dir + "/" + std::to_string(msg_id);
        if(access(this->metrial_path.c_str(), 0)){
            // if (system(std::string("mkdir " + this->metrial_path).c_str())) {
            //     status = -1;
            //     SLOGE("mkdir fail! path:{}", this->metrial_path.c_str());
            // }else{
            //     SLOGI("mkdir {}", this->metrial_path.c_str());
            // }
            if (mkdir(this->metrial_path.c_str(), 0755)) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }
        }
        this-> metrial_path = this-> metrial_path + "/" + metrial_dir_name;
        if(access(this->metrial_path.c_str(), 0)){
            // if (system(std::string("mkdir " + this->metrial_path).c_str())) {
            //     status = -1;
            //     SLOGE("mkdir fail! path:{}", this->metrial_path.c_str());
            // }else{
            //     SLOGI("mkdir {}", this->metrial_path.c_str());
            // }
            if (mkdir(this->metrial_path.c_str(), 0755)) {
                status = -1;
                SLOGE("mkdir fail! path:{}", this->result_dir_path.c_str());
            }
        }
        SLOGI("metrial_path:{}", this-> metrial_path.c_str());

        // remote samba url
        this-> upload_result_dir_path = this-> upload_result_dir_path + "/" +  std::to_string(msg_id) + "/";
        SLOGI("upload_result_dir_path:{}", this-> upload_result_dir_path.c_str());

        // run_cmd
        //parse addtional cfg of testbed package
        std::string extended_cmd_str = "";
        #if 0
        {
            //name _configurations.json
            std::string testbed_cfg_file_path = fmt::format("{}/_configurations.json", testbed_path);
            if (fs::exists(testbed_cfg_file_path)) {
                try {
                    std::ifstream ifm(testbed_cfg_file_path);
                    std::string cfg_content = "";
                    std::string tmp_str = "";
                    while (std::getline(ifm, tmp_str)) {
                        cfg_content += tmp_str;
                    }
                    ifm.close();
                    SLOGD("get the cfg file content:{}", cfg_content);
                    
                    json js_root = json::parse(cfg_content);
                    json js_replace_array = json::array();
                    extended_cmd_str = js_root.at("formattedInputs").get<std::string>();
                    js_replace_array = js_root.at("configPath");
                    for (auto& replace_pair : js_replace_array) {
                        std::string file_name = replace_pair.at("file_name").get<std::string>();
                        std::string dst_dir = replace_pair.at("dst_dir").get<std::string>();
                        std::string src_file = fmt::format("{}/{}", testbed_path, file_name); 
                        std::string dst_file = fmt::format("{}/{}", dst_dir, file_name); ;
                        if (fs::exists(src_file)) {
                            if (fs::absolute(src_file) == fs::absolute(normal_path(dst_file))) {
                                SLOGI("path same, src file:{}, dst file:{}", src_file, dst_file);
                            }
                            else{
                                fs::rename(src_file, fs::absolute(normal_path(dst_file)));
                            }
                        }
                    }
                }
                catch (std::exception & e) {
                    SLOGE("error, testbed cfg file:{} exist, but parse error! {}", testbed_cfg_file_path, e.what());
                }
            }
        }
        #else
        extended_cmd_str = test_replace_file("_configurations.json", testbed_path) + testbed_cmd_append_str;
        #endif
        
        #if 0
        size_t lastindex = metrial_path_url.find_last_of("/\\");
        std::string material_filename = metrial_path_url.substr(lastindex + 1);
        std::string cd_md = "cd " +  testbed_path;
        std::string testbed_param = "123 dms " + metrial_path + "/" + material_filename + " " + result_dir_path + " " + metrial_path_url;
        #endif
        // run_cmd = cd_md + "&& chmod a+x * && ./" + testbed_name +" " + testbed_param;
        // new zjx9083
        auto cur_root_dir = LOG_INSTANCE().get_cur_log_dir_t();
        fs::path testbed_folder_Path = std::string(cur_root_dir.dir) + std::string("/testbed");
        try {
            fs::create_directory(testbed_folder_Path);
            SLOGW("testbed子文件夹创建成功");
        } catch (const std::exception& e) {
            SLOGE("testbed无法创建子文件夹-{}", e.what());
            testbed_folder_Path = cur_root_dir.dir;
        }
        //generate execute command
        std::string camera_type = "dms";
        size_t lastindex = metrial_path_url.find_last_of("/\\");
        std::string material_filename = metrial_path_url.substr(lastindex + 1);
        std::string material_path = fmt::format("{}/{}", metrial_path, material_filename);
        std::string testbed_function = "non";
        //有的包用了TESTBED_PALTFORM 作为平台参数，所有二选一
        auto func_get_testbed_name = [&](const std::string& first_name, const std::string& second_name, std::string& out_name) {
            bool is_first_name = true;
            std::string out_str = fmt::format("{}/{}", testbed_path, first_name);
            if (!fs::exists(out_str)) {
                out_str = fmt::format("{}/{}", testbed_path, second_name);
                is_first_name = false;
            }
            out_name = out_str;
            return is_first_name;
        };

        std::string testbed_uniform_log_path = fmt::format("{}/testbed_{}.log", testbed_folder_Path.string(), parent_task_id);
        std::string testbed_redirect_log_path = fmt::format("{}/{}.log", testbed_folder_Path.string(), fs::path(material_filename).stem().string());
        testbed_uniform_log_path = testbed_redirect_log_path;

        static const std::string old_testbed_name = "TESTBED_MAIN";
        static const std::string new_testbed_name = "TESTBED_PLATFORM";
        std::string cur_testbed_path;

        if (material_type == "dms" || material_type == "oms") {
            camera_type = material_type;
            testbed_function = "warning_Event";
            bool is_first = func_get_testbed_name(new_testbed_name, old_testbed_name, cur_testbed_path);
            // bool is_first = func_get_testbed_name(old_testbed_name, new_testbed_name, cur_testbed_path);
            if (is_first) {
                run_cmd = fmt::format("cd {} && chmod a+x * && {}  --module={}  --function={} --materialpath={}  --resultpath={}  --taskname=task1 --fixedtimestamp=true  --materialname={} --logEnable=false  {} >> {}",
                    testbed_path,  cur_testbed_path, camera_type, testbed_function, material_path, result_dir_path, metrial_path_url, extended_cmd_str, testbed_uniform_log_path);
            }
            else {
                run_cmd = fmt::format("cd {} && chmod a+x * && {} 123 {}  {} {} {} {} >> {}",
                    testbed_path, cur_testbed_path, camera_type, material_path, result_dir_path, metrial_path_url, extended_cmd_str, testbed_uniform_log_path);
            }
        }
        else if (material_type == "register") {
            camera_type = "dms";
            testbed_function = "face_DeleteAll";
            bool is_first = func_get_testbed_name(new_testbed_name, old_testbed_name, cur_testbed_path);
            // std::string cur_testbed_path = func_get_testbed_name( new_testbed_name, old_testbed_name);
            if (msg_id == 0) {
                //if first material, to clean all
                run_cmd = fmt::format("cd {} && chmod a+x * && {} --module={}  --function={}  --fixedtimestamp=true --materialname={} --logEnable=false {} >> {}",
                    testbed_path,  cur_testbed_path, camera_type, testbed_function, metrial_path_url, extended_cmd_str, testbed_uniform_log_path);
            }
            //continue
            //xjf 2023/2/28 modify face_Register_one_delete to face_Register
            // run_cmd = fmt::format("cd {} && chmod a+x * && {}  --module={}  --function=face_Register_one_delete --materialpath={}  --resultpath={}  --taskname=task1 --fixedtimestamp=true  --materialname={} --logEnable=false >> {}",
            run_cmd = fmt::format("cd {} && chmod a+x * && {}  --module={}  --function=face_Register --materialpath={}  --resultpath={}  --taskname=task1 --fixedtimestamp=true  --materialname={} --logEnable=false {} >> {}",
                testbed_path,  cur_testbed_path, camera_type, material_path, result_dir_path, metrial_path_url, extended_cmd_str, testbed_uniform_log_path);
        }
        else if (material_type == "recognize") {
            camera_type = "dms";
            testbed_function = "face_Recognize";
            bool is_first = func_get_testbed_name(new_testbed_name, old_testbed_name, cur_testbed_path);
            // std::string cur_testbed_path = func_get_testbed_name( new_testbed_name, old_testbed_name);
            run_cmd = fmt::format("cd {} && chmod a+x * && {} --module={}  --function={} --materialpath={}  --resultpath={}  --taskname=task2 --fixedtimestamp=true  --materialname={} --logEnable=false {} >> {}",
                testbed_path,  cur_testbed_path, camera_type, testbed_function, material_path, result_dir_path, metrial_path_url, extended_cmd_str, testbed_uniform_log_path);
        }
        else if (material_type == "algorithm") {
            camera_type = "algorithm";
            testbed_function = "warning_Event";
            bool is_first = func_get_testbed_name(new_testbed_name, old_testbed_name, cur_testbed_path);
            if (is_first) {
                run_cmd = fmt::format("cd {} && chmod a+x * && {} --module={}  --function={} --materialpath={}  --resultpath={}  --taskname=task2 --fixedtimestamp=true  --materialname={} --logEnable=false {} >> {}",
                testbed_path,  cur_testbed_path, camera_type, testbed_function, material_path, result_dir_path, metrial_path_url, extended_cmd_str, testbed_uniform_log_path);
            }
            else {
                SLOGE("error, expect exe:{} not exist", new_testbed_name);
            }
        }
        SLOGW("run testbed system enter, msgid:{} material type:{} cmd:{}, cmd_size:{}",msg_id, material_type, run_cmd, run_cmd.size());

        // auto& cmd_parser = TestbedCmdParser::ins();
        auto cmd_parser = TestbedCmdParser{};
        //builtin
        cmd_parser.push_buitin_var_value(CVAR_LOCAL_MATERIAL_PATH, testbed_path);
        cmd_parser.push_buitin_var_value(CVAR_MATERIAL_URL, metrial_path_url);
        cmd_parser.push_buitin_var_value(CVAR_RESULT_DIR, result_dir_path);
        cmd_parser.push_buitin_var_value(CVAR_MSG_ID, msg_id);
        //addtion
        // run_cmd = run_cmd + " " + extended_cmd_str;
        //cfg var
        #if 0
        cmd_parser.push_cfg_var_value("cfgxxx", "cfgxxx");
        cmd_parser.push_cfg_var_value("cfgxxx", "cfgxxx");
        cmd_parser.push_cfg_var_value("cfgxxx", "cfgxxx");
        std::string use_cmd = cmd_parser.gen_replaced_cmd("cfgxxxx");
        run_cmd = use_cmd;
        #endif
    }
    int get_status(){return status;}
    // download
    std::string get_metrial_path(){return metrial_path;}
    std::string get_metrial_path_url(){return metrial_path_url;}
    // run
    std::string get_run_cmd(){return run_cmd;}
    // upload
    std::string get_upload_result_dir_path(){return upload_result_dir_path;}
    std::string get_result_dir_path(){return result_dir_path;}
    std::string get_metrial_dir(){return metrial_dir;}
private:
    int status;

    int parent_task_id;
    int msg_id;

    std::string testbed_root_dir_path; // "/var/TESTBED"
    std::string testbed_dir_name;      // "testbed_objective"
    std::string testbed_name;          // "TESTBED_MAIN"
    std::string testbed_path;          // /var/TESTBED/testbed_ec24

    std::string run_cmd;

    std::string metrial_dir_name; // "metrial"
    std::string metrial_path_url;
    std::string material_type;
    std::string metrial_path;     // /var/TESTBED/testbed_ec24/"parent_task_id"/"sub_task_id"/metrial
    std::string metrial_dir;      // /var/TESTBED/testbed_ec24/"parent_task_id"

    std::string result_dir_path;  // /var/TESTBED/testbed_ec24/"parent_task_id"/"sub_task_id"/result/metrial_name
    std::string result_dir_name;  // "result"
    std::string upload_result_dir_path; // "smb://172.17.11.202/objective_result"
    std::string ret_zip_file_path;
};

#endif
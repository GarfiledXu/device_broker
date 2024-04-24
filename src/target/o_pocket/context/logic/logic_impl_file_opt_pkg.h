#include "logic_impl_file_opt.h"

//./new_service function mearsure_url_space --url=http://172.17.11.189:30080/versionZip/FaceDetect/1.1.1.1//FD_TESTBED_1.0.1.zip --dst_dir=/var/i30_objective/objective/test_dir/
class Cli11Option_mearsure_url_space : public Cli11OptionBase
{
public:
    std::string url;
    std::string dst_dir;
    std::string sub_cmd_name = "mearsure_url_space";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "mearsure_url_space");
        cur_sub->add_option("--url", url, "http url") -> required(true);
        cur_sub->add_option("--dst_dir", dst_dir, "dst dir") -> required(true);
    };
    virtual int call_funtion() override {
        int ret = url_space_measure(url, dst_dir);
        if (ret) {
            SLOGE("call mearsure_url_space fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};

//./new_service function unzip_testbed --url=http://172.17.11.189:30080/versionZip/FaceDetect/1.1.1.1//FD_TESTBED_1.0.1.zip --dst_dir=/var/i30_objective/objective/test_dir/ --cache_dir=/var/i30_objective/objective/tmp_dir/
class Cli11Option_unzip_testbed : public Cli11OptionBase
{
public:
    std::string url;
    std::string dst_dir;
    std::string cache_dir;
    std::string sub_cmd_name = "unzip_testbed";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "unzip testbed");
        // auto* cur_sub = inapp.add_subcommand("unzip_testbed", "unzip testbed");
        cur_sub->add_option("--url", url, "http url") -> required(true);
        cur_sub->add_option("--dst_dir", dst_dir, "dst unzip dir") -> required(true);
        cur_sub->add_option("--cache_dir", cache_dir, "cache dir") -> required(true);
    };

    virtual int call_funtion() override {
        int ret = unzip_testbed(url, dst_dir, cache_dir);
        if (ret) {
            SLOGE("call_function_unzipfile");
            return -1;
        }
        return 0;
    };

    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};

//./new_service function query_file_size --path=/var/i30_objective/objective/test_dir/testbed_objective
class Cli11Option_query_file_size : public Cli11OptionBase
{
public:
    std::string path;
    std::string sub_cmd_name = "query_file_size";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "query_file_size");
        cur_sub->add_option("--path", path, "local path, file or dir") -> required(true);
    };
    virtual int call_funtion() override {
        std::size_t out_size = 0;
        std::size_t out_folder_num = 0;
        std::size_t out_file_num = 0;
        int ret = query_file_size(path, out_size, out_folder_num, out_file_num);
        if (ret) {
            SLOGE("call query_file_size fail, ret:{}", ret);
            return -1;
        }
        SLOGI("get file size byte:{}, folder num:{}, file num:{}", out_size, out_folder_num, out_file_num);
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};

//./new_service function query_dir_remain_space --path=/var/i30_objective/objective/test_dir/testbed_objective
class Cli11Option_query_dir_remain_space : public Cli11OptionBase
{
public:
    std::string path;
    std::string sub_cmd_name = "query_dir_remain_space";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "query_dir_remain_space");
        cur_sub->add_option("--path", path, "local path, file or dir") -> required(true);
    };
    virtual int call_funtion() override {
        std::size_t out_size = 0;
        int ret = query_dir_remain_space(path, out_size);
        if (ret) {
            SLOGE("call query_dir_remain_space fail, ret:{}", ret);
            return -1;
        }
        SLOGI("query_dir_remain_space size byte:{}", out_size);
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};


class Cli11Option_mv_file : public Cli11OptionBase
{
public:
    std::string src_file;
    std::string dst_dir;
    bool is_check_src_file;
    std::string sub_cmd_name = "mv_file";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "download");
        cur_sub->add_option("--src_file", src_file, "src_file") -> required(true);
        cur_sub->add_option("--dst_dir", dst_dir, "dst_dir") -> required(true);
        cur_sub->add_option("--is_check_src_file", is_check_src_file, "is_check_src_file") -> required(true);
    };
    virtual int call_funtion() override {
        int ret = mv_file_to_target(src_file, dst_dir, is_check_src_file);
        if (ret) {
            SLOGE("call mv_file_to_target fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};


//./new_service function http_download --url=http://172.17.11.189:30080/versionZip/FaceDetect/1.1.1.1//FD_TESTBED_1.0.1.zip --dst_file=/var/i30_objective/objective/test_dir/tt.zip
class Cli11Option_download_http : public Cli11OptionBase
{
public:
    std::string url;
    std::string dst_file;
    std::string sub_cmd_name = "http_download";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "download");
        cur_sub->add_option("--url", url, "http url") -> required(true);
        cur_sub->add_option("--dst_file", dst_file, "dst file name") -> required(true);
    };
    virtual int call_funtion() override {
        int ret = http_download(url, dst_file);
        if (ret) {
            SLOGE("call http download fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};



//./new_service function http_filesize --url=http://172.17.11.189:30080/versionZip/FaceDetect/1.1.1.1//FD_TESTBED_1.0.1.zip 
class Cli11Option_http_filesize : public Cli11OptionBase
{
public:
    std::string url;
    std::string sub_cmd_name = "http_filesize";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "file size");
        cur_sub->add_option("--url", url, "http url") -> required(true);
    };
    virtual int call_funtion() override {
        std::size_t out_size = 0;
        int ret = http_file_size(url, out_size);
        if (ret) {
            SLOGE("call http file size fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }
};



//./new_service function  smb_download --url=smb://172.17.11.202/objective_result/1645/1645/0/result.txt  --dst_dir=./test --user=yhw9826 --wg=arcsoft-hz --passwd=Yhw@2023@
//./new_service function  smb_download --url=smb://172.17.10.122/Arcsoft-hz_facesample/DMS/打哈欠/test/CS1E-DMS_1_02_0330389c9cf4bbcb3e67a090639ff8de.jpg  --dst_dir=./test --user=yhw9826 --wg=arcsoft-hz --passwd=Yhw@2023@
//./new_service function  smb_download --url=smb://172.17.10.122/arcsoft-hz_facesample/dms/打哈欠/test/cs1e-dms_1_02_0330389c9cf4bbcb3e67a090639ff8de.jpg  --dst_dir=./test --user=yhw9826 --wg=arcsoft-hz --passwd=Yhw@2023@
class Cli11Option_smb_download : public Cli11OptionBase
{
public:
    std::string url;
    std::string dst_dir;
    std::string user;
    std::string wg;
    std::string passwd;
    std::string sub_cmd_name = "smb_download";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "smb_download");
        cur_sub->add_option("--url", url, "url") -> required(true);
        cur_sub->add_option("--dst_dir", dst_dir, "dst_dir") -> required(true);
        cur_sub->add_option("--user", user, "user") -> required(true);
        cur_sub->add_option("--wg", wg, "wg") -> required(true);
        cur_sub->add_option("--passwd", passwd, "passwd") -> required(true);
    };
    virtual int call_funtion() override {
        int ret = smb_download(url, dst_dir, user, wg, passwd);
        if (ret) {
            SLOGE("call mv_file_to_target fail, ret:{}", ret);
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};


//./new_service function update_testbed_and_replace --url=http://172.17.11.202//cabin_data//testbed/3824/Geely-CX11-DMS_PLATFORM_v1.0.5_build20240411.zip --dst_dir=/var/TESTBED/testbed_objective --cache_dir=/var/tmp_dir
class Cli11Option_update_testbed_and_replace : public Cli11OptionBase
{
public:
    std::string url;
    std::string dst_dir;
    std::string cache_dir;
    std::string sub_cmd_name = "update_testbed_and_replace";

    virtual int to_add_option(CLI::App& inapp) override {
        auto* cur_sub = inapp.add_subcommand(sub_cmd_name, "unzip testbed");
        // auto* cur_sub = inapp.add_subcommand("unzip_testbed", "unzip testbed");
        cur_sub->add_option("--url", url, "http url") -> required(true);
        cur_sub->add_option("--dst_dir", dst_dir, "dst unzip dir") -> required(true);
        cur_sub->add_option("--cache_dir", cache_dir, "cache dir") -> required(true);
    };
    virtual int call_funtion() override {
        int ret = update_testbed_and_replace(url, dst_dir, cache_dir, {});
            // , { {"/var/TESTBED/testbed_objective/libavcodec.so.60", "/etc/images/dsp"} }
        // );
        if (ret) {
            SLOGE("call_function_unzipfile");
            return -1;
        }
        return 0;
    };
    virtual std::string get_sub_cmd_name() override {
        return sub_cmd_name;
    }

};
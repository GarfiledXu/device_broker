#pragma once
#include "CLI11.hpp"
#include "fmt_test.h"
#include "log.h"


#define COLOR_WHITE "\033[0;37m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_BLUE "\033[34m"

struct platform_cmd {
    std::string module;
    std::string function;
    bool fixetimestamp;
    std::string materialpath;
    std::string materialname;
    std::string resultpath;
    std::string taskname;
    bool logEnable;
};
/**
 *@brief 
 * @param argc 
 * @param argv 
 * @param platform_cmd 
 * @return int 
 *  ./TESTBED_PLATFORM --module=dms --function=test --materialpath="xxx.jpg" --materialname="http:xxx.jpg" --resultpath="./result_dir" 
 */
int platform_entry(int argc, char** argv, platform_cmd& platform_cmd) {
    std::string arg_msg = "";
    for (int i = 0; i < argc; i++) 
        arg_msg += fmt::format(" {} ", argv[i]);
    SLOGW("enter platform entry, cmd content:\n{}", arg_msg);

    std::string help_msg = fmt::format("\n"COLOR_WHITE"{} command line tool help message:\n"COLOR_GREEN"{}developer:{}"COLOR_WHITE
        , "BYD tool for platform"
        , "sample: exe --module=dms --function=warnning_event --materialpath=./ID13024_BYDDMS_ShortDistract_CommonCaseID_129_000001_06259.mp4 --materialname=xx --resultpath=./result"
        , "xjf2613\n");
    CLI::App cli_root{help_msg};
    cli_root.failure_message([&](const CLI::App *, const CLI::Error &e)->std::string{
        return fmt::format("\n"COLOR_WHITE"parser fail!"COLOR_RED"\n{}\n{}\n", e.what(), help_msg);
    });
    cli_root.allow_extras();

    // platform_cmd platform_cmd{};

    //platform
    cli_root.add_option("--module", platform_cmd.module, "dms oms") -> required(true);
    cli_root.add_option("--function", platform_cmd.function, "face or warnning evnet") -> required(true) ;
    cli_root.add_option("--materialpath", platform_cmd.materialpath, "local material path") -> required(true);
    cli_root.add_option("--materialname", platform_cmd.materialname, "remote url, which used in record result message") -> required(true);
    cli_root.add_option("--resultpath", platform_cmd.resultpath, "result path") -> required(true);
    cli_root.add_option("--taskname", platform_cmd.taskname, "task name") -> required(false);
    // cli_root.add_flag("--fixetimestamp", platform_cmd.fixetimestamp, "switch: true or false") -> required(false);
    cli_root.add_flag("--fixedtimestamp", platform_cmd.fixetimestamp, "switch: true or false") -> required(false);
    cli_root.add_flag("--logEnable", platform_cmd.logEnable, "switch: true or false") -> required(false);
    //sdk addtion


    try {
        SLOGD("enter CLI11 PARSE");
        CLI11_PARSE(cli_root, argc, argv);
        SLOGD("out CLI11 PARSE");
        SLOGW("parse result:\nmodeul:{}, function:{}, fixetimestamp:{}, materialpath:{}, materialname:{}, resultpath:{}, taskname:{}, logEnable:{}"
        , platform_cmd.module, platform_cmd.function, platform_cmd.fixetimestamp, platform_cmd.materialpath, platform_cmd.materialname, platform_cmd.resultpath, platform_cmd.taskname, platform_cmd.logEnable);
    }
    catch (std::exception& e) {
        SLOGE("cli11 parse error! {}\n will return main -1", e.what());
        return -1;
    }


    //exe --module=dms --function=warnning_event --materialpath=xx -- materialname=xx -resultpath=xx 
    std::string file_extension = fs::path(platform_cmd.materialpath).extension().string();
    if (file_extension != ".jpg" && file_extension != ".png" && file_extension != ".mp4") {
        SLOGE("local material file, format error, path:{}, extension:{}", platform_cmd.materialpath, file_extension);
        return -2;
    }

    // if (file_extension == ".jpg" || file_extension == ".png") {
    // }
    // else if (file_extension == ".mp4") {
    // }
    // SLOGW("main function will return 0");
    SLOGW("will return the platform param");

    return 0;
}
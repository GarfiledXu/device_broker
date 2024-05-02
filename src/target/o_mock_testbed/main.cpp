#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include "cmd_entry.h"
#include "fmt_test.h"

int simple_sleep_success_run(int argc, char** argv) {
    
    printf("enter mock testbed\n");

    platform_cmd cur_platform_cmd;
    platform_entry(argc, argv, cur_platform_cmd);

    std::string arg_str = fmt::format("pid: [{}]\n", getpid());
    for (int i = 0;i < argc;i++) {
        arg_str += fmt::format("argc [{}]: [{}]\n", i, argv[i]);
    }
    printf("%s", arg_str.c_str());

    //do someting
    printf("will sleep 10s testbed\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 5));
    if (!fs::exists(cur_platform_cmd.resultpath)) {
        printf("reslt dir:%s not exist, will auto create...\n", cur_platform_cmd.resultpath.c_str());
        fs::create_directories(cur_platform_cmd.resultpath);
    }
    std::string result_path = cur_platform_cmd.resultpath + "/result.txt";
    std::ofstream outFile(result_path);
    if (outFile.is_open()) {
        outFile << arg_str;
        outFile.close();
    } else {
        std::cout << "can't read to file path: " << result_path << std::endl;
    }
    printf("end sleep 10s testbed\n");

    printf("out mock testbed\n");
    return 0;

}

int main(int argc, char** argv) {

    simple_sleep_success_run(argc, argv);
    return 0;

}
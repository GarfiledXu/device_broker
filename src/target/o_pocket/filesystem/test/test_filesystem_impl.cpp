#pragma once
#include "gtest/gtest.h"
#include "filesystem_impl.inl"

//create test folder and file
inline void create_env() {

}
inline void destroy_env() {

}
START_NAMESPACE(fs_impl)
//fast test
inline void test_filesystem(int argc, char** argv) {
    #if 0
    int ret = 0;
    auto start_time = std::chrono::steady_clock::now();

    if (std::string(argv[1]) == "1") {
        size_t out_space = 0;
        size_t out_folder_num = 0;
        size_t out_file_num = 0;
        ret = obtain_file_space(argv[2], out_space, out_folder_num, out_file_num);
        std::cout << "space byte:" << out_space <<  " folder num:"<< out_folder_num<< " file num:"<< out_file_num<< std::endl;
    }
    else if (std::string(argv[1]) == "2") {
        size_t out_space = 0;
        ret = obtain_folder_remain_space(argv[2], out_space);
        std::cout << "remain space byte:" << out_space << std::endl;
    }
    else if (std::string(argv[1]) == "3") {
        ret = clean_folder(argv[2]);
    }
    else if (std::string(argv[1]) == "4") {
        //目标文件夹干净
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 1 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 1 0
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 0 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 0 0
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 1 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 1 0
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 0 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 0 0
        //目标文件夹不干净
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 1 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 1 0
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 0 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  1 0 0
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 1 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 1 0
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 0 1
        //rm -rf ./log_copyed && rm -rf ./log_moved && cp -rf ./log ./log_copyed && cp -rf ./log ./log_moved &&  ./e03_api_test_param 4 /home/PrivacyMosaic/log_copyed /home/PrivacyMosaic/log_moved  0 0 0
        ret = move_file(argv[2], argv[3], std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]));
    }
    else if (std::string(argv[1]) == "5") {
        ret = copy_file(argv[2], argv[3], std::stoi(argv[4]), std::stoi(argv[5]));
    }
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Time taken: " << duration.count() << " milliseconds ret:" << ret<< std::endl;
    #endif
}
END_NAMESPACE(fs_impl)

#ifndef GF_FILESYSTEM_TEST_HPP
#define GF_FILESYSTEM_TEST_HPP
#include "ghc/filesystem.hpp"
namespace fs = ghc::filesystem;

inline void test_filesystem() {
    int argc;
    char* argv1[] = { "xxx" };
    char** argv = argv1;
    fs::u8arguments u8guard(argc, argv);
    if(!u8guard.valid()) {
        // std::cout << "Bad encoding, needs UTF-8." << std::endl;
        exit(EXIT_FAILURE);
    }
}







#endif

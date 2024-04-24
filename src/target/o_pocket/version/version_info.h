#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "compile_info.h"

#define VERSION "0.0.1"
static const char* development_log = R"(
    
)";

inline int version_info(int argc, char** argv) {
    if (argc == 2) {
        if (!strcmp(argv[1],  "-v")) {
            printf("\n    build data:%s\n    version:%s\n", BUILD_DATE, VERSION);
            return 0;
        }
        else if (!strcmp(argv[1], "-l")) {
            printf("\n%s\n", development_log);
            return 0;
        }
    }
}
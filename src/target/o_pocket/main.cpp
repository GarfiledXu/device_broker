#include <stdlib.h>
#include <stdio.h>
#include "gtest.h"
#include "cmd_entry.h"
#include "signal_handle.h"

int main(int argc, char** argv) {

    REGISTER_SIGINT_HANDLE();
    return cmd_entry(argc, argv);

    return 0;
}
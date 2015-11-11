// Copyright 2010-2012 RethinkDB, all rights reserved.
#include "utils.hpp"
#include "unittest/gtest.hpp"
#include "extproc/extproc_spawner.hpp"

// TODO ATN

#ifdef _WIN32

void open_console() {
    AllocConsole();
    freopen("conin$", "r", stdin);
    freopen("conout$", "w", stdout);
    freopen("conout$", "w", stderr);
}

void close_console() {
    printf("Press return to exit...");
    fflush(stdout);
    getchar();
}

// TODO ATN: this doesn't do a graceful shutdown
BOOL unittest_ctrl_c(DWORD type) {
    // TODO: abort other threads with stack trace
    if (type == CTRL_C_EVENT || type == CTRL_BREAK_EVENT) {
        crash("^C");
        return true;
    }
    return false;
}

#endif

int main(int argc, char **argv) {
    startup_shutdown_t startup_shutdown;
#ifdef _WIN32
    SetConsoleCtrlHandler(unittest_ctrl_c, true);
#endif

#ifdef _WIN32
    extproc_maybe_run_worker(argc, argv);
#endif

    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}

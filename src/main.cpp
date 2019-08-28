/*
On unit tests:
Testing is done using added 'Test' build configuration which
excludes this main.cpp file from it's build, but builds
it's own files from 'src/test' directory, with test_main.cpp being the main one.
In 'Debug' and 'Release' builds those unit test files are excluded.
*/
#include <stdexcept>
#include "application.h"
#include "util/log.h"

int main() {
    try {
        Application app;
        app.Run();
    }
    catch (const std::exception &e) {
        util::Log::Error("Exception: ", e.what());
        return 1;
    }
    catch (...) {
        util::Log::Error("Unknown error");
        return 1;
    }
}
/*
    Unit testing is done using Catch2 framewrok.
    This file is the 'main' file of testing where Catch includes
    it's own main function.
    To run tests acivate 'Test' build configuration as it will remove 
    apps main.cpp file from build so this one becomes application entry point.
*/

// Let Catch provide main():
// It accepts and responds to command line arguments
// NOTE: don't define this macro anywhere else in code.
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "FunctionalTestAssembler.h"
//#include "FileSystem.h"
#include <iostream>

int main(int argc, char **argv)
{
    std::string test_name;
    if(argc > 1) {
        test_name = std::string(argv[1]);
    }
    return ADVANCED_FUNCTIONAL_TEST(test_name);
}

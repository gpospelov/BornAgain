#include "fit_functional_tests.h"

//! The main function of CoreSuite to run functional tests
int main(int argc, char **argv)
{
    std::string test_name;
    if(argc > 1) {
        test_name = std::string(argv[1]);
    }
    return fit_functional_test(test_name);
}

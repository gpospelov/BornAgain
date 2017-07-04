#include <iostream>
#include "CoreIOTest.h"

bool run_tests() {
     bool success = CoreIOTest().runTest();
    return success;
}

int main()
{
    return run_tests() == true ? 0 : 1;
}


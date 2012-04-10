#include <iostream>
#include <string>
#include "TestFresnelCoeff.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello Brave New World!" << endl;

    if(argc>=2) {
        std::string spar(argv[1]);
        if(spar.find("fresnel") != std::string::npos) {
            TestFresnelCoeff test;
            test.execute();
        }
    }

    return 0;
}


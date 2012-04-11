#include <iostream>
#include <string>
#include "TestFresnelCoeff.h"
#include "TApplication.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello Brave New World!" << endl;

    if(argc>=2) {
        std::string spar(argv[1]);

        // user algorithm to test reflection/refraction coefficients for multilayer system
        if(spar.find("fresnel") != std::string::npos) {
            TestFresnelCoeff test;
            test.execute();
        }
    }

    if(gApplication) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        gApplication->Run();
    }
    return 0;
}


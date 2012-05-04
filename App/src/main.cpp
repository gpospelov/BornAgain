#include <iostream>
#include <string>
#include "TestFresnelCoeff.h"
#include "TestDiffuseScattering.h"
#include "TestFormFactor.h"
#include "TestRoughness.h"
#include "DrawHelper.h"

#include "TApplication.h"


int main(int argc, char **argv)
{
    std::cout << "Hello Brave New World!" << std::endl;
    TApplication theApp("theApp",0,0);
    DrawHelper::SetStyle();

    if(argc>=2) {
        std::string spar(argv[1]);

        // user algorithm to test reflection/refraction coefficients for multilayer system
        if(spar.find("fresnel") != std::string::npos) {
            TestFresnelCoeff test;
            test.execute();
        }

        // user algorithm to test cross-section for diffuse (uncoherent) scattering
        if(spar.find("diffuse") != std::string::npos) {
            TestDiffuseScattering test;
            test.execute();
        }

        // user algorithm to test the form factor calculation
        if(spar.find("formfactor") != std::string::npos) {
            TestFormFactor test;
            test.execute();
        }

        // user algorithm to test roughness
        if(spar.find("roughness") != std::string::npos) {
            TestRoughness test;
            test.execute();
        }


    }

    if(gApplication) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        gApplication->Run();
    }
    return 0;
}



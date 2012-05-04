#include <iostream>
#include <string>
#include "TestFresnelCoeff.h"
#include "TestDiffuseScattering.h"
#include "TestFormFactor.h"
#include "TestDWBAFormFactor.h"
#include "TestRoughness.h"
#include "DrawHelper.h"

#include "TApplication.h"

bool exists(int argc, char **argv, const std::string &stext);

int main(int argc, char **argv)
{
    std::cout << "Hello Brave New World!" << std::endl;
    TApplication theApp("theApp", &argc, argv);

    DrawHelper::SetStyle();

    // user algorithm to test reflection/refraction coefficients for multilayer system
    if( exists(argc, argv, "fresnel") ) {
        TestFresnelCoeff test;
        test.execute();
    }

    // user algorithm to test cross-section for diffuse (uncoherent) scattering
    if( exists(argc, argv, "diffuse") ) {
        TestDiffuseScattering test;
        test.execute();
    }

    // user algorithm to test the form factor calculation
    if( exists(argc, argv,"formfactor") ) {
        TestFormFactor test;
        test.execute();
     }

    // user algorithm to test roughness
    if( exists(argc, argv, "roughness") ) {
        TestRoughness test;
        test.execute();
    }

    if( exists(argc, argv, "dwba") ) {
        TestDWBAFormFactor test;
        test.execute();
    }

    if( exists(argc, argv, "report") ) {
        DrawHelper::SaveReport();
    }

    if(gApplication) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        gApplication->Run();
    }
    return 0;
}



/* ************************************************************************* */
// check existance
/* ************************************************************************* */
bool exists(int argc, char **argv, const std::string &stext)
{
    if(argc<=1) return false;

    for(int i=1; i<argc; i++) {
        std::string spar(argv[i]);
        if( spar.find(stext) != std::string::npos ) return true;
    }
    return false;
}

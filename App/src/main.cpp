#include "FunctionalTestFactory.h"
#include "DrawHelper.h"
#include "CommandLine.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include "TROOT.h"
#include "TApplication.h"
#include "ProgramOptions.h"
#include "AppOptionsDescription.h"
#include "Macros.h"

int main(int argc, char **argv)
{
    std::cout << "Hello Brave New World!" << std::endl;
    ProgramOptions::instance().parseCommandLine(argc, argv);

    // setting graphics environment
    TApplication *theApp(0);
    if( ProgramOptions::instance().find("batch") ) {
        gROOT->SetBatch(true);
    } else {
        theApp = new TApplication("theApp", 0, 0);
        DrawHelper::SetStyle();
    }

    // running functional tests
    if( ProgramOptions::instance().find("all") ) {
        // running all registered tests
        FunctionalTestFactory::instance().execute_all();

    } else {
        // loop over functional tests, run test if it's name is present in command line
        FunctionalTestFactory::iterator it = FunctionalTestFactory::instance().begin();
        for(; it!= FunctionalTestFactory::instance().end(); ++it) {
            if( ProgramOptions::instance().find( (*it).first ) )
                FunctionalTestFactory::instance().execute( (*it).first );
        }
    }

    // saving report in pdf and root
    if( ProgramOptions::instance().find("report") ) {
        DrawHelper::instance().saveReport();
    }

    // exit now if there is unrecognized options or plead for help
    if( !ProgramOptions::instance().isConsistent() ) return 0;

    // holding graphics if not in the batch mode
    if(gApplication && !gROOT->IsBatch() ) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        gApplication->Run();
    }

    return 0;
}


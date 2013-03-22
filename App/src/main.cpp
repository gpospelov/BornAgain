#include "FunctionalTestFactory.h"
#include "DrawHelper.h"
#include "ProgramOptions.h"
#include "AppOptionsDescription.h"
#include "CoreOptionsDescription.h"
#include "Version.h"
#include "MessageService.h"

#include <iostream>
#include <string>
#include "TROOT.h"
#include "TApplication.h"

#ifdef DEBUG_FPE
#include <fenv.h>
#ifdef Q_OS_MAC
#include "fp_exception_glibc_extension.h"
#endif
#endif

int main(int argc, char **argv)
{
#ifdef DEBUG_FPE
    std::cout << "main() -> Enabling floating point exception debugging" << std::endl;
    feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
#endif
    std::cout << AppVersion::g_app_name << " "
              << AppVersion::g_app_version_number << std::endl;

    ProgramOptions command_line_options;
    AddApplicationOptions(&command_line_options);
    AddCoreOptions(&command_line_options);
    command_line_options.parseCommandLine(argc, argv);

    MSG::SetLevel(command_line_options["msgsvc"].as<std::string>());

    // setting graphics environment
    TApplication *theApp(0);
    if( command_line_options.find("batch") ) {
        (void)theApp;
        gROOT->SetBatch(true);
    } else {
        theApp = new TApplication("theApp", 0, 0);
        DrawHelper::SetStyle();
    }

    // running functional tests
    if( command_line_options.find("all") ) {
        // running all registered tests
        FunctionalTestFactory::execute_all(&command_line_options);

    } else {
        // loop over functional tests, run test if it's name is present in command line
        FunctionalTestFactory::iterator it = FunctionalTestFactory::begin();
        for(; it!= FunctionalTestFactory::end(); ++it) {
            if( command_line_options.find( (*it).first ) )
                FunctionalTestFactory::execute( (*it).first, &command_line_options );
        }
    }

    // saving report in pdf and root
    if( command_line_options.find("report") ) {
        DrawHelper::saveReport();
    }

    // exit now if there is unrecognized options or plead for help
    if( !command_line_options.isConsistent() ) return 0;

    // holding graphics if it exists
    if( theApp ) {
        std::cout << "main() -> Info. Holding graphics, press ctrl-C to exit..." << std::endl;
        theApp->Run();
    }

    return 0;
}


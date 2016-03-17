// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/main.cpp
//! @brief     Universal test program
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ApplicationTestFactory.h"
#include "DrawHelper.h"
#include "ProgramOptions.h"
#include "AppOptionsDescription.h"
#include "CoreOptionsDescription.h"
#include "BAVersion.h"
#include "MessageService.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include "TROOT.h"
#include "TApplication.h"

//! Universal test program.

int main(int argc, char **argv)
{
    Utils::EnableFloatingPointExceptions();

    std::cout << BornAgain::GetName() << " "
              << BornAgain::GetVersionNumber() << std::endl;

    ApplicationTestFactory test_factory;
    RegisterApplicationTests(&test_factory);

    ProgramOptions command_line_options;
    AddApplicationOptions(&command_line_options, &test_factory);
    AddCoreOptions(&command_line_options);
    command_line_options.parseCommandLine(argc, argv);

    if(command_line_options.getVariables().count("msglog"))
        MSG::SetLevel(command_line_options["msglog"].as<std::string>());

    // set graphics environment
    TApplication *theApp(0);
    if( command_line_options.find("batch") ) {
        (void)theApp;
        gROOT->SetBatch(true);
    } else {
        theApp = new TApplication("theApp", &argc, argv);
        DrawHelper::SetStyle();
    }

    // run functional tests
    if( command_line_options.find("all") ) {
        // run all registered tests
        test_factory.execute_all(&command_line_options);

    } else {
        // loop over functional tests,
        // run test if its name is present in command line
        ApplicationTestFactory::iterator it = test_factory.begin();
        for(; it!= test_factory.end(); ++it) {
            if( command_line_options.find( (*it).first ) )
                test_factory.execute(
                    (*it).first, &command_line_options );
        }
    }

    // save report in pdf and root
    if( command_line_options.find("report") ) {
        DrawHelper::saveReport();
    }

    // exit now if there is unrecognized options or plead for help
    if( !command_line_options.isConsistent() ) return 0;

    // hold graphics if it exists
    if( theApp ) {
        std::cout
            << "main() -> Info. Holding graphics, press ctrl-C to exit..."
            << std::endl;
        theApp->Run();
    }

    return 0;
}




#include "AppOptionsDescription.h"
#include "ProgramOptions.h"
#include "FunctionalTestFactory.h"

#include <boost/program_options/options_description.hpp>

// performing automatic registration
namespace {
    static AppOptionsDescription application_options;
}

namespace bpo = boost::program_options;



/* ************************************************************************* */
// declaration of command line and config file options
/* ************************************************************************* */
AppOptionsDescription::AppOptionsDescription()
{
    // general options
    bpo::options_description general_options("General options");
    general_options.add_options()
            ("help,h",  "produce help message")
            ("batch",   "run application in batch mode (no graphics)")
            ("report",  "write functional tests report in pdf file")
            ("all",     "run all registered functional test")
            ("profile", "profile specified test")
            ("config,c", bpo::value<std::string>()->default_value("gisasfw.cfg"),"config file name")
    ;

    // functional tests options constructed from information carried by FunctionalTestFactory
    bpo::options_description functional_test_options("Functional tests");
    FunctionalTestFactory::iterator it = FunctionalTestFactory::instance().begin();
    for(; it!= FunctionalTestFactory::instance().end(); ++it) {
        // it.first - test name, it.second - test description
        functional_test_options.add_options()((*it).first.c_str(), (*it).second.c_str());
    }

    // adding options to the main option holder
    ProgramOptions::instance().add(general_options).add(functional_test_options);
}




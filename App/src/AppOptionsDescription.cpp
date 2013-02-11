#include "AppOptionsDescription.h"
#include "ProgramOptions.h"
#include "FunctionalTestFactory.h"

#include <boost/program_options/options_description.hpp>

namespace bpo = boost::program_options;

/* ************************************************************************* */
// add command line and config file options
/* ************************************************************************* */
void AddApplicationOptions(ProgramOptions* p_options)
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
            ("fitconfig", bpo::value<int>()->default_value(1), "used in TestMesocrystal2")
            ("fitpreserve", bpo::value<int>()->default_value(1), "used in TestMesocrystal2")
    ;

    // there is no positional options (without '--' or '-' signs) at the moment

    // functional tests options constructed from information carried by FunctionalTestFactory
    bpo::options_description functional_test_options("Functional tests");
    FunctionalTestFactory::iterator it = FunctionalTestFactory::instance().begin();
    for(; it!= FunctionalTestFactory::instance().end(); ++it) {
        // it.first - test name, it.second - test description
        functional_test_options.add_options()((*it).first.c_str(), (*it).second.c_str());
    }

    // adding options to the main option holder
    p_options->add(general_options).add(functional_test_options);
}


// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/AppOptionsDescription.cpp
//! @brief     Implements global function AppOptionsDescription.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AppOptionsDescription.h"
#include "ProgramOptions.h"
#include "ApplicationTestFactory.h"

#include <boost/program_options/options_description.hpp>

namespace bpo = boost::program_options;

//! Adds command line and config file options.

void AddApplicationOptions(ProgramOptions* p_options, ApplicationTestFactory *p_test_factory)
{
    // general options
    bpo::options_description general_options("General options");
    general_options.add_options()
        ("help,h",  "produce help message")
        ("batch",   "run application in batch mode (no graphics)")
        ("report",  "write functional tests report in pdf file")
        ("all",     "run all registered functional test")
        ("profile", "profile specified test")
        ("config,c", bpo::value<std::string>()->default_value("bornagain.cfg"),
         "config file name")
        ("fitconfig", bpo::value<int>()->default_value(1),
         "used in TestMesocrystal2")
        ("fitpreserve", bpo::value<int>()->default_value(1),
         "used in TestMesocrystal2")
//            ("functest,f", bpo::value< std::vector<std::string> > ()->default_value(std::vector<std::string>(), ""), "List of functional tests to show.")
            ("functest,f", bpo::value< std::vector<std::string> > ()->multitoken()->zero_tokens(), "List of functional tests to show.")
// see http://stackoverflow.com/questions/1804514/how-to-accept-empty-value-in-boostprogram-options
    ;

    // there is no positional options (without '--' or '-' signs) at the moment

    // functional tests options constructed from information carried by FunctionalTestFactory
    bpo::options_description functional_test_options("Functional tests");
    ApplicationTestFactory::iterator it = p_test_factory->begin();
    for(; it!= p_test_factory->end(); ++it) {
        // it.first - test name, it.second - test description
        if( (*it).first != "functest") {
            functional_test_options.add_options()((*it).first.c_str(), (*it).second.c_str());
        }
    }

    //p_options->addPositional("functest",-1);

    // adding options to the main option holder
    p_options->add(general_options).add(functional_test_options);
}




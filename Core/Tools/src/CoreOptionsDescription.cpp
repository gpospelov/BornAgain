// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/CoreOptionsDescription.cpp
//! @brief     Implements function AddCoreOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreOptionsDescription.h"
#include "ProgramOptions.h"

namespace bpo = boost::program_options;

//! Adds command line and config file options

void AddCoreOptions(ProgramOptions *p_options)
{
    // general options
    bpo::options_description core_options("Core options");
    core_options.add_options()
            ("threads", bpo::value<int>(),
             "number of threads\n"
             "arg<0 - no threads, arg=0 - system optimal, otherwise"
             " specified number of threads.")
            ("nbatches", bpo::value<int>(),
             "number of batches\n")
            ("currentbatch", bpo::value<int>(),
             "current batch number (must be smaller than \"nbatches\")")
            ("msglog", bpo::value<std::string>()->default_value("ERROR"),
             "Logging at one of the levels "
             "VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL"
            );
    // adding options into main options holder
    p_options->add(core_options);
}



// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/CoreOptionsDescription.cpp
//! @brief     Implements function AddCoreOptions.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "CoreOptionsDescription.h"
#include "ProgramOptions.h"

#include <boost/program_options/options_description.hpp>

namespace bpo = boost::program_options;

//! add command line and config file options

void AddCoreOptions(ProgramOptions *p_options)
{
    // general options
    bpo::options_description core_options("Core options");
    core_options.add_options()
            ("threads", bpo::value<int>()->default_value(-1), "number of threads\n"
             "arg<0 - no threads, arg=0 - system optimal, otherwise specified number of threads."
             );
    // adding options into main options holder
    p_options->add(core_options);
}

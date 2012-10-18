#include "CoreOptionsDescription.h"
#include "ProgramOptions.h"

#include <boost/program_options/options_description.hpp>

namespace bpo = boost::program_options;

/* ************************************************************************* */
// add command line and config file options
/* ************************************************************************* */
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



// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      appoptions.h
//! @brief     Collection of utilities to parse command line options
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef APPOPTIONS_H
#define APPOPTIONS_H

#include "Macros.h"
#include "WinDllMacros.h"
GCC_DIAG_OFF(unused-parameter);
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
GCC_DIAG_ON(unused-parameter);

#include <string>

namespace bpo = boost::program_options;


//! @class ApplicationOptions
//! @ingroup tools_internal
//! @brief Handles command line and config file program options

class ApplicationOptions
{
public:
    ApplicationOptions(int argc = 0, char **argv = 0);

    //! access to variable with given name defined in variables container
    const bpo::variable_value& operator[] (const std::string& s) const;

    //! Returns true if option with given name has been set
    bool find(std::string name) const { return (m_variables_map.count(name.c_str()) ? true : false); }

    //! Returns true if options are consistent (no conflicting options, no --help request, config file is parsed)
    bool isConsistent() const { return m_options_is_consistent; }

    //! Parses command line arguments
    void parseCommandLine(int argc, char **argv);

    //! Returns reference to the variables container
    bpo::variables_map& getVariables() { return m_variables_map; }

    //! Returns reference to the options description
    bpo::options_description& getOptions() { return m_options; }

    void processOptions();

    void printHelpMessage() const;

private:
    bool m_options_is_consistent;       //! true if options are consistent (no conflicts, no --help request)
    bpo::options_description m_options; //! options description, to be filled with add() from different program modules
    bpo::positional_options_description m_positional_options; //! positional options description, to be filled with addPositional() from main module
    bpo::variables_map m_variables_map; //! parsed variables
};



#endif

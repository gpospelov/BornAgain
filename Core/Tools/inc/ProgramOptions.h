// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/ProgramOptions.h
//! @brief     Defines class ProgramOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include "WinDllMacros.h"
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
GCC_DIAG_ON(unused-parameter);

#include <string>

namespace bpo = boost::program_options;


//! @class ProgramOptions
//! @ingroup tools_internal
//! @brief Handles command line and config file program options
//!
//! The definition of program options are done separately from
//! CoreOptionsDescription, AppOptionsDescription modules and then
//! added to given class using add() method

class BA_CORE_API_ ProgramOptions
{
public:
    typedef bpo::options_description Variables_t;

    ProgramOptions();

    //! Adds options to the global options list (object is passed by value, so no dependency from object life)
    ProgramOptions & add(bpo::options_description opt) { m_options.add(opt); return *this;}

    //! Adds positional options
    ProgramOptions & addPositional(std::string option_name, int num_occurencies) { m_positional_options.add(option_name.c_str(), num_occurencies); return *this;}

    //! access to variable with given name defined in variables container
    const bpo::variable_value& operator[] (const std::string& s) const;

    //! Returns true if option with given name has been set
    bool find(std::string name) const { return (m_variables_map.count(name.c_str()) ? true : false); }

    //! Returns true if options are consistent (no conflicting options, no --help request, config file is parsed)
    bool isConsistent() const { return m_options_is_consistent; }

    //! Parses command line arguments
    void parseCommandLine(int argc, char **argv);

    //! Parses config file for arguments
    void parseConfigFile();

    //! Returns reference to the variables container
    bpo::variables_map& getVariables() { return m_variables_map; }

    //! Returns reference to the options description
    bpo::options_description& getOptions() { return m_options; }

    //! Returns reference to the positional options description
    bpo::positional_options_description& getPositionalOptions() { return m_positional_options; }

private:
    bool m_options_is_consistent;       //! true if options are consistent (no conflicts, no --help request)
    bpo::options_description m_options; //! options description, to be filled with add() from different program modules
    bpo::positional_options_description m_positional_options; //! positional options description, to be filled with addPositional() from main module
    bpo::variables_map m_variables_map; //! parsed variables
};

#endif // PROGRAMOPTIONS_H



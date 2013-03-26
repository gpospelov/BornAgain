// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/ProgramOptions.h
//! @brief     Defines class ProgramOptions.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
GCC_DIAG_ON(unused-parameter);
#include <boost/program_options/variables_map.hpp>

#include <string>

namespace bpo = boost::program_options;

//! @brief Handles command line and config file program options

//! The definition of program options are done separately from
//! CoreOptionsDescription, AppOptionsDescription modules and then
//! added to given class using add() method

class ProgramOptions
{
 public:
    typedef bpo::options_description Variables_t;

    ProgramOptions();

    //! adding options to the global options list (object is passed by value, so no dependency from object life)
    ProgramOptions  &add(bpo::options_description opt) { m_options.add(opt); return *this;}

    //! adding positional options
    ProgramOptions  &addPositional(std::string option_name, int num_occurencies) { m_positional_options.add(option_name.c_str(), num_occurencies); return *this;}

    //! access to variable with given name defined in variables container
    const bpo::variable_value& operator[] (const std::string &s) const;

    //! return true if option with given name has been set
    bool find(std::string name) const { return (m_variables_map.count(name.c_str()) ? true : false); }

    //! return true if options are consistent (no conflicting options, no --help request, config file is parsed)
    bool isConsistent() const { return m_options_is_consistent; }

    //! parsing command line arguments
    void parseCommandLine(int argc, char **argv);

    //! parse config file for arguments
    void parseConfigFile();

    // return reference to the variables container
    bpo::variables_map &getVariables() { return m_variables_map; }

    // return reference to the options description
    bpo::options_description &getOptions() { return m_options; }

    // return reference to the positional options description
    bpo::positional_options_description &getPositionalOptions() { return m_positional_options; }

 private:
    bool m_options_is_consistent;       //! true if options are consistent (no conflicts, no --help request)
    bpo::options_description m_options; //! options description, to be filled with add() from different program modules
    bpo::positional_options_description m_positional_options; //! positional options description, to be filled with addPositional() from main module
    bpo::variables_map m_variables_map; //! parsed variables
};

#endif // PROGRAMOPTIONS_H

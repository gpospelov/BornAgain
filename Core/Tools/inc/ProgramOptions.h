#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ProgramOptions.h
//! @brief  Definition of ProgramOptions class
//! @author Scientific Computing Group at FRM II
//! @date   21.09.2012


#include "ISingleton.h"

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
#include <boost/program_options/options_description.hpp>
GCC_DIAG_ON(unused-parameter);
#include <boost/program_options/variables_map.hpp>

#include <string>

namespace bpo = boost::program_options;


//- -------------------------------------------------------------------
//! @class ProgramOptions
//! @brief Handles command line and config file program options
//
//! The definition of program options are done separately from
//! CoreOptionsDescription, AppOptionsDescription modules and then
//! added to given class using add() method
//- -------------------------------------------------------------------
class ProgramOptions : public ISingleton<ProgramOptions>
{
public:
    typedef bpo::options_description Variables_t;

    ProgramOptions();

    //! adding options to the global options list (object is passed by value, so no dependency from object life)
    ProgramOptions  &add(bpo::options_description opt) { m_options.add(opt); return *this;}

    //! access to variable with given name defined in variables container
    const bpo::variable_value& operator[] (const std::string &s);

    //! return variables container
    bpo::variables_map &getVariables() { return m_variables_map; }

    //! return true if option with given name has been set
    bool find(std::string name){ return (m_variables_map.count(name.c_str()) ? true : false); }

    //! return true if options are consistent (no conflicting options, no --help request, config file is parsed)
    bool isConsistent() { return m_options_is_consistent; }

    //! parsing command line arguments
    void parseCommandLine(int argc, char **argv);

    //! parse config file for arguments
    void parseConfigFile();

private:
    bool m_options_is_consistent;       //! true if options are consistent (no conflicts, no --help request)
    bpo::options_description m_options; //! options desciption, to be filled with add() from different program modules
    bpo::variables_map m_variables_map; //! parsed variables
};

#endif // PROGRAMOPTIONS_H

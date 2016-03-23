// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      appoptions.cpp
//! @brief     Implements class ProgramOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "appoptions.h"
#include "GUIHelpers.h"
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>


ApplicationOptions::ApplicationOptions(int argc, char **argv)
    : m_options_is_consistent(false)
{
    m_options.add_options()
        ("help,h",      "print help message")
        ("version,v",   "print version number")
        ("with-debug",  "run application with debug printout")
        ("no-splash",   "do not show splash screen");

    parseCommandLine(argc, argv);

    processOptions();
}

//! access variables

const bpo::variable_value& ApplicationOptions::operator[] (const std::string& s) const
{
    return m_variables_map[s.c_str()];
}

//! parse command line arguments

void ApplicationOptions::parseCommandLine(int argc, char **argv)
{
    m_options_is_consistent = false;
    // parsing command line arguments
    try {
        // if positional option description is empty, no command line arguments
        // without '--' or '-' will be accepted
        // 'store' populates the variable map
        bpo::store( bpo::command_line_parser( argc, argv).options( m_options ).positional( m_positional_options ).run(), m_variables_map);
        //bpo::store(bpo::parse_command_line(argc, argv, m_options), m_variables_map);

        // 'notify' raises any errors encountered
        bpo::notify(m_variables_map);

        m_options_is_consistent = true;
    }
    catch(std::exception& e) {
        // we get here if there is unrecognized options
        std::cout << "main() ->  " << e.what() << std::endl;
        std::cout << m_options << std::endl;
    }

}

void ApplicationOptions::processOptions()
{
    if(!m_options_is_consistent) return;

    if (m_variables_map.count("help")) {
        printHelpMessage();
        m_options_is_consistent = false;
    }
    else if(m_variables_map.count("version")) {
        std::cout << "BornAgain-"<<GUIHelpers::getBornAgainVersionString().toStdString() << std::endl;
        m_options_is_consistent = false;
    }

}

void ApplicationOptions::printHelpMessage() const
{
    std::cout << "BornAgain Graphical User Interface" << std::endl;
    std::cout << m_options << std::endl;
}



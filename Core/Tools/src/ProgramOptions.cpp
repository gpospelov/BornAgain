// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/ProgramOptions.cpp
//! @brief     Implements class ProgramOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProgramOptions.h"
#include "Utils.h"
#include "FileSystem.h"
#include "MessageService.h"
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>

ProgramOptions::ProgramOptions() : m_options_is_consistent(false)
{
}

//! access variables

const bpo::variable_value& ProgramOptions::operator[] (const std::string& s) const
{
    if( !m_options_is_consistent ) {
        // no consistent options, the reason might be that no call to
        // parseConfigFile has been made (for example due to the absence of
        // main())
    }
    return m_variables_map[s.c_str()];
}

//! parse command line arguments

void ProgramOptions::parseCommandLine(int argc, char **argv)
{
    // saving relative path to the application for later usage
    Utils::FileSystem::SetArgvPath(argv[0]);

    // parsing command line arguments
    try {
        // if positional option description is empty, no command line arguments
        // without '--' or '-' will be accepted
        // 'store' populates the variable map
        bpo::store( bpo::command_line_parser( argc, argv).options( m_options ).positional( m_positional_options ).run(), m_variables_map);
        //bpo::store(bpo::parse_command_line(argc, argv, m_options), m_variables_map);

        // 'notify' raises any errors encountered
        bpo::notify(m_variables_map);

        if (m_variables_map.count("help") || argc == 1) {
            std::cout << m_options << std::endl;
            // if user asked for help there is no sence to continue
            return;
        }
    }
    catch(std::exception& e) {
        // we get here if there is unrecognized options
        msglog(MSG::ERROR) << "ProgramOptions::parseCommandLine() -> Error. Unrecognized options in command line.";
        std::cerr << "error: " << e.what() << "\n";
        throw; // throwing it further to terminate program
    }

    // and now call parsing of config file
//    parseConfigFile();
    m_options_is_consistent = true;
}

//! parse config file for arguments

void ProgramOptions::parseConfigFile()
{
    //std::cout << "ProgramOptions::parseConfigFile" << std::endl;
    // default config file name
    std::string config_file("bornagain.cfg");

    // definition of config file name in command line options overrides default name
    if (m_variables_map.count("config") ) {
        config_file = m_variables_map["config"].as<std::string >();
        msglog(MSG::INFO) << "ProgramOptions::parseConfigFile() -> Name of config file '" << config_file << "'";
    }

    std::string config_full_name = Utils::FileSystem::GetHomePath()+config_file;
    std::ifstream ifs(config_full_name.c_str());
    if (!ifs) {
        msglog(MSG::WARNING) << "ProgramOptions::parseConfigFile() -> Can not open config file: " << config_file;
    } else {

        // parsing config file
        try {
            // 'store' populates the variable map
            bpo::store(bpo::parse_config_file(ifs, m_options), m_variables_map);
            // 'notify' raises any erros encountered
            bpo::notify(m_variables_map);
        }
        catch(std::exception& e) {
            // we get here if there is unrecognized options
            msglog(MSG::ERROR) << "ProgramOptions::parseConfigFile() -> Unrecognized options in file '" << config_file << "'";
            std::cerr << "error: " << e.what() << "\n";
            throw; // throwing it further to terminate program
        }
    }

    m_options_is_consistent = true;
}



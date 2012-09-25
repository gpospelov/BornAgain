#include "ProgramOptions.h"
#include <boost/program_options/config.hpp>
#include <boost/program_options/parsers.hpp>
#include <iostream>
#include <fstream>

ProgramOptions::ProgramOptions() : m_options_is_consistent(false)
{

}


/* ************************************************************************* */
// access to variables
/* ************************************************************************* */
const bpo::variable_value& ProgramOptions::operator[] (const std::string &s)
{
    if( !m_options_is_consistent ) {
        // no consistent options, there reason might be that no call to parseConfigFile
        // has been made (for example due to the absence of main())
        parseConfigFile();
    }
    return m_variables_map[s.c_str()];
}


/* ************************************************************************* */
// parse command line arguments
/* ************************************************************************* */
void ProgramOptions::parseCommandLine(int argc, char **argv)
{
    try {
        // if positional option description is empty, no command line arguments without '--' or '-' will be accepted
        // 'store' populates the variable map
        bpo::store( bpo::command_line_parser( argc, argv).options( m_options ).positional( m_positional_options ).run(), m_variables_map);
        //bpo::store(bpo::parse_command_line(argc, argv, m_options), m_variables_map);

        // 'notify' raises any erros encountered
        bpo::notify(m_variables_map);

        if (m_variables_map.count("help") || argc == 1) {
            std::cout << m_options << std::endl;
            // if user asked for help there is no sence to continue
            return;
        }
    }
    catch(std::exception& e) {
        // we get here if there is unrecognized options
        std::cout << "ProgramOptions::parseCommanLine() -> Error. Unrecognized options in command line." << std::endl;
        std::cerr << "error: " << e.what() << "\n";
        throw e; // throwing it further to terminate program
    }

    // and now call parsing of config file
    parseConfigFile();
}


/* ************************************************************************* */
// parse config file for arguments
/* ************************************************************************* */
void ProgramOptions::parseConfigFile()
{
    std::cout << "ProgramOptions::parseConfigFile" << std::endl;

    // default config file name
    std::string config_file("gisasfw.cfg");

    // definitions of config file name in command line options overrides default name
    if (m_variables_map.count("config") ) {
        config_file = m_variables_map["config"].as<std::string >();
        std::cout << "Name of config file defined in command line '" << config_file << "'" << std::endl;
    }

    std::ifstream ifs(config_file.c_str());
    if (!ifs) {
        std::cout << "ProgramOptions::parseConfigFile() -> Warning! Can not open config file: " << config_file << std::endl;
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
            std::cout << "ProgramOptions::parseConfigFile() -> Error. Unrecognized options in file '" << config_file << "'" << std::endl;
            std::cerr << "error: " << e.what() << "\n";
            throw e; // throwing it further to terminate program
        }
    }

    m_options_is_consistent = true;
}

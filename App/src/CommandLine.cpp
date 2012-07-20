#include "CommandLine.h"
#include "TestFactory.h"
#include <iomanip>
#include <set>
#include <algorithm>


/* ************************************************************************* */
// command line constructor parses command line arguments, create list of
// known arguments and they description
/* ************************************************************************* */
CommandLine::CommandLine(int argc, char **argv) : m_argc(argc), m_argv(argv)
{
    // saving command line argument for later convenient access
    for(int i=1; i<argc; i++) m_arguments.push_back(std::string(argv[i]));

    // saving relative path to the application for later usage
    Utils::FileSystem::SetRelativePath(argv[0]);

    // creating list of defined arguments
    m_defined_arguments.push_back("help");
    m_defined_arguments.push_back("batch");
    m_defined_arguments.push_back("pdfreport");
    m_defined_arguments.push_back("all");
    m_defined_arguments.push_back("profile");
    // getting info about names of defined functional tests and adding them to the list of defined arguments
    m_defined_functional_tests = TestFactory::instance().get_testnames();
    m_defined_arguments.insert(m_defined_arguments.end(), m_defined_functional_tests.begin(), m_defined_functional_tests.end());

    // adding description of command line arguments

    // description of general command line arguments
    m_description["help"]         = "print given help";
    m_description["batch"]        = "run application in batch mode (no graphics)";
    m_description["pdfreport"]    = "generate pdf report for functional tests";
    m_description["all"]          = "run all registered functional test";
    m_description["profile"]      = "profile specified test";
    // default description of functional tests
    for(arguments_t::iterator it = m_defined_functional_tests.begin(); it!=m_defined_functional_tests.end(); ++it ) {
        m_description[ (*it) ]    = "functional test: no description";
    }
    // additional description of functional tests (overwrites previous default)
    m_description["isgisaxs1"]    = "functional test: isgisaxs ex-1 (2 types of particles without inteference on top of substrate)";
    m_description["isgisaxs3"]    = "functional test: isgisaxs ex-3 (cylinder FF)";
    m_description["isgisaxs9"]    = "functional test: isgisaxs ex-9 (pyramid FF)";
    m_description["isgisaxs10"]   = "functional test: isgisaxs ex-10 (cylinders with interference on top of substrate)";
    m_description["convolution"]  = "functional test: test of convolution via fft";
    m_description["diffuse"]      = "functional test: diffuse scattering from multi layer with roughness";
    m_description["formfactor"]   = "functional test: some formfactor";
    m_description["roughness"]    = "functional test: roughness parameters";
    m_description["roottree"]     = "functional test: using root trees to read/write data from/to disk";

}


/* ************************************************************************* */
// return true if all command line arguments are recognized
/* ************************************************************************* */
bool CommandLine::isGood()
{
    // no arguments in command line is not good
    if(!m_arguments.size() ) return false;

    // pleading for 'help' in command line is also not good
    if( find("help") ) return false;

    // check if all arguments from command line are known
    std::set<std::string> s_defined( m_defined_arguments.begin(), m_defined_arguments.end() );
    std::set<std::string> s_requested( m_arguments.begin(), m_arguments.end() );
    arguments_t unknown_arguments;
    std::set_difference(s_requested.begin(), s_requested.end(), s_defined.begin(), s_defined.end(), std::back_inserter(unknown_arguments) );
    if( unknown_arguments.size() ) {
        std::cout << "Unkown arguments: ";
        for(size_t i=0; i<unknown_arguments.size(); i++){
            std::cout << "'" << unknown_arguments[i] << "' ";
        }
        std::cout << std::endl;
        return false;
    }

    return true;
}


/* ************************************************************************* */
// return true if there is functional test with such name
/* ************************************************************************* */
bool CommandLine::isFunctionalTest(std::string name)
{
    for(arguments_t::iterator it=m_defined_functional_tests.begin(); it!= m_defined_functional_tests.end(); ++it) {
        if(name == (*it)) return true;
    }
    return false;
}


/* ************************************************************************* */
// print help on the screen
/* ************************************************************************* */
void CommandLine::print_help()
{
    std::cout << " " << std::endl;
    std::cout << "CommandLine::print_help() -> Run application with one ore more arguments from the list below" << std::endl;
    std::cout << " " << std::endl;
    for(arguments_t::iterator it=m_defined_arguments.begin(); it!= m_defined_arguments.end(); ++it) {
        std::cout << std::setw(15) << std::left << (*it) << " - " << m_description[(*it)] << std::endl;
    }
    std::cout << " " << std::endl;
    std::cout << "Example: ./App isgisaxs10 " << std::endl;
    std::cout << "Example: ./App isgisaxs3 isgisaxs10 pdfreport batch " << std::endl;

}

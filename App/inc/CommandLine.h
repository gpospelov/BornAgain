#ifndef COMMANDLINE_H
#define COMMANDLINE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   CommandLine.h
//! @brief  Definition of CommandLine class
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <string>
#include <vector>
#include <map>

#include <algorithm>
#include "Utils.h"

//- -------------------------------------------------------------------
//! @class CommandLine
//! @brief Simple handling of command line parameters
//- -------------------------------------------------------------------
class CommandLine
{
public:
    typedef std::vector<std::string > arguments_t;

    //! command line constructor parses command line arguments
    CommandLine(int argc, char **argv);

    //! return command line argument
    std::string &operator[](int i) {return m_arguments.at(i); }

    //! check if such name present in command line arguments
    bool find(std::string name) {return std::find(m_arguments.begin(), m_arguments.end(), name)==m_arguments.end() ? false : true; }

    //! return original comand line argc
    int  getArgc() const  { return m_argc; }

    //! return original comand line argv
    char **getArgv() const  { return m_argv; }

    //! print help on the screen
    void print_help();

    //! return true if all command line arguments are recognized
    bool isGood();

    //! return true if there is functional test with such name
    bool isFunctionalTest(std::string name);

    //! return number of arguments in command line
    size_t size() { return m_arguments.size(); }

private:
    int m_argc; //! original command line argc
    char **m_argv; //! original command line argv
    arguments_t m_arguments; //! parsed command line arguments

    arguments_t m_defined_arguments; //! defined command line arguments
    arguments_t m_defined_functional_tests; //! defined names of functional tests
    std::map<std::string, std::string > m_description; //! description of command line arguments

};

#endif // COMMANDLINE_H

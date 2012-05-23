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
#include <algorithm>

//- -------------------------------------------------------------------
//! @class CommandLine
//! @brief Simple hadling of command line parameters
//- -------------------------------------------------------------------
class CommandLine
{
public:
    CommandLine(int argc, char **argv)
    {
        for(int i=1; i<argc; i++) m_pars.push_back(std::string(argv[i]));
    }

    //bool operator==(std::string name) { return std::find(m_pars.begin(), m_pars.end(), name)==m_pars.end() ? false : true; }
    //bool operator!=(std::string name) { return std::find(m_pars.begin(), m_pars.end(), name)==m_pars.end() ? true : false; }
    std::string &operator[](int i) {return m_pars.at(i); }

    size_t size() { return m_pars.size(); }

    bool find(std::string name) {return std::find(m_pars.begin(), m_pars.end(), name)==m_pars.end() ? false : true; }
private:
    std::vector<std::string > m_pars;

};

#endif // COMMANDLINE_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreIO/Benchmark.cpp
//! @brief     Implements Benchmark class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Benchmark.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

Benchmark::~Benchmark()
{
    for (auto it = m_data.begin(); it!= m_data.end(); ++it) {
        delete it->second;
    }
}

void Benchmark::start(const std::string& name)
{
    std::cout << "Benchmark::start() -> Starting '" << name << "'" << std::endl;
    if(m_data.find(name) == m_data.end())
        m_data.insert(std::make_pair(name, new Duration()));

    m_data[name]->start();
}

void Benchmark::stop(const std::string& name)
{
    if(m_data.find(name) == m_data.end())
        throw std::runtime_error("Benchmark::stop() -> No such process '"+name+"'");

    m_data[name]->stop();
}

double Benchmark::runTime(const std::string& name)
{
    if(m_data.find(name) == m_data.end())
        throw std::runtime_error("Benchmark::stop() -> No such process '"+name+"'");

    return m_data[name]->runTime();
}

std::string Benchmark::report() const
{
    std::ostringstream result;

    for (auto it = m_data.begin(); it!= m_data.end(); ++it) {
        std::string name(it->first);
        name.resize(20, ' ');
        result  <<  name << " : " << std::setprecision(6) << it->second->runTime() << "\n";
    }


    return result.str();
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/IParameterized.cpp
//! @brief     Implements classes IParameterized and ParameterPattern.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <sstream>
#include <memory>
#include "IParameterized.h"

// Copies INamed, but not the parameters.

IParameterized& IParameterized::operator=(const IParameterized& other)
{
    if( this != &other)
        INamed::operator=(other);
    return *this;
}

ParameterPool* IParameterized::createParameterTree()
{
    std::unique_ptr<ParameterPool> P_new_pool( new ParameterPool(this) );
    std::string path("/");
    addParametersToExternalPool(path, P_new_pool.get());
    return P_new_pool.release();
}

//! Copies local parameters to external_pool, under name "path/<name>copy_number/"

std::string IParameterized::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    if( path[path.length()-1] != '/' )
        path += "/";
    std::ostringstream osCopyNumber;
    if(copy_number >=0)
        osCopyNumber << copy_number;
    path += getName() + osCopyNumber.str() + "/";

    // copy local parameter to external pool
    m_parameters.copyToExternalPool(path, external_pool);

    return path;
}

void IParameterized::setParameterValue(const std::string &name, double value)
{
    if(name.find('*') == std::string::npos && name.find('/') == std::string::npos) {
        m_parameters.setParameterValue(name, value);
    } else {
        std::unique_ptr<ParameterPool> P_pool { createParameterTree() };
        if(name.find('*') != std::string::npos) {
            P_pool->setMatchedParametersValue(name, value);
        } else {
            P_pool->setParameterValue(name, value);
        }
    }
    onChange();
}

void IParameterized::printParameters()
{
    std::unique_ptr<ParameterPool> P_pool( createParameterTree() );
    std::cout << *P_pool << std::endl;
}

void IParameterized::print(std::ostream& ostr) const
{
    ostr << "IParameterized:" << getName() << " " << m_parameters;
}

ParameterPattern& ParameterPattern::beginsWith(std::string start_type)
{
    m_pattern = start_type;
    return *this;
}

ParameterPattern& ParameterPattern::add(std::string object_type)
{
    m_pattern = m_pattern + "/" + object_type;
    return *this;
}

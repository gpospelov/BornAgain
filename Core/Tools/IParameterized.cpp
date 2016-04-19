// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/IParameterized.cpp
//! @brief     Implements class IParameterized,
//!               mainly by including IParameterized.h.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParameterized.h"

#include "Utils.h"
#include <iostream>
#include <memory>

IParameterized& IParameterized::operator=(const IParameterized& other)
{
    if( this !=& other)
    {
        INamed::operator=(other);
        // parameters are not copied
    }
    return *this;
}

ParameterPool *IParameterized::createParameterTree() const
{
    std::unique_ptr<ParameterPool> P_new_pool { new ParameterPool };
    std::string path("/");
    addParametersToExternalPool(path, P_new_pool.get());
    return P_new_pool.release();
}

std::string IParameterized::addParametersToExternalPool(
    std::string path, ParameterPool *external_pool, int copy_number) const
{
    // adding trailing slash, if it is not already there
    if( path[path.length()-1] != '/' ) path += "/";

    // constructing new path, using object name and copy number
    std::ostringstream osCopyNumber;
    if(copy_number >=0) osCopyNumber << copy_number;
    path =  path + getName() + osCopyNumber.str() + "/";

    // copy local parameter to external pool
    m_parameters.copyToExternalPool(path, external_pool);

    return path;
}

bool IParameterized::setParameterValue(const std::string &name, double value)
{
    if(name.find('*') == std::string::npos && name.find('/') == std::string::npos) {
        return m_parameters.setParameterValue(name, value);
    }
    std::unique_ptr<ParameterPool> P_pool { createParameterTree() };
    if(name.find('*') != std::string::npos) {
        return P_pool->setMatchedParametersValue(name, value);
    } else {
        return P_pool->setParameterValue(name, value);
    }
}

void IParameterized::printParameters() const
{
    std::unique_ptr<ParameterPool> P_pool { createParameterTree() };
    std::cout << *P_pool << std::endl;
}

void IParameterized::init_parameters()
{
    throw NotImplementedException("IParameterized::init_parameters() -> "
                                  "Error! Method is not implemented");
}

void IParameterized::print(std::ostream& ostr) const
{
    ostr << "IParameterized:" << getName() << " " << m_parameters;
}

ParameterPattern::ParameterPattern()
    : m_pattern { }
{
}

ParameterPattern::ParameterPattern(std::string root_object)
    : m_pattern ( "/" + root_object )
{
}

ParameterPattern &ParameterPattern::beginsWith(std::string start_type)
{
    m_pattern = start_type;
    return *this;
}

ParameterPattern &ParameterPattern::add(std::string object_type)
{
    m_pattern = m_pattern + "/" + object_type;
    return *this;
}

std::string ParameterPattern::toStdString() const
{
    return m_pattern;
}

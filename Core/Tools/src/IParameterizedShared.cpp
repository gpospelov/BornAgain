// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/IParameterizedShared.cpp
//! @brief     Implements class IParameterizedShared,
//!               mainly by including IParameterizedShared.h.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParameterized.h"
#include "IParameterizedShared.h"

#include "Utils.h"
#include <iostream>
#include <memory>

IParameterizedShared& IParameterizedShared::operator=(const IParameterizedShared& other)
{
    if( this !=& other)
    {
        INamedShared::operator=(other);
        // parameters are not copied
    }
    return *this;
}

ParameterPool *IParameterizedShared::createParameterTree() const
{
    std::unique_ptr<ParameterPool> P_new_pool { new ParameterPool };
    std::string path("/");
    addParametersToExternalPool(path, P_new_pool.get());
    return P_new_pool.release();
}

std::string IParameterizedShared::addParametersToExternalPool(
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

bool IParameterizedShared::setParameterValue(const std::string &name, double value)
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

void IParameterizedShared::printParameters() const
{
    std::unique_ptr<ParameterPool> P_pool { createParameterTree() };
    std::cout << *P_pool << std::endl;
}

void IParameterizedShared::init_parameters()
{
    throw NotImplementedException("IParameterizedShared::init_parameters() -> "
                                  "Error! Method is not implemented");
}

void IParameterizedShared::print(std::ostream& ostr) const
{
    ostr << "IParameterizedShared:" << getName() << " " << m_parameters;
}


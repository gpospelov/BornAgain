// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/IParameterized.cpp
//! @brief     Implements class IParameterized,
//!               mainly by including IParameterized.h.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParameterized.h"

#include <boost/scoped_ptr.hpp>

#include "Utils.h"
#include <iostream>

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
    ParameterPool *newpool = new ParameterPool;
    std::string path("/");
    addParametersToExternalPool(path, newpool);
    return newpool;
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
    boost::scoped_ptr<ParameterPool> pool(createParameterTree());
    if(name.find('*') != std::string::npos) {
        return pool->setMatchedParametersValue(name, value);
    } else {
        return pool->setParameterValue(name, value);
    }
}


void IParameterized::printParameters() const
{
    ParameterPool *p_pool = createParameterTree();
    std::cout << *p_pool << std::endl;
    delete p_pool;
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




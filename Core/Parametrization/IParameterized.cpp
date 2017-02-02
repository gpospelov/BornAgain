// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameterized.cpp
//! @brief     Implements class IParameterized.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IParameterized.h"
#include "RealLimits.h"
#include "ParameterPool.h"
#include "RealParameter.h"
#include "Exceptions.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

IParameterized::IParameterized(const std::string& name)
    : INamed(name)
{
    m_pool = new ParameterPool;
}

IParameterized::IParameterized(const IParameterized& other)
    : IParameterized(other.getName())
{
    if( other.getParameterPool()->size() )
        throw std::runtime_error( "BUG: not prepared to copy parameters of " + getName() );
}

IParameterized::~IParameterized()
{
    delete m_pool;
}

ParameterPool* IParameterized::createParameterTree() const
{
    std::unique_ptr<ParameterPool> result(new ParameterPool);
    m_pool->copyToExternalPool("/"+getName()+"/", result.get());
    return result.release();
}

std::string IParameterized::parametersToString() const
{
    std::ostringstream result;
    std::unique_ptr<ParameterPool> P_pool( createParameterTree() );
    result << *P_pool << "\n";
    return result.str();
}

RealParameter& IParameterized::registerParameter(const std::string& name, double* data)
{
    return m_pool->addParameter(
        new RealParameter( name, data, getName(), [&]()->void{ onChange(); } ));
}

void IParameterized::setParameterValue(const std::string& name, double value)
{
    if(name.find('*') == std::string::npos && name.find('/') == std::string::npos) {
        m_pool->setParameterValue(name, value);
    } else {
        std::unique_ptr<ParameterPool> P_pool { createParameterTree() };
        if(name.find('*') != std::string::npos)
            P_pool->setMatchedParametersValue(name, value);
        else
            P_pool->setParameterValue(name, value);
    }
    onChange();
}

//! Returns parameter with given 'name'.
RealParameter* IParameterized::getParameter(const std::string& name) const {
    return m_pool->getParameter(name);
}

void IParameterized::removeParameter(const std::string& name)
{
    m_pool->removeParameter(name);
}

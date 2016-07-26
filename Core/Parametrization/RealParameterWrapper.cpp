// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/RealParameterWrapper.cpp
//! @brief     Implements class RealParameterWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RealParameterWrapper.h"
#include "Exceptions.h"
#include "IParameterized.h"
#include <sstream>

RealParameterWrapper::RealParameterWrapper(
    const std::string& name, IParameterized* parent, volatile double* par, const AttLimits& limits)
    : INamed(name)
    , m_parent(parent)
    , m_data(par)
    , m_limits(limits)
{
    if(par && !m_limits.isInRange(getValue())) {
        std::ostringstream message;
        message << "Parameter " << fullName() << " has invalid initial value " << getValue()
                << ": out of bounds [" << limits << "]\n";
        throw Exceptions::OutOfBoundsException(message.str());
    }
}

RealParameterWrapper::RealParameterWrapper(const RealParameterWrapper& other )
    : RealParameterWrapper( other.getName(), other.m_parent, other.m_data, other.m_limits ) {}

//! This constructor takes copies 'other' except for the name.
RealParameterWrapper::RealParameterWrapper(
    const std::string& name, const RealParameterWrapper& other)
    : RealParameterWrapper( name, other.m_parent, other.m_data, other.m_limits ) {}

//! throw exception if parameter was not initialized with proper value
void RealParameterWrapper::checkNull() const
{
    if(isNull())
        throw Exceptions::NullPointerException(
            "BUG in RealParameterWrapper::getValue() -> Attempt to access uninitialised pointer.");
}

void RealParameterWrapper::setValue(double value)
{
    checkNull();
    if(value == *m_data)
        return; // nothing to do
    if(!m_limits.isInRange(value)) {
        std::ostringstream message;
        message << "Parameter " << fullName() << " has invalid value " << getValue()
                << ": out of bounds [" << m_limits << "]\n";
        throw Exceptions::OutOfBoundsException(message.str());
    }
    if(m_limits.isFixed())
        throw Exceptions::OutOfBoundsException("Parameter "+fullName()+" is fixed");
    *m_data = value;
    m_parent->onChange();
}

void RealParameterWrapper::swapContent(RealParameterWrapper& other)
{
    std::swap(this->m_parent, other.m_parent);
    std::swap(this->m_name, other.m_name);
    std::swap(this->m_data, other.m_data);
    std::swap(this->m_limits, other.m_limits);
}

std::string RealParameterWrapper::fullName()
{
    return m_parent->getName() + "/" + getName();
}

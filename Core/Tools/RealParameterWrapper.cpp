// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/RealParameterWrapper.cpp
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
#include <sstream>

RealParameterWrapper::RealParameterWrapper(double *par, const AttLimits &limits)
    : m_data(par)
    , m_limits(limits)
{
    if(par && !m_limits.isInRange(getValue())) {
        std::ostringstream message;
        message << "RealParameterWrapper::RealParameterWrapper() -> Error. "
                << "Initial value " << getValue() << " is out of bounds "
                << limits << std::endl;
        throw OutOfBoundsException(message.str());
    }
}

RealParameterWrapper::RealParameterWrapper(const RealParameterWrapper& other )
{
    m_data = other.m_data;
    m_limits = other.m_limits;
}

RealParameterWrapper& RealParameterWrapper::operator=(const RealParameterWrapper& other)
{
    if( this !=& other )  {
        RealParameterWrapper tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

bool RealParameterWrapper::setValue(double value)
{
    bool success(true);
    checkNull();
    if(value != *m_data) {
        if(m_limits.isInRange(value) && !m_limits.isFixed()) {
            *m_data = value;
        } else {
            success = false;
        }
    }
    return success;
}

void RealParameterWrapper::swapContent(RealParameterWrapper& other)
{
    std::swap(this->m_data, other.m_data);
    std::swap(this->m_limits, other.m_limits);
}

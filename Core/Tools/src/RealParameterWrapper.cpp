// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/RealParameterWrapper.cpp
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

RealParameterWrapper::RealParameterWrapper(double *par, const AttLimits &limits)
    : m_data(par)
    , m_limits(limits)
{

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
        *m_data = value;
    }
    return success;
}

void RealParameterWrapper::swapContent(RealParameterWrapper& other)
{
    std::swap(this->m_data, other.m_data);
    std::swap(this->m_limits, other.m_limits);
}



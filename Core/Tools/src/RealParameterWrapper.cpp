// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/RealParameterWrapper.cpp
//! @brief     Implements class RealParameterWrapper.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RealParameterWrapper.h"

RealParameterWrapper::RealParameterWrapper(const RealParameterWrapper& other )
{
    m_data = other.m_data;
}

RealParameterWrapper& RealParameterWrapper::operator=(const RealParameterWrapper& other)
{
    if( this !=& other )  {
        RealParameterWrapper tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void RealParameterWrapper::swapContent(RealParameterWrapper& other)
{
    std::swap(this->m_data, other.m_data);
}



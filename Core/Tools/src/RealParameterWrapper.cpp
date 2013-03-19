// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Tools/RealParameterWrapper.cpp 
//! @brief     Implements class RealParameterWrapper.
//
// ************************************************************************** //

#include "RealParameterWrapper.h"

RealParameterWrapper::RealParameterWrapper(const RealParameterWrapper &other )
{
    m_data = other.m_data;
}

RealParameterWrapper &RealParameterWrapper::operator=(const RealParameterWrapper &other)
{
    if( this != &other )  {
        RealParameterWrapper tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void RealParameterWrapper::swapContent(RealParameterWrapper &other)
{
    std::swap(this->m_data, other.m_data);
}

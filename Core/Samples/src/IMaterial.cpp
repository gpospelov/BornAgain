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
//! @file      Samples/IMaterial.cpp 
//! @brief     Implements class IMaterial.
//
// ************************************************************************** //

#include "IMaterial.h"

IMaterial::IMaterial(const IMaterial &other) : INamed(other)
{
}

IMaterial &IMaterial::operator=(const IMaterial &other)
{
    if( this != &other) {
        INamed::operator=(other);
        m_name = other.m_name;
    }
    return *this;
}

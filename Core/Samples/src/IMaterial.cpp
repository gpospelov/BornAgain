// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/IMaterial.cpp
//! @brief     Implements class IMaterial.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
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

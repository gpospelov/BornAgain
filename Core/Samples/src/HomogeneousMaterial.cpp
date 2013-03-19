// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/HomogeneousMaterial.cpp
//! @brief     Implements class HomogeneousMaterial.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "HomogeneousMaterial.h"

HomogeneousMaterial::HomogeneousMaterial()
{
}

HomogeneousMaterial::HomogeneousMaterial(const complex_t &refractive_index)
    : IMaterial("noname"), m_refractive_index(refractive_index)
{
}

HomogeneousMaterial::HomogeneousMaterial(const std::string &name, const complex_t &refractive_index)
    : IMaterial(name), m_refractive_index(refractive_index)
{
}

HomogeneousMaterial::HomogeneousMaterial(const std::string &name, double refractive_index_real, double refractive_index_imag)
    : IMaterial(name), m_refractive_index(refractive_index_real, refractive_index_imag)
{
}

HomogeneousMaterial::HomogeneousMaterial(const HomogeneousMaterial &other) : IMaterial(other)
{
    m_refractive_index = other.m_refractive_index;
}

HomogeneousMaterial &HomogeneousMaterial::operator=(const HomogeneousMaterial &other)
{
    if(this != &other)
    {
        IMaterial::operator=(other);
        m_refractive_index = other.m_refractive_index;
    }
    return *this;
}

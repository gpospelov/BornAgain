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
//! @file      Samples/HomogeneousMaterial.cpp 
//! @brief     Implements class HomogeneousMaterial.
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

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/IMaterial.cpp
//! @brief     Implements class IMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMaterial.h"
#include "Exceptions.h"
#include "HomogeneousMagneticMaterial.h"
#include "WavevectorInfo.h"

//! Returns true if *this agrees with other in all parameters.
complex_t IMaterial::getScalarSLD(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    double prefactor = M_PI/wavelength/wavelength;
    complex_t refractive_index = getRefractiveIndex();
    return prefactor * refractive_index * refractive_index;
}

Eigen::Matrix2cd IMaterial::getPolarizedSLD(const WavevectorInfo& wavevectors) const
{
    return getScalarSLD(wavevectors)*Eigen::Matrix2cd::Identity();
}

bool IMaterial::operator==(const IMaterial& other) const
{
    if( getName()!=other.getName() )
        return false;
    if( getRefractiveIndex().real() != other.getRefractiveIndex().real() )
        return false;
    if( getRefractiveIndex().imag() != other.getRefractiveIndex().imag() )
        return false;
    if( isScalarMaterial() != other.isScalarMaterial() )
        return false;
    auto p_this  = dynamic_cast<const HomogeneousMagneticMaterial*>(this);
    auto p_other = dynamic_cast<const HomogeneousMagneticMaterial*>(&other);
    if (p_this && p_other && p_this->getMagneticField() != p_other->getMagneticField() )
        return false;
    return true;
}

std::ostream& operator<<(std::ostream& ostr, const IMaterial& m)
{
    m.print(ostr);
    return ostr;
}

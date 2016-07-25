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
#include "HomogeneousMagneticMaterial.h"

IMaterial *IMaterial::clone() const
{
    throw Exceptions::NotImplementedException(
        "IMaterial is an interface and should not be cloned!");
}

const IMaterial *IMaterial::createTransformedMaterial(const IRotation&) const
{
    throw Exceptions::NotImplementedException(
        "IMaterial is an interface and should not be created!");
}

Eigen::Matrix2cd IMaterial::getScatteringMatrix(double k_mag2) const
{
    (void)k_mag2;
    return Eigen::Matrix2cd::Identity();
}

#ifndef SWIG
Eigen::Matrix2cd IMaterial::getSpecularScatteringMatrix(const kvector_t k) const
{
    Eigen::Matrix2cd result;
    double k_mag2 = k.mag2();
    double xy_proj2 = k.magxy2() / k_mag2;
    result = getScatteringMatrix(k_mag2) - xy_proj2 * Eigen::Matrix2cd::Identity();
    return result;
}
#endif // SWIG

//! Returns true if *left agrees with *right in all parameters.
bool pEqual(const IMaterial* left, const IMaterial* right)
{
    if( left->getName()!=right->getName() )
        return false;
    if( left->getRefractiveIndex().real() != right->getRefractiveIndex().real() )
        return false;
    if( left->getRefractiveIndex().imag() != right->getRefractiveIndex().imag() )
        return false;
    if( left->isScalarMaterial() != right->isScalarMaterial() )
        return false;
    auto p_left  = dynamic_cast<const HomogeneousMagneticMaterial*>(left);
    auto p_right = dynamic_cast<const HomogeneousMagneticMaterial*>(right);
    if (p_left && p_right) {
        if( p_left->getMagneticField() != p_right->getMagneticField() )
            return false;
    }
    return true;
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularScalarNCStrategy.h
//! @brief     Defines class SpecularScalarNCStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSCALARNCSTRATEGY_H
#define SPECULARSCALARNCSTRATEGY_H

#include "SpecularScalarStrategy.h"

class Slice;

//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//! @ingroup algorithms_internal

class BA_CORE_API_ SpecularScalarNCStrategy : public SpecularScalarStrategy
{
private:

    //! Roughness is modelled by a Gaussian profile, i.e. Nevot-Croce factors for the
    //! reflection coefficients.
    //! Implementation follows A. Gibaud and G. Vignaud, in X-ray and Neutron Reflectivity, edited by J. Daillant
    //! and A. Gibaud, volume 770 of Lecture Notes in Physics (2009)
    virtual Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma, double thickness,
                                        const Eigen::Vector2cd& t_r1) const override;


};

#endif // SPECULARSCALARNCSTRATEGY_H

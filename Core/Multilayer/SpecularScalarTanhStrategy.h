// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SpecularMatrix.h
//! @brief     Defines namespace SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSCALARTANHSTRATEGY_H
#define SPECULARSCALARTANHSTRATEGY_H

#include "SpecularScalarStrategy.h"

class Slice;

//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//! @ingroup algorithms_internal

class SpecularScalarTanhStrategy : public SpecularScalarStrategy
{
private:

    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    virtual Eigen::Vector2cd transition(complex_t kzi, complex_t kzi1, double sigma, double thickness,
                                        const Eigen::Vector2cd& t_r1) const override;


};

#endif // SPECULARSCALARTANHSTRATEGY_H

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

#ifndef SPECULARSCALARSTRATEGY_H
#define SPECULARSCALARSTRATEGY_H

#include "ISpecularStrategy.h"
#include "ScalarRTCoefficients.h"
#include "Vectors3D.h"
#include <vector>
#include <memory>

class Slice;

//! Implements method 'execute' to compute refraction angles and transmission/reflection
//! coefficients for coherent wave propagation in a multilayer.
//! @ingroup algorithms_internal

class SpecularScalarStrategy : public ISpecularStrategy
{
public:

    //! Computes refraction angles and transmission/reflection coefficients
    //! for given coherent wave propagation in a multilayer.
    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    BA_CORE_API_ virtual ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                                             const kvector_t& k) const override;

    //! Computes transmission/reflection coefficients
    //! for given set of z-components of wave-vectors in a multilayer.
    //! Roughness is modelled by tanh profile [see e.g. Phys. Rev. B, vol. 47 (8), p. 4385 (1993)].
    BA_CORE_API_ virtual ISpecularStrategy::coeffs_t Execute(const std::vector<Slice>& slices,
                                                             const std::vector<complex_t>& kz) const override;
};

#endif // SPECULARSCALARSTRATEGY_H

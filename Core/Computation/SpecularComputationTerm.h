// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.h
//! @brief     Defines class SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARCOMPUTATIONTERM_H_
#define SPECULARCOMPUTATIONTERM_H_

#include <vector>

class IFresnelMap;
class MultiLayer;
class ProgressHandler;
class SimulationElement;
class SpecularSimulationElement;

//! Computes the specular scattering.
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularComputationTerm
{
    using SpecularElementIter = std::vector<SpecularSimulationElement>::iterator;
public:
    SpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void eval(ProgressHandler* progress, const SpecularElementIter& begin_it,
              const SpecularElementIter& end_it) const;

private:
    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
};

#endif /* SPECULARCOMPUTATIONTERM_H_ */

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

//! Computes the specular scattering.
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularComputationTerm
{
public:
    SpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void eval(ProgressHandler* progress, const std::vector<SimulationElement>::iterator& begin_it,
              const std::vector<SimulationElement>::iterator& end_it) const;

private:
    void evalSingle(const std::vector<SimulationElement>::iterator& iter) const;

    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
};

#endif /* SPECULARCOMPUTATIONTERM_H_ */

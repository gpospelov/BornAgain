// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/GISASSpecularComputationTerm.h
//! @brief     Defines class GISASSpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASSPECULARCOMPUTATIONTERM_H_
#define GISASSPECULARCOMPUTATIONTERM_H_

#include "IComputationTerm.h"
#include <vector>

class SimulationElement;

//! Computes the specular scattering. Used by DWBAComputation.
//! @ingroup algorithms_internal

class GISASSpecularComputationTerm final : public IComputationTerm
{
public:
    GISASSpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void compute(SimulationElement& elem) const;
};

#endif // GISASSPECULARCOMPUTATIONTERM_H_

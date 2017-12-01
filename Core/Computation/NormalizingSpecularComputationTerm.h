// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/NormalizingSpecularComputationTerm.h
//! @brief     Defines class NormalizingSpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NORMALIZINGSPECULARCOMPUTATIONTERM_H
#define NORMALIZINGSPECULARCOMPUTATIONTERM_H

#include "IComputationTerm.h"

//! Computes the specular scattering.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class NormalizingSpecularComputationTerm final : public IComputationTerm
{
public:
    NormalizingSpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void eval(ProgressHandler* progress,
              const std::vector<SimulationElement>::iterator& begin_it,
              const std::vector<SimulationElement>::iterator& end_it) const override;
};

#endif // NORMALIZINGSPECULARCOMPUTATIONTERM_H

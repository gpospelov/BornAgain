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

//! Computes the specular scattering. Used by DWBAComputation.
//! @ingroup algorithms_internal

class GISASSpecularComputationTerm final : public IComputationTerm
{
public:
    GISASSpecularComputationTerm(const MultiLayer* p_multi_layer, const IFresnelMap* p_fresnel_map);

    void setProgressHandler(ProgressHandler*) override {}

    void eval(ProgressHandler* progress, const std::vector<SimulationElement>::iterator& begin_it,
              const std::vector<SimulationElement>::iterator& end_it) const override;

private:
    void evalSingle(const std::vector<SimulationElement>::iterator& iter) const;
};

#endif // GISASSPECULARCOMPUTATIONTERM_H_

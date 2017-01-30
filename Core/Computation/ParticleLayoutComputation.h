// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.h
//! @brief     Defines class ParticleLayoutComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUTCOMPUTATION_H
#define PARTICLELAYOUTCOMPUTATION_H

#include "DelayedProgressCounter.h"
#include <vector>
#include <memory>

using std::size_t;

class Layer;
class ILayerSpecularInfo;
class ILayout;
class MultiLayer;
class ProgressHandler;
class SimulationElement;
class SimulationOptions;

//! Computes the scattering contribution from one particle layout.
//! Controlled by MainComputation.
//! @ingroup algorithms_internal

class ParticleLayoutComputation
{
public:
    ParticleLayoutComputation(const Layer* p_layer, const ILayout* p_layout);

    void setSpecularInfo(const ILayerSpecularInfo* p_specular_info);

    void eval(const SimulationOptions& options,
              ProgressHandler* progress,
              bool polarized,
              const std::vector<SimulationElement>::iterator& begin_it,
              const std::vector<SimulationElement>::iterator& end_it) const;

private:
    const Layer* mp_layer;
    const ILayout* mp_layout;
    const ILayerSpecularInfo* mp_specular_info;
};

#endif // PARTICLELAYOUTCOMPUTATION_H

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
#include "SafePointerVector.h"
#include <vector>

using std::size_t;

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
    ParticleLayoutComputation(const MultiLayer* p_multilayer, const ILayout* p_layout,
                              size_t layer_index);

    //! Sets magnetic reflection/transmission info for all layers
    void setSpecularInfo(const SafePointerVector<ILayerSpecularInfo>* p_specular_info);

    void eval(const SimulationOptions& options,
              ProgressHandler* progress,
              bool polarized,
              const std::vector<SimulationElement>::iterator& begin_it,
              const std::vector<SimulationElement>::iterator& end_it) const;

private:
    const MultiLayer* mp_multilayer;
    const ILayout* mp_layout;
    const SafePointerVector<ILayerSpecularInfo>* mp_specular_info_map;
    size_t m_layer_index;
};

#endif // PARTICLELAYOUTCOMPUTATION_H

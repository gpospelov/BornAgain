// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularComputation.h"
#include "LayerSpecularInfo.h"

SpecularComputation::SpecularComputation(const MultiLayer *p_multi_layer)
    : mp_multi_layer(p_multi_layer)
{}

void SpecularComputation::eval(
        const SimulationOptions &options,
        ProgressHandler *progress,
        bool polarized,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it)
{
    return;
}

void SpecularComputation::setSpecularInfo(const LayerSpecularInfo &specular_info)
{
    if (mP_specular_info.get() != &specular_info) {
        mP_specular_info.reset(specular_info.clone());
    }
}

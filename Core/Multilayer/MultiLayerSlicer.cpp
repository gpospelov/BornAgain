// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/MultiLayerSlicer.cpp
//! @brief     Implements class MultiLayerSlicer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiLayerSlicer.h"
#include "MultiLayer.h"
#include "Layer.h"

#include <sstream>

MultiLayerSlicer::MultiLayerSlicer(const MultiLayer& multilayer)
    : mP_multilayer{multilayer.clone()}
{}

std::string MultiLayerSlicer::slicedRepresentation() const
{
    auto P_sliced = mP_multilayer->cloneSliced(true);
    std::ostringstream rep;
    for (unsigned i=0; i<P_sliced->numberOfLayers(); i++) {
        auto p_layer = P_sliced->layer(i);
        rep << "Layer " << i << ", thickness: " << p_layer->thickness() << std::endl;
    }
    return rep.str();
}

MultiLayerSlicer::~MultiLayerSlicer() =default;

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

std::vector<double> MultiLayerSlicer::slicedThicknesses() const
{
    std::vector<double> result;
    auto P_sliced = mP_multilayer->cloneSliced(true);
    for (unsigned i=0; i<P_sliced->numberOfLayers(); i++) {
        result.push_back(P_sliced->layer(i)->thickness());
    }
    return result;
}

std::string MultiLayerSlicer::slicedRepresentation() const
{
    std::ostringstream rep;
    auto thicknesses = slicedThicknesses();
    for (unsigned i =0; i<thicknesses.size(); i++) {
        rep << "Layer " << i << ", thickness: " << thicknesses[i] << std::endl;
    }
    return rep.str();
}

MultiLayerSlicer::~MultiLayerSlicer() =default;

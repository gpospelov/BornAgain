// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/LayerDWBASimulation.cpp
//! @brief     Implements class LayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Layer.h"
#include "LayerDWBASimulation.h"

LayerDWBASimulation::LayerDWBASimulation(const Layer* p_layer)
: mp_specular_info(0)
{
    mp_layer = p_layer->clone();
}

LayerDWBASimulation::~LayerDWBASimulation()
{
    delete mp_layer;
    delete mp_specular_info;
}

Bin1DCVector LayerDWBASimulation::getKfBin(
    double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    return k_f_bin;
}

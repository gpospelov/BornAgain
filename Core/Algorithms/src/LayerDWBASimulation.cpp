// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerDWBASimulation.cpp
//! @brief     Implements class LayerDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerDWBASimulation.h"
#include "Layer.h"

#include <cassert>
#include <boost/scoped_ptr.hpp>

LayerDWBASimulation::LayerDWBASimulation(const Layer *p_layer)
: mp_specular_info(0)
{
    mp_layer = p_layer->clone();
}

LayerDWBASimulation::~LayerDWBASimulation()
{
    delete mp_layer;
    delete mp_specular_info;
}

Bin1DCVector LayerDWBASimulation::getKfBin(double wavelength,
        const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    return k_f_bin;
}


// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/LayerComputation.cpp
//! @brief     Implements class LayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerComputation.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"

LayerComputation::LayerComputation(const Layer* p_layer)
    : mp_specular_info(nullptr)
{
    mp_layer = p_layer->clone();
}

LayerComputation::~LayerComputation()
{
    delete mp_layer;
    delete mp_specular_info;
}

LayerComputation* LayerComputation::clone() const
{
    throw Exceptions::NotImplementedException(
        "Bug: unexpected call to LayerComputation::clone(); "
        "functionality not yet implemented");
}


void LayerComputation::setSpecularInfo(const LayerSpecularInfo& specular_info)
{
    if (mp_specular_info != &specular_info) {
        delete mp_specular_info;
        mp_specular_info = specular_info.clone();
    }
}

Bin1DCVector LayerComputation::getKfBin(
    double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin) const
{
    Bin1DCVector k_f_bin(wavelength, alpha_bin, phi_bin);
    return k_f_bin;
}

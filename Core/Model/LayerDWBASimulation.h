// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/LayerDWBASimulation.h
//! @brief     Defines class LayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERDWBASIMULATION_H
#define LAYERDWBASIMULATION_H

#include "DWBASimulation.h"

class Layer;
class LayerSpecularInfo;

//! Pure virtual base class for DWBA simulations in a layer.
//! Sole child is DecoratedLayerDWBASimulation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerDWBASimulation : public DWBASimulation
{
public:
    LayerDWBASimulation(const Layer* p_layer);
    virtual ~LayerDWBASimulation();
    LayerDWBASimulation* clone() const;

    void run() =0;

    void setSpecularInfo(const LayerSpecularInfo& specular_info);

protected:
    Bin1DCVector getKfBin(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin) const;

    Layer* mp_layer;
    LayerSpecularInfo* mp_specular_info;
};

#endif // LAYERDWBASIMULATION_H

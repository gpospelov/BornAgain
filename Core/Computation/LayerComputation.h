// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/LayerComputation.h
//! @brief     Defines class LayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERCOMPUTATION_H
#define LAYERCOMPUTATION_H

#include "Computation.h"

class Layer;
class LayerSpecularInfo;

//! Pure virtual base class for DWBA simulations in a layer.
//! Sole child is DecoratedLayerComputation.
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerComputation : public Computation
{
public:
    LayerComputation(const Layer* p_layer);
    virtual ~LayerComputation();
    LayerComputation* clone() const;

    void run() =0;

    void setSpecularInfo(const LayerSpecularInfo& specular_info);

protected:
    Bin1DCVector getKfBin(double wavelength, const Bin1D& alpha_bin, const Bin1D& phi_bin) const;

    Layer* mp_layer;
    LayerSpecularInfo* mp_specular_info;
};

#endif // LAYERCOMPUTATION_H

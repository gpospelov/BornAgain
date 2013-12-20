// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/LayerDWBASimulation.h
//! @brief     Defines class LayerDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERDWBASIMULATION_H_
#define LAYERDWBASIMULATION_H_

#include "DWBASimulation.h"
#include "LayerSpecularInfo.h"

//! @class LayerDWBASimulation
//! @ingroup algorithms_internal
//! @brief Base class for DWBA simulations in a layer.

class BA_CORE_API_ LayerDWBASimulation : public DWBASimulation
{
public:
    LayerDWBASimulation();
    virtual ~LayerDWBASimulation();

    LayerDWBASimulation *clone() const
    {
        throw NotImplementedException(
            "ISimulation::clone() -> Error: not implemented exception.");
    }

    void setSpecularInfo(const LayerSpecularInfo &specular_info);

protected:
    Bin1DCVector getKfBin(double wavelength, const Bin1D& alpha_bin,
                          const Bin1D& phi_bin) const;
    Bin1DCVector getKfBin1_matrix(double wavelength, const Bin1D& alpha_bin,
                          const Bin1D& phi_bin) const;
    Bin1DCVector getKfBin2_matrix(double wavelength, const Bin1D& alpha_bin,
                          const Bin1D& phi_bin) const;
    LayerSpecularInfo *mp_specular_info;
};

inline void LayerDWBASimulation::setSpecularInfo(
        const LayerSpecularInfo &specular_info) {
    if (mp_specular_info != &specular_info) {
        delete mp_specular_info;
        mp_specular_info = specular_info.clone();
    }
}

#endif /* LAYERDWBASIMULATION_H_ */



// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerSpecularInfo.h
//! @brief     Defines class LayerSpecularInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSPECULARINFO_H
#define LAYERSPECULARINFO_H

#include "ICloneable.h"
#include <memory>

class ISpecularInfoMap;
class ILayerRTCoefficients;
class SimulationElement;

//! Holds the amplitude information of the radiation wavefunction in a specific layer
//! for different incoming (outgoing) angles of the beam in the top layer
//! (these amplitudes correspond to the specular part of the neutron wavefunction).
//! @ingroup algorithms_internal

class BA_CORE_API_ LayerSpecularInfo : public ICloneable
{
public:
    LayerSpecularInfo();
    ~LayerSpecularInfo() final;

    LayerSpecularInfo* clone() const final;

    //! Adds the amplitude coefficients for the (time-reversed) outgoing
    //! wavevector with the given angles
    void addRTCoefficients(ISpecularInfoMap* rt_coefficient_map);

    //! Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector.
    const ILayerRTCoefficients* getOutCoefficients(const SimulationElement& sim_element) const;

    //! Retrieves the amplitude coefficients for an incoming wavevector.
    const ILayerRTCoefficients* getInCoefficients(const SimulationElement& sim_element) const;

private:
    std::unique_ptr<ISpecularInfoMap> mP_coeff_map;
};

#endif // LAYERSPECULARINFO_H
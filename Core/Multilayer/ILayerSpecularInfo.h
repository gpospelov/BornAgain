// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ILayerSpecularInfo.h
//! @brief     Defines class ILayerSpecularInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ILAYERSPECULARINFO_H
#define ILAYERSPECULARINFO_H

#include "ICloneable.h"

class ILayerRTCoefficients;
class SimulationElement;

//! Holds the necessary information to calculate the radiation wavefunction in a specific layer
//! for different incoming (outgoing) angles of the beam in the top layer
//! (these amplitudes correspond to the specular part of the wavefunction).
//! @ingroup algorithms_internal

class BA_CORE_API_ ILayerSpecularInfo : public ICloneable
{
public:
    ILayerSpecularInfo();
    ~ILayerSpecularInfo();

    ILayerSpecularInfo* clone() const =0;

    //! Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector.
    virtual const ILayerRTCoefficients* getOutCoefficients(
            const SimulationElement& sim_element) const =0;

    //! Retrieves the amplitude coefficients for an incoming wavevector.
    virtual const ILayerRTCoefficients* getInCoefficients(
            const SimulationElement& sim_element) const =0;
};

#endif // ILAYERSPECULARINFO_H

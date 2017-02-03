// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IFresnelMap.h
//! @brief     Defines class IFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFRESNELMAP_H
#define IFRESNELMAP_H

#include "INoncopyable.h"
#include <cstddef>

class ILayerRTCoefficients;
class SimulationElement;

//! Holds the necessary information to calculate the radiation wavefunction in every layer
//! for different incoming (outgoing) angles of the beam in the top layer
//! (these amplitudes correspond to the specular part of the wavefunction).
//! @ingroup algorithms_internal

class BA_CORE_API_ IFresnelMap : public INoncopyable
{
public:
    IFresnelMap();
    ~IFresnelMap();

    //! Retrieves the amplitude coefficients for a (time-reversed) outgoing wavevector.
    virtual const ILayerRTCoefficients* getOutCoefficients(
            const SimulationElement& sim_element, size_t layer_index) const =0;

    //! Retrieves the amplitude coefficients for an incoming wavevector.
    virtual const ILayerRTCoefficients* getInCoefficients(
            const SimulationElement& sim_element, size_t layer_index) const =0;
};

#endif // IFRESNELMAP_H

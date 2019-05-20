// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IMultiLayerFresnelMap.h
//! @brief     Defines class IMultiLayerFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMULTILAYERFRESNELMAP_H
#define IMULTILAYERFRESNELMAP_H

#include "IFresnelMap.h"

class MultiLayer;

//! Holds the necessary information to calculate the radiation wavefunction in every layer
//! for different incoming (outgoing) angles of the beam in the top layer
//! (these amplitudes correspond to the specular part of the wavefunction).
//! @ingroup algorithms_internal

class BA_CORE_API_ IMultiLayerFresnelMap : public IFresnelMap
{
public:
    IMultiLayerFresnelMap();
    virtual ~IMultiLayerFresnelMap();

    //! Sets the multilayer to be used for the Fresnel calculations.
    virtual void setMultilayer(const MultiLayer& multilayer);

protected:
    std::unique_ptr<MultiLayer> mP_multilayer;
};

#endif // IMULTILAYERFRESNELMAP_H

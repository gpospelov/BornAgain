// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IBeamFormFactor.h
//! @brief     Defines class IBeamFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IBEAMFORMFACTOR_H_
#define IBEAMFORMFACTOR_H_

#include "WinDllMacros.h"

class MultiLayer;
class Beam;

//! Defines abstract beam form-factor (spatial characteristics of the beam)
//! @ingroup simulation

class BA_CORE_API_ IBeamFormFactor
{
public:
    virtual ~IBeamFormFactor();

    //! Calculate footprint correction coefficient from _sample_ dimensions and the beam incident
    //! angle _alpha_.
    virtual double calculateFootprintFactor(const MultiLayer& sample, double alpha) const = 0;
};

#endif /* IBEAMFORMFACTOR_H_ */

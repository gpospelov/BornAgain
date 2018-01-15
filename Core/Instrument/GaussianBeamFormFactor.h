// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/GaussianBeamFormFactor.h
//! @brief     Defines class GaussianBeamFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GAUSSIANBEAMFORMFACTOR_H_
#define GAUSSIANBEAMFORMFACTOR_H_

#include "IBeamFormFactor.h"

//! Defines spatial characteristics of a gaussian beam

class BA_CORE_API_ GaussianBeamFormFactor : public IBeamFormFactor
{
public:
    GaussianBeamFormFactor(double width);
    virtual ~GaussianBeamFormFactor();

    //! Calculate footprint correction coefficient from _sample_ dimensions and the beam incident
    //! angle _alpha_.
    double calculateFootprintFactor(const MultiLayer& sample, double alpha) const override;

private:
    double m_beam_width; //! Characteristic full width on e^{-1/2} level from max. intensity
};

#endif /* GAUSSIANBEAMFORMFACTOR_H_ */

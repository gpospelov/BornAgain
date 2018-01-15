// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SquareBeamFormFactor.h
//! @brief     Defines class SquareBeamFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SQUAREBEAMFORMFACTOR_H_
#define SQUAREBEAMFORMFACTOR_H_

#include "IBeamFormFactor.h"

//! Defines spatial characteristics of a square beam

class BA_CORE_API_ SquareBeamFormFactor : public IBeamFormFactor
{
public:
    SquareBeamFormFactor(double width);
    virtual ~SquareBeamFormFactor();

    //! Calculate footprint correction coefficient from _sample_ dimensions and the beam incident
    //! angle _alpha_.
    double calculateFootprintFactor(const MultiLayer& sample, double alpha) const override;

private:
    double m_beam_width; //! Beam full width
};

#endif /* SQUAREBEAMFORMFACTOR_H_ */

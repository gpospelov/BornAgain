//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Beam/FootprintSquare.h
//! @brief     Defines class FootprintSquare.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_BEAM_FOOTPRINTSQUARE_H
#define BORNAGAIN_DEVICE_BEAM_FOOTPRINTSQUARE_H

#include "Device/Beam/IFootprintFactor.h"

//! Calculates footprint coefficient for a square beam
//! @ingroup beam

class FootprintSquare : public IFootprintFactor
{
public:
    FootprintSquare(const std::vector<double> P);
    FootprintSquare(double width_ratio);

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    FootprintSquare* clone() const override;

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;

    //! Print python-formatted footprint definition
    std::string print() const override;
};

#endif // BORNAGAIN_DEVICE_BEAM_FOOTPRINTSQUARE_H

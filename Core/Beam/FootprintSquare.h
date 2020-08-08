// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintSquare.h
//! @brief     Defines class FootprintSquare.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BEAM_FOOTPRINTFACTORSQUARE_H
#define BORNAGAIN_CORE_BEAM_FOOTPRINTFACTORSQUARE_H

#include "Core/Beam/IFootprintFactor.h"

//! Calculates footprint coefficient for a square beam
//! @ingroup beam

class BA_CORE_API_ FootprintSquare : public IFootprintFactor
{
public:
    FootprintSquare(double width_ratio);

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    FootprintSquare* clone() const override;

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;

    //! Print python-formatted footprint definition
    std::string print() const override;

protected:
    FootprintSquare(const FootprintSquare& other);

private:
    void initialize();
};

#endif // BORNAGAIN_CORE_BEAM_FOOTPRINTFACTORSQUARE_H

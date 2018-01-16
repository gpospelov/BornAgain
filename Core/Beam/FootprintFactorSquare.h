// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintFactorSquare.h
//! @brief     Defines class FootprintFactorSquare.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FOOTPRINTFACTORSQUARE_H_
#define FOOTPRINTFACTORSQUARE_H_

#include "IFootprintFactor.h"

//! Defines spatial characteristics of a square beam
//! @ingroup simulation

class BA_CORE_API_ FootprintFactorSquare : public IFootprintFactor
{
public:
    FootprintFactorSquare(double width);
    virtual ~FootprintFactorSquare();

    //! Calculate footprint correction coefficient from _sample_ dimensions and the beam incident
    //! angle _alpha_.
    double calculate(const MultiLayer& sample, double alpha) const override;

private:
    double m_beam_width; //! Beam full width
};

#endif /* FOOTPRINTFACTORSQUARE_H_ */

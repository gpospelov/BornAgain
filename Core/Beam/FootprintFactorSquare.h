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
    //! Creates footprint factor calculator for a square beam.
    //! @param width_ratio The ratio of the beam full width to the width of a sample.
    FootprintFactorSquare(double width_ratio);
    virtual ~FootprintFactorSquare();

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;

private:
    double m_width_ratio; //! Beam to sample widths ratio
};

#endif /* FOOTPRINTFACTORSQUARE_H_ */

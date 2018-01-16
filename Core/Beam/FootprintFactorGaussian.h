// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Beam/FootprintFactorGaussian.h
//! @brief     Defines class FootprintFactorGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FOOTPRINTFACTORGAUSSIAN_H
#define FOOTPRINTFACTORGAUSSIAN_H

#include "IFootprintFactor.h"

//! Calculates footprint coefficient for a gaussian beam
//! Beam width is interpreted as the full width on the level
//! of \f[ \exp{-1/2} \f] from the peak intensity.
//! @ingroup simulation

class BA_CORE_API_ FootprintFactorGaussian : public IFootprintFactor
{
public:
    using IFootprintFactor::IFootprintFactor;

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;
};

#endif /* FOOTPRINTFACTORGAUSSIAN_H */

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

//! Defines spatial characteristics of a Gaussian beam
//! @ingroup simulation

class BA_CORE_API_ FootprintFactorGaussian : public IFootprintFactor
{
public:
    //! Creates footprint factor calculator for a gaussian beam.
    //! @param width_ratio The ratio of the beam characteristic full width on e^{-1/2} level from
    //! max. intensity to the width of a sample.
    FootprintFactorGaussian(double width_ratio);
    virtual ~FootprintFactorGaussian();

    //! Calculate footprint correction coefficient from the beam incident angle _alpha_.
    double calculate(double alpha) const override;

private:
    //! The ratio of the beam characteristic full width on e^{-1/2} level from max. intensity
    //! to the width of a sample
    double m_width_ratio;
};

#endif /* FOOTPRINTFACTORGAUSSIAN_H */

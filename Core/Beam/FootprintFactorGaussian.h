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
    FootprintFactorGaussian(double width);
    virtual ~FootprintFactorGaussian();

    //! Calculate footprint correction coefficient from _sample_ dimensions and the beam incident
    //! angle _alpha_.
    double calculate(const MultiLayer& sample, double alpha) const override;

private:
    //! Characteristic full width on e^{-1/2} level from max. intensity,
    //! i.e. \f[ 2 \sigma \f] of Gaussian distribution
    double m_beam_width;
};

#endif /* FOOTPRINTFACTORGAUSSIAN_H */

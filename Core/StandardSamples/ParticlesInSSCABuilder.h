// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParticlesInSSCABuilder.h
//! @brief     Defines class ParticlesInSSCABuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLESINSSCABUILDER_H
#define PARTICLESINSSCABUILDER_H

#include "ISampleBuilder.h"

//! @class ParticlesInSCCABuilder
//! @ingroup standard_samples
//! @brief Builds sample: size spacing correlation approximation
//! (IsGISAXS example #15)

class BA_CORE_API_ ParticlesInSSCABuilder : public ISampleBuilder
{
public:
    ParticlesInSSCABuilder();
    ISample *buildSample() const;
};

#endif // PARTICLESINSSCABUILDER_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS11Builder.h
//! @brief     Defines class IsGISAXS11Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS11BUILDER_H
#define ISGISAXS11BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS11Builder
//! @ingroup standard_samples
//! @brief Builds sample: Core Shell Nanoparticles (IsGISAXS example #11)

class IsGISAXS11Builder : public ISampleBuilder
{
public:
    IsGISAXS11Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS11BUILDER_H

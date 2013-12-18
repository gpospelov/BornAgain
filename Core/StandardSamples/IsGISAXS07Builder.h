// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS07Builder.h
//! @brief     Defines class IsGISAXS07Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS07BUILDER_H
#define ISGISAXS07BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS07Builder
//! @ingroup standard_samples
//! @brief Builds sample: mixture of different particles (IsGISAXS example #7)

class IsGISAXS07Builder : public ISampleBuilder
{
public:
    IsGISAXS07Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS07BUILDER_H

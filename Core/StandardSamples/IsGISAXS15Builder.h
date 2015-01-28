// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS15Builder.h
//! @brief     Defines class IsGISAXS15Builder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS15BUILDER_H
#define ISGISAXS15BUILDER_H

#include "ISampleBuilder.h"

//! @class IsGISAXS15Builder
//! @ingroup standard_samples
//! @brief Builds sample: size spacing correlation approximation
//! (IsGISAXS example #15)

class BA_CORE_API_ IsGISAXS15Builder : public ISampleBuilder
{
public:
    IsGISAXS15Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS15BUILDER_H

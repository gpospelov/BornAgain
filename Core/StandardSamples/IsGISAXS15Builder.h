// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IsGISAXS15Builder.h
//! @brief     Defines class IsGISAXS15Builder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXS15BUILDER_H
#define ISGISAXS15BUILDER_H

#include "ISampleBuilder.h"

//! The IsGISAXS15Builder class to build sample: size spacing correlation approximation
//! (IsGISAXS example #15)
class IsGISAXS15Builder : public ISampleBuilder
{
public:
    IsGISAXS15Builder();
    ISample *buildSample() const;
};

#endif // ISGISAXS15BUILDER_H

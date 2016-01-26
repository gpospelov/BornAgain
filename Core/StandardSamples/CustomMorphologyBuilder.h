// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CustomMorphologyBuilder.h
//! @brief     Defines class CustomMorphologyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUSTOMMORPHOLOGYBUILDER_H
#define CUSTOMMORPHOLOGYBUILDER_H

#include "ISampleBuilder.h"

//! @class CustomMorphologyBuilder
//! @ingroup standard_samples
//! @brief Builds sample: mixture of different particles (IsGISAXS example #7)

class BA_CORE_API_ CustomMorphologyBuilder : public ISampleBuilder
{
public:
    CustomMorphologyBuilder();
    ISample *buildSample() const;
};

#endif // CUSTOMMORPHOLOGYBUILDER_H


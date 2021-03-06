//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/StandardSamples/MultipleLayoutBuilder.h
//! @brief     Defines class MultipleLayoutBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_MULTIPLELAYOUTBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_MULTIPLELAYOUTBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: mixture of cylinders and prisms without interference,
//! using multiple particle layouts
//! @ingroup standard_samples

class MultipleLayoutBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_MULTIPLELAYOUTBUILDER_H
#endif // USER_API

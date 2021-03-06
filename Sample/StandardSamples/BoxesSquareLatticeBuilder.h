//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/StandardSamples/BoxesSquareLatticeBuilder.h
//! @brief     Defines class BoxesSquareLattice2DBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_BOXESSQUARELATTICEBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_BOXESSQUARELATTICEBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: square boxes in a square lattice
//! @ingroup standard_samples

class BoxesSquareLattice2DBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_BOXESSQUARELATTICEBUILDER_H
#endif // USER_API

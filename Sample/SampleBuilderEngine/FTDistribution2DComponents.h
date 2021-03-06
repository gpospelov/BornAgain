//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/SampleBuilderEngine/FTDistribution2DComponents.h
//! @brief     Defines sample components for complex sample builders.
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
#ifndef BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_FTDISTRIBUTION2DCOMPONENTS_H
#define BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_FTDISTRIBUTION2DCOMPONENTS_H

#include "Sample/Correlations/FTDistributions2D.h"
#include "Sample/SampleBuilderEngine/IRegistry.h"

//! @class FTDistribution2DComponents
//! @brief Predefined Fourier transformed distributions for functional tests.

class FTDistribution2DComponents : public IRegistry<IFTDistribution2D> {
public:
    FTDistribution2DComponents();
};

#endif // BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_FTDISTRIBUTION2DCOMPONENTS_H
#endif // USER_API

//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/SampleBuilderEngine/FTDistribution2DComponents.cpp
//! @brief     Implements sample components for complex sample builders.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/SampleBuilderEngine/FTDistribution2DComponents.h"

//  ************************************************************************************************
FTDistribution2DComponents::FTDistribution2DComponents()
//  ************************************************************************************************
{
    add("FTDistribution2DCauchy", new FTDistribution2DCauchy(0.5, 1.0, 0));
    add("FTDistribution2DGauss", new FTDistribution2DGauss(0.5, 1.0, 0));
    add("FTDistribution2DGate", new FTDistribution2DGate(0.5, 1.0, 0));
    add("FTDistribution2DCone", new FTDistribution2DCone(0.5, 1.0, 0));
    add("FTDistribution2DVoigt", new FTDistribution2DVoigt(0.5, 1.0, 0, 0.2));
}

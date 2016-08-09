// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IReferencedTest.cpp
//! @brief     Implements pure virtual base class IReferencedTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IReferencedTest.h"
#include "IntensityDataFunctions.h"
#include <iostream>

IFunctionalTest::ETestResult IReferencedTest::compareIntensityMaps(
    const OutputData<double>& dat, const OutputData<double>& ref) const
{
    if( dat.getVariability() != ref.getVariability() ) {
        std::cerr << "Failed: reproducibility threshold has changed from "
                  << ref.getVariability()
                  << " to " << dat.getVariability() << "." << std::endl;
        return FAILED_DIFF;
    }
    double threshold = ref.getVariability();
    double diff = IntensityDataFunctions::getRelativeDifference(dat, ref);
    if ( diff > threshold ) {
        std::cerr << "Failed: Relative difference between dat and ref = " << diff
                  << " is above reproducibility threshold = " << threshold << "." << std::endl;
        return FAILED_DIFF;
    }
    std::cout << "Relative difference between dat and ref = " << diff
                  << " is within reproducibility threshold = " << threshold << "." << std::endl;
    return SUCCESS;
}

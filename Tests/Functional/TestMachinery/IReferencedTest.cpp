// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Referenced/TestMachinery/IReferencedTest.cpp
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
    const OutputData<double>& dat, const OutputData<double>& ref)
{
    double diff = IntensityDataFunctions::getRelativeDifference(dat, ref);
    if ( diff > m_threshold) {
        std::cerr << "Failed: Relative difference between dat and ref = " << diff
                  << " is above threshold = " << m_threshold << "." << std::endl;
        return FAILED_DIFF;
    }
    std::cout << "Relative difference between dat and ref = " << diff
                  << " is within threshold = " << m_threshold << "." << std::endl;
    return SUCCESS;
}

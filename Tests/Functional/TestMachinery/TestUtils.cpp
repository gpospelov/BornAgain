// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.cpp
//! @brief     Implements TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/TestMachinery/TestUtils.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

bool TestUtils::isTheSame(const OutputData<double>& dat, const OutputData<double>& ref,
                          double threshold)
{
    double diff = IntensityDataFunctions::getRelativeDifference(dat, ref);
    if (diff > threshold) {
        std::cerr << "  => FAILED: relative deviation of dat from ref is " << diff
                  << ", above given threshold " << threshold << "\n";
        return false;
    }
    if (diff)
        std::cerr << "  => OK: relative deviation of dat from ref is " << diff
                  << ", within given threshold " << threshold << "\n";
    else
        std::cout << "  => OK: dat = ref\n";
    return true;
}

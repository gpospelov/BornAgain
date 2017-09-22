// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.h
//! @brief     Defines TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "WinDllMacros.h"
#include "StandardTestInfo.h"
#include "OutputData.h"

namespace TestUtils
{

//! Returns test info for given set of command line parameters.
StandardTestInfo testInfo(int argc, char** argv);

//! Returns true if intensity maps are the same within given threshold.
bool isTheSame(const OutputData<double>& dat, const OutputData<double>& ref, double threshold);

}


#endif

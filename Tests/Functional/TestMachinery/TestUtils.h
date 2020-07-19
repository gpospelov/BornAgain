// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/TestUtils.h
//! @brief     Defines TestUtils namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTUTILS_H
#define BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTUTILS_H

#include "Core/Instrument/OutputData.h"
#include "Wrap/WinDllMacros.h"

namespace TestUtils
{

//! Returns true if intensity maps are the same within given threshold.
BA_CORE_API_ bool isTheSame(const OutputData<double>& dat, const OutputData<double>& ref,
                            double threshold);

} // namespace TestUtils

#endif // BORNAGAIN_TESTS_FUNCTIONAL_TESTMACHINERY_TESTUTILS_H

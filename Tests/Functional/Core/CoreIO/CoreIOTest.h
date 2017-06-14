// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreIO/CoreIOTest.h
//! @brief     Defines CoreIOTest class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COREIOTEST_H
#define COREIOTEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include <memory>

//! Functional test to validate read/write of large data files.

class CoreIOTest : public IFunctionalTest
{
public:
    CoreIOTest() {}
    ~CoreIOTest() {}

    bool runTest();

private:
    std::unique_ptr<OutputData<double>> createData(int nx, int ny, bool fill = false);
    double biggest_difference(const OutputData<double>& data, const OutputData<double>& ref);
};

#endif // COREIOTEST_H

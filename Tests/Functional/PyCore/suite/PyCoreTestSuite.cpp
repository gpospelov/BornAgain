// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/suite/PyCoreTestSuite.cpp
//! @brief     Implements program PyCoreTestSuite, to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "PySuiteTest.h"

class PyCoreTestSuite : public IStandardTest
{
public:
    PyCoreTestSuite() : IStandardTest("PySuite") {}
    IFunctionalTest* getTest() const { return new PySuiteTest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! The main function of PySuite, to run functional tests
int main(int argc, char** argv)
{
    return PyCoreTestSuite().execute(argc, argv);
}

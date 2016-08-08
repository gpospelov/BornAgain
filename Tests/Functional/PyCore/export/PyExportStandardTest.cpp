// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/export/PyExportStandardTest.cpp
//! @brief     Implements program PyExportStandardTest, to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "PyExportTest.h"

//! Provides a PyExportTest through a callback mechanism explained in IStandardTest.h.
class PyExportStandardTest : public IStandardTest
{
public:
    PyExportStandardTest() : IStandardTest("PyExport") {}
    IFunctionalTest* getTest() const { return new PyExportTest(
            getName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! Runs PyExportTest on a standard simulation indicated by argv[1].
int main(int argc, char** argv)
{
    return PyExportStandardTest().execute(argc, argv);
}

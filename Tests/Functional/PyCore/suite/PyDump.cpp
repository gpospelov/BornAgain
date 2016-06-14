// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestPyDump/PyDump.cpp
//! @brief     Implements program PySuite, to run pyscript functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FutestSuite.h"
#include "FutestRegistry.h"
#include "PyScriptFutest.h"

class PySuite : public FutestSuite, public ISingleton<PySuite>
{
public:
    PySuite() { setName("PySuite"); }
    IFutest* getFutest() const { return new PyScriptFutest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! The main function of PyTestSuite, to run functional tests
int main(int argc, char** argv)
{
    return PySuite::instance().execute(argc, argv);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestCore/CoreSuite.cpp
//! @brief     Implements program CoreSuite, to run core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FutestSuite.h"
#include "CoreFutest.h"

class CoreSuite : public FutestSuite
{
public:
    CoreSuite() { setName("CoreSuite"); }
    IFutest* getFutest() const { return new CoreFutest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold() ); }
};

//! The main function of CoreSuite, to run functional tests
int main(int argc, char** argv)
{
    return CoreSuite().execute(argc, argv);
}

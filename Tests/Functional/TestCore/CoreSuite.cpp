// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/core_functional_test.h
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
#include "FutestRegistry.h"
#include "CoreFutest.h"

class CoreSuite : public FutestSuite, public ISingleton<CoreSuite>
{
public:
    CoreSuite() { setName("CoreSuite"); }
    IFutest* getFutest() const { return new CoreFutest(
            getTestName(), getTestDescription(), getSimulation(),
            getReferenceData(), getTestThreshold(), getReferenceFileName() ); }
};

//! The main function of CoreSuite, to run functional tests
int main(int argc, char** argv)
{
    return CoreSuite::instance().execute(argc, argv);
}

//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testintegration/toyitemslattice.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"

using namespace ModelView;
using namespace ToyItems;

//! Test toy LatticeItem.

class ToyItemsLatticeTest : public ::testing::Test {
public:
    ~ToyItemsLatticeTest();
};

ToyItemsLatticeTest::~ToyItemsLatticeTest() = default;

//! Business logice (enabled/disabled).

TEST_F(ToyItemsLatticeTest, ToyItemsLatticeTest)
{
    ToyItems::SampleModel model;
    auto lattice = model.insertItem<LatticeItem>();

    // by default integration flag is ON, rotation angle is disabled
    EXPECT_TRUE(lattice->property<bool>(LatticeItem::P_INTEGRATION));
    EXPECT_FALSE(lattice->getItem(LatticeItem::P_ROTATION_ANLE)->isEnabled());

    // switching integration OFF, checking that rotation is enabled
    lattice->setProperty(LatticeItem::P_INTEGRATION, false);
    EXPECT_TRUE(lattice->getItem(LatticeItem::P_ROTATION_ANLE)->isEnabled());
}

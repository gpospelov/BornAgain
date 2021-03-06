//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testmodel/plottableitems.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/standarditems/plottableitems.h"
#include <QColor>

using namespace ModelView;

//! Testing PlottableItemsTest.

class PlottableItemsTest : public ::testing::Test {
public:
    ~PlottableItemsTest();
};

PlottableItemsTest::~PlottableItemsTest() = default;

//! Initial state.

TEST_F(PlottableItemsTest, penItem_initialState)
{
    PenItem item;
    EXPECT_EQ(item.property<QColor>(PenItem::P_COLOR), QColor(Qt::black));
    EXPECT_EQ(item.property<int>(PenItem::P_WIDTH), 1);
    EXPECT_EQ(item.property<ComboProperty>(PenItem::P_STYLE).currentIndex(), Qt::SolidLine);
}

TEST_F(PlottableItemsTest, penItem_setSelected)
{
    PenItem item;

    item.setSelected(true);
    EXPECT_EQ(item.property<ComboProperty>(PenItem::P_STYLE).currentIndex(), Qt::DashLine);

    item.setSelected(false);
    EXPECT_EQ(item.property<ComboProperty>(PenItem::P_STYLE).currentIndex(), Qt::SolidLine);
}

TEST_F(PlottableItemsTest, penItem_setNamedColor)
{
    PenItem item;
    item.setNamedColor("mediumaquamarine");
    EXPECT_EQ(item.colorName(), std::string("#66cdaa"));
}

//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testmodel/itemmanager.test.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "mvvm/model/itemmanager.h"
#include "mvvm/model/itempool.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include <memory>

using namespace ModelView;

//! Testing ItemFactory in the context of SessionModel and unique identifiers of SessionItem.

class ItemManagerTest : public ::testing::Test {
public:
    ~ItemManagerTest();
};

ItemManagerTest::~ItemManagerTest() = default;

TEST_F(ItemManagerTest, initialState)
{
    ItemManager manager;
    EXPECT_EQ(manager.itemPool(), nullptr);

    std::shared_ptr<ItemPool> pool(new ItemPool);
    manager.setItemPool(pool);
    EXPECT_EQ(manager.itemPool(), pool.get());
    EXPECT_EQ(manager.itemPool()->size(), 0);
}

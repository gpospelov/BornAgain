#include "google_test.h"
#include "SessionItemUtils.h"
#include "SessionModel.h"
#include "SessionItem.h"
#include "VectorItem.h"
#include "item_constants.h"

class TestSessionItemUtils : public ::testing::Test
{
public:
    ~TestSessionItemUtils();
};

TestSessionItemUtils::~TestSessionItemUtils() = default;

//! Test SessionItemUtils::ParentVisibleRow utility method.

TEST_F(TestSessionItemUtils, test_ParentVisibleRow)
{
    SessionModel model("TestModel");

    // 3 property items in root, all visible
    auto item1 = model.insertNewItem(Constants::PropertyType);
    auto item2 = model.insertNewItem(Constants::PropertyType);
    auto item3 = model.insertNewItem(Constants::PropertyType);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item1), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item2), 1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item3), 2);

    // one item become invisible
    item2->setVisible(false);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item1), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item2), -1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item3), 1);

    // two more items
    auto item4 = model.insertNewItem(Constants::PropertyType);
    auto item5 = model.insertNewItem(Constants::PropertyType);
    item5->setVisible(false);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item1), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item2), -1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item3), 1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item4), 2);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*item5), -1);

    // adding vector item
    SessionItem* vector = model.insertNewItem(Constants::VectorType);
    auto x = vector->getItem(VectorItem::P_X);
    auto y = vector->getItem(VectorItem::P_Y);
    auto z = vector->getItem(VectorItem::P_Z);
    x->setVisible(false);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*x), -1);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*y), 0);
    EXPECT_EQ(SessionItemUtils::ParentVisibleRow(*z), 1);
}

#include "google_test.h"
#include "SessionItemUtils.h"
#include "SessionModel.h"
#include "SessionItem.h"
#include "ExternalProperty.h"
#include "ComboProperty.h"
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

//! Comparing types of variant.

TEST_F(TestSessionItemUtils, VariantType)
{
    EXPECT_TRUE(SessionItemUtils::VariantType(QVariant::fromValue(1.0))
                == SessionItemUtils::VariantType(QVariant::fromValue(2.0)));
    EXPECT_FALSE(SessionItemUtils::VariantType(QVariant::fromValue(1.0))
                 == SessionItemUtils::VariantType(QVariant::fromValue(1)));
    EXPECT_FALSE(SessionItemUtils::VariantType(QVariant::fromValue(1.0))
                 == SessionItemUtils::VariantType(QVariant::fromValue(QString("a"))));

    QVariant v1, v2;
    EXPECT_TRUE(SessionItemUtils::VariantType(v1) == SessionItemUtils::VariantType(v2));
    EXPECT_FALSE(SessionItemUtils::VariantType(v1)
                 == SessionItemUtils::VariantType(QVariant::fromValue(42.0)));

    ComboProperty c1, c2;
    EXPECT_TRUE(SessionItemUtils::VariantType(c1.variant())
                == SessionItemUtils::VariantType(c2.variant()));
    EXPECT_FALSE(SessionItemUtils::VariantType(c1.variant())
                 == SessionItemUtils::VariantType(QVariant::fromValue(42.0)));
    EXPECT_FALSE(SessionItemUtils::VariantType(c1.variant())
                 == SessionItemUtils::VariantType(QVariant()));

    ExternalProperty p1, p2;
    EXPECT_TRUE(SessionItemUtils::VariantType(p1.variant())
                == SessionItemUtils::VariantType(p2.variant()));
    EXPECT_FALSE(SessionItemUtils::VariantType(p1.variant())
                 == SessionItemUtils::VariantType(QVariant::fromValue(42.0)));
    EXPECT_FALSE(SessionItemUtils::VariantType(p1.variant())
                 == SessionItemUtils::VariantType(c1.variant()));
    EXPECT_FALSE(SessionItemUtils::VariantType(p1.variant())
                 == SessionItemUtils::VariantType(QVariant()));
}

//! Test variant equality reported by SessionItemUtils::isTheSame

TEST_F(TestSessionItemUtils, IsTheSameVariant)
{
    // comparing undefined variants
    QVariant v1, v2;
    EXPECT_TRUE(SessionItemUtils::IsTheSame(v1, v2));

    // comparing QVariant based on double
    EXPECT_TRUE(SessionItemUtils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(1.0)));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(2.0)));

    // comparing QVariant based on strings
    EXPECT_TRUE(SessionItemUtils::IsTheSame(QVariant::fromValue(QString("a")),
                                            QVariant::fromValue(QString("a"))));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(QVariant::fromValue(QString("a")),
                                             QVariant::fromValue(QString("b"))));

    // comparing variants of different type
    EXPECT_FALSE(SessionItemUtils::IsTheSame(QVariant::fromValue(1.0), QVariant::fromValue(1)));

    // comparing custom variants (should be always false)
    ExternalProperty p1, p2;
    EXPECT_FALSE(SessionItemUtils::IsTheSame(p1.variant(), p2.variant()));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(p1.variant(), QVariant::fromValue(42.0)));

    ComboProperty c1, c2;
    EXPECT_FALSE(SessionItemUtils::IsTheSame(c1.variant(), c2.variant()));
    EXPECT_FALSE(SessionItemUtils::IsTheSame(c1.variant(), QVariant::fromValue(42.0)));

    EXPECT_FALSE(SessionItemUtils::IsTheSame(p1.variant(), c1.variant()));
}

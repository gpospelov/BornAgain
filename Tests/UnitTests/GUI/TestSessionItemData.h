#include "google_test.h"
#include "SessionItemData.h"
#include "ExternalProperty.h"
#include "SessionFlags.h"

class TestSessionItemData : public ::testing::Test
{
public:
    ~TestSessionItemData();
};

TestSessionItemData::~TestSessionItemData() = default;

TEST_F(TestSessionItemData, initialState)
{
    SessionItemData itemData;
    EXPECT_TRUE(itemData.roles().isEmpty());
    EXPECT_FALSE(itemData.data(Qt::DisplayRole).isValid());
}

TEST_F(TestSessionItemData, setData)
{
    SessionItemData itemData;

    // setting DisplayRole
    QVariant v(42.0);
    EXPECT_TRUE(itemData.setData(Qt::DisplayRole, v));
    QVector<int> expected {Qt::DisplayRole};
    EXPECT_EQ(itemData.roles(), expected);
    EXPECT_TRUE(itemData.data(Qt::DisplayRole) == v);

    // setting same data twice
    EXPECT_FALSE(itemData.setData(Qt::DisplayRole, v));
    EXPECT_EQ(itemData.roles(), expected);

    // changing the data
    v.setValue(43.0);
    EXPECT_TRUE(itemData.setData(Qt::DisplayRole, v));
    EXPECT_EQ(itemData.roles(), expected);
    EXPECT_TRUE(itemData.data(Qt::DisplayRole) == QVariant(43.0));

    // setting invalid variant for the role
    EXPECT_TRUE(itemData.setData(Qt::DisplayRole, QVariant()));
    EXPECT_TRUE(itemData.roles().isEmpty());
    EXPECT_FALSE(itemData.data(Qt::DisplayRole).isValid());

    // Setting custom variant
    ExternalProperty ep;
    ep.setIdentifier("abc");

    EXPECT_TRUE(itemData.setData(Qt::DisplayRole, ep.variant()));
    EXPECT_TRUE(itemData.setData(SessionFlags::CustomEditorRole, QVariant::fromValue(QString("abc"))));

    expected = {Qt::DisplayRole, SessionFlags::CustomEditorRole};
    EXPECT_EQ(itemData.roles(), expected);

    EXPECT_EQ(itemData.data(Qt::DisplayRole).value<ExternalProperty>(), ep);
    EXPECT_EQ(itemData.data(SessionFlags::CustomEditorRole).toString(), QString("abc"));
}

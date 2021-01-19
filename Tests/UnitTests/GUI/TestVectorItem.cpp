#include "GUI/coregui/Models/VectorItem.h"
#include "Tests/GTestWrapper/google_test.h"

//! Tests VectorItem class.

class TestVectorItem : public ::testing::Test {
};

//! The initial state.

TEST_F(TestVectorItem, initialState)
{
    VectorItem item;

    EXPECT_EQ(item.x(), 0.0);
    EXPECT_EQ(item.y(), 0.0);
    EXPECT_EQ(item.z(), 0.0);

    auto kvec = item.getVector();
    EXPECT_EQ(kvec.x(), 0.0);
    EXPECT_EQ(kvec.y(), 0.0);
    EXPECT_EQ(kvec.z(), 0.0);
}

//! Setters.

TEST_F(TestVectorItem, setXYZ)
{
    VectorItem item;

    item.setX(1.0);
    item.setY(2.0);
    item.setZ(3.0);

    EXPECT_EQ(item.x(), 1.0);
    EXPECT_EQ(item.y(), 2.0);
    EXPECT_EQ(item.z(), 3.0);

    auto kvec = item.getVector();
    EXPECT_EQ(kvec.x(), 1.0);
    EXPECT_EQ(kvec.y(), 2.0);
    EXPECT_EQ(kvec.z(), 3.0);
}

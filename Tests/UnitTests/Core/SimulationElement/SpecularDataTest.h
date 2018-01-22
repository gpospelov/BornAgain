#include "google_test.h"
#include "SpecularData.h"

class SpecularDataTest : public ::testing::Test
{
protected:
    SpecularDataTest();
    ~SpecularDataTest();

    std::vector<ScalarRTCoefficients> test_data;
};

SpecularDataTest::SpecularDataTest()
{
    constexpr size_t size = 10;
    test_data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        test_data[i].kz = 1.0;
        test_data[i].lambda = 1.0;
    }
}

SpecularDataTest::~SpecularDataTest() = default;

TEST_F(SpecularDataTest, InitialState)
{
    SpecularData spec_data;
    EXPECT_FALSE(spec_data.isInited());
    EXPECT_THROW(spec_data[0], std::runtime_error);
}

TEST_F(SpecularDataTest, InvalidData)
{
    std::vector<MatrixRTCoefficients> invalid_data;
    SpecularData spec_data(invalid_data);

    EXPECT_TRUE(spec_data.isInited());
    EXPECT_THROW(spec_data[0], std::runtime_error);

    std::vector<ScalarRTCoefficients> invalid_data2;
    SpecularData spec_data2(invalid_data2);

    EXPECT_TRUE(spec_data2.isInited());
    EXPECT_THROW(spec_data2[0], std::runtime_error);

    SpecularData spec_data3(test_data);
    EXPECT_THROW(spec_data3[test_data.size()], std::runtime_error);
}

TEST_F(SpecularDataTest, CopyMoveAssign)
{
    SpecularData spec_data(test_data);

    EXPECT_TRUE(spec_data.isInited());
    EXPECT_EQ(spec_data[0].getScalarKz(), test_data[0].getScalarKz());

    SpecularData spec_data2 = spec_data;

    EXPECT_TRUE(spec_data2.isInited());
    EXPECT_TRUE(spec_data.isInited());
    EXPECT_EQ(spec_data2[1].getScalarKz(), test_data[1].getScalarKz());
    EXPECT_EQ(spec_data2[1].getScalarKz(), spec_data[1].getScalarKz());

    SpecularData spec_data3;
    spec_data3 = spec_data;

    EXPECT_TRUE(spec_data3.isInited());
    EXPECT_TRUE(spec_data.isInited());
    EXPECT_EQ(spec_data3[1].getScalarKz(), test_data[1].getScalarKz());
    EXPECT_EQ(spec_data3[1].getScalarKz(), spec_data[1].getScalarKz());

    SpecularData spec_data4;
    spec_data4 = std::move(spec_data);

    EXPECT_TRUE(spec_data4.isInited());
    EXPECT_EQ(spec_data4[1].getScalarKz(), test_data[1].getScalarKz());

    SpecularData spec_data5 = std::move(spec_data2);

    EXPECT_TRUE(spec_data5.isInited());
    EXPECT_EQ(spec_data5[1].getScalarKz(), test_data[1].getScalarKz());
}

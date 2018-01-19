#include "google_test.h"
#include "UnitConverters.h"
#include "Units.h"

class UnitConverterTest : public ::testing::Test
{
public:
    ~UnitConverterTest();
};

UnitConverterTest::~UnitConverterTest() = default;

TEST_F(UnitConverterTest, SphericalConverter)
{
    SphericalConverter converter(100, 0.0, 5.0*Units::deg,
                                 70, -2.0*Units::deg, 1.5);

    EXPECT_EQ(converter.dimension(), 2u);

    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEFAULT), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::NBINS), 100.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEGREES), 5.0);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}

TEST_F(UnitConverterTest, SphericalConverterClone)
{
    SphericalConverter converter(100, 0.0, 5.0*Units::deg,
                                 70, -2.0*Units::deg, 1.5);
    std::unique_ptr<SphericalConverter> P_clone(converter.clone());

    EXPECT_EQ(P_clone->dimension(), 2u);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_THROW(P_clone->calculateMin(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMin(0, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::DEFAULT), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::NBINS), 100.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(0, AxesUnits::DEGREES), 5.0);
    EXPECT_THROW(P_clone->calculateMax(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(0, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::DEFAULT), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(P_clone->calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_THROW(P_clone->calculateMin(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMin(1, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::DEFAULT), 1.5);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(P_clone->calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_THROW(P_clone->calculateMax(1, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(1, AxesUnits::QYQZ), std::runtime_error);

    EXPECT_THROW(P_clone->calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}

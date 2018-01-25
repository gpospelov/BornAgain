#include "google_test.h"
#include "Beam.h"
#include "SphericalDetector.h"
#include "UnitConverters.h"
#include "Units.h"
#include "Vectors3D.h"

class UnitConverterTest : public ::testing::Test
{
public:
    UnitConverterTest();
    ~UnitConverterTest();
protected:
    SphericalDetector m_detector;
    Beam m_beam;
    double m_kiz, m_kfy, m_kfz1, m_kfz2;
};

UnitConverterTest::UnitConverterTest()
    : m_detector(100, 0.0, 5.0*Units::deg, 70, -2.0*Units::deg, 1.5)
{
    m_beam.setCentralK(1.0, 1.0*Units::deg, 0.0);
    auto k_i = m_beam.getCentralK();
    m_kiz = k_i.z();
    double K = 2.0*M_PI/m_beam.getWavelength();
    m_kfy = K*std::sin(5.0*Units::deg);
    m_kfz1 = K*std::sin(-2.0*Units::deg);
    m_kfz2 = K*std::sin(1.5);
}

UnitConverterTest::~UnitConverterTest() = default;

TEST_F(UnitConverterTest, SphericalConverter)
{
    SphericalConverter converter(m_detector, m_beam);

    EXPECT_EQ(converter.dimension(), 2u);

    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::QYQZ), 0.0);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEFAULT), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::NBINS), 100.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEGREES), 5.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::QYQZ), m_kfy);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::QYQZ), m_kfz1 - m_kiz);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::QYQZ), m_kfz2 - m_kiz);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}

TEST_F(UnitConverterTest, SphericalConverterClone)
{
    SphericalConverter converter(m_detector, m_beam);
    std::unique_ptr<SphericalConverter> P_clone(converter.clone());

    EXPECT_EQ(P_clone->dimension(), 2u);

    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEFAULT), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::RADIANS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::DEGREES), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(0, AxesUnits::QYQZ), 0.0);
    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEFAULT), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::NBINS), 100.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::RADIANS), Units::deg2rad(5.0));
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::DEGREES), 5.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::QYQZ), m_kfy);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::QYQZ), m_kfz1 - m_kiz);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::QYQZ), m_kfz2 - m_kiz);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(P_clone->calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}

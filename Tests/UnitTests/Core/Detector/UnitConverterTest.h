#include "google_test.h"
#include "UnitConverters.h"
#include "Units.h"
#include "Vectors3D.h"

class UnitConverterTest : public ::testing::Test
{
public:
    UnitConverterTest();
    ~UnitConverterTest();
protected:
    double m_wavelength;
    double m_alpha_i;
    double m_phi_i;
};

UnitConverterTest::UnitConverterTest()
    : m_wavelength(1.0), m_alpha_i(-1.0*Units::deg), m_phi_i(0.0)
{}

UnitConverterTest::~UnitConverterTest() = default;

TEST_F(UnitConverterTest, SphericalConverter)
{
    SphericalConverter converter(100, 0.0, 5.0*Units::deg,
                                 70, -2.0*Units::deg, 1.5,
                                 m_wavelength, m_alpha_i, m_phi_i);
    auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
    double k_iz = k_i.z();
    double K = 2.0*M_PI/m_wavelength;
    double k_fy = K*std::sin(5.0*Units::deg);
    double k_fz1 = K*std::sin(-2.0*Units::deg);
    double k_fz2 = K*std::sin(1.5);

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
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::QYQZ), k_fy);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::QYQZ), k_fz1 - k_iz);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::QYQZ), k_fz2 - k_iz);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(converter.calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}

TEST_F(UnitConverterTest, SphericalConverterClone)
{
    SphericalConverter converter(100, 0.0, 5.0*Units::deg,
                                 70, -2.0*Units::deg, 1.5,
                                 1.0, -1.0*Units::deg, 0.0);
    std::unique_ptr<SphericalConverter> P_clone(converter.clone());
    auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
    double k_iz = k_i.z();
    double K = 2.0*M_PI/m_wavelength;
    double k_fy = K*std::sin(5.0*Units::deg);
    double k_fz1 = K*std::sin(-2.0*Units::deg);
    double k_fz2 = K*std::sin(1.5);

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
    EXPECT_DOUBLE_EQ(converter.calculateMax(0, AxesUnits::QYQZ), k_fy);
    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEFAULT), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::NBINS), 0.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::RADIANS), Units::deg2rad(-2.0));
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::DEGREES), -2.0);
    EXPECT_DOUBLE_EQ(converter.calculateMin(1, AxesUnits::QYQZ), k_fz1 - k_iz);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::MM), std::runtime_error);

    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEFAULT), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::NBINS), 70.0);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::RADIANS), 1.5);
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::DEGREES), Units::rad2deg(1.5));
    EXPECT_DOUBLE_EQ(converter.calculateMax(1, AxesUnits::QYQZ), k_fz2 - k_iz);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::MM), std::runtime_error);

    EXPECT_THROW(P_clone->calculateMin(2, AxesUnits::DEFAULT), std::runtime_error);
    EXPECT_THROW(P_clone->calculateMax(2, AxesUnits::DEFAULT), std::runtime_error);
}

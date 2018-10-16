#include "google_test.h"
#include "Beam.h"
#include "FixedBinAxis.h"
#include "MathConstants.h"
#include "PointwiseAxis.h"
#include "UnitConverter1D.h"
#include "Units.h"
#include "VariableBinAxis.h"

class UnitConverter1DTest : public ::testing::Test
{
public:
    UnitConverter1DTest();
    ~UnitConverter1DTest();

    double getQ(double angle) {return 4.0 * M_PI * std::sin(angle) / m_beam.getWavelength();}
protected:
    void checkMainFunctionality(const UnitConverter1D& test_object);
    const double m_alpha_start = 0.5; // first axis value in rads
    const double m_alpha_end = 1.0; // last axis value in rads
    const size_t m_nbins = 100;
    Beam m_beam;
    FixedBinAxis m_axis;
};

UnitConverter1DTest::UnitConverter1DTest()
    : m_axis("Angles", m_nbins, m_alpha_start, m_alpha_end) // angles in radians
{
    m_beam.setCentralK(1.0, 0.0, 0.0); // wavelength = 1.0 nm
}

UnitConverter1DTest::~UnitConverter1DTest() = default;

void UnitConverter1DTest::checkMainFunctionality(const UnitConverter1D& test_object)
{
    double expected_min = m_axis.getBinCenter(0);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::DEFAULT), Units::rad2deg(expected_min),
                Units::rad2deg(expected_min) * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::NBINS), 0.0, 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::RADIANS), expected_min,
                expected_min * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::DEGREES), Units::rad2deg(expected_min),
                Units::rad2deg(expected_min) * 1e-10);
    EXPECT_NEAR(test_object.calculateMin(0, AxesUnits::QSPACE), getQ(expected_min),
                getQ(expected_min) * 1e-10);

    double expected_max = m_axis.getBinCenter(m_nbins - 1);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::DEFAULT), Units::rad2deg(expected_max),
                Units::rad2deg(expected_max) * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::NBINS), static_cast<double>(m_nbins), 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::RADIANS), expected_max,
                expected_max * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::DEGREES), Units::rad2deg(expected_max),
                Units::rad2deg(expected_max) * 1e-10);
    EXPECT_NEAR(test_object.calculateMax(0, AxesUnits::QSPACE), getQ(expected_max),
                getQ(expected_max) * 1e-10);

    auto axis = test_object.createConvertedAxis(0, AxesUnits::DEFAULT);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis.get()));
    EXPECT_EQ(axis->size(), test_object.axisSize(0));
    EXPECT_EQ(axis->getName(), test_object.axisName(0));
    EXPECT_EQ(axis->getMin(), test_object.calculateMin(0, AxesUnits::DEFAULT));
    EXPECT_EQ(axis->getMax(), test_object.calculateMax(0, AxesUnits::DEFAULT));

    auto axis2 = test_object.createConvertedAxis(0, AxesUnits::QSPACE);
    EXPECT_TRUE(dynamic_cast<PointwiseAxis*>(axis2.get()));
    EXPECT_EQ(axis2->size(), test_object.axisSize(0));
    EXPECT_EQ(axis2->getName(), test_object.axisName(0, AxesUnits::QSPACE));
    EXPECT_EQ(axis2->getMin(), test_object.calculateMin(0, AxesUnits::QSPACE));
    EXPECT_EQ(axis2->getMax(), test_object.calculateMax(0, AxesUnits::QSPACE));

    auto axis3 = test_object.createConvertedAxis(0, AxesUnits::NBINS);
    EXPECT_TRUE(dynamic_cast<FixedBinAxis*>(axis3.get()));
    EXPECT_EQ(axis3->size(), test_object.axisSize(0));
    EXPECT_EQ(axis3->getName(), test_object.axisName(0, AxesUnits::NBINS));
    EXPECT_EQ(axis3->getMin(), test_object.calculateMin(0, AxesUnits::NBINS));
    EXPECT_EQ(axis3->getMax(), test_object.calculateMax(0, AxesUnits::NBINS));
}

TEST_F(UnitConverter1DTest, UnitConverter1D)
{
    UnitConverter1D converter(m_beam, m_axis);
    checkMainFunctionality(converter);
}

TEST_F(UnitConverter1DTest, UnitConverter1DExceptions)
{
    UnitConverter1D converter(m_beam, m_axis);

    EXPECT_THROW(converter.calculateMin(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMin(1, AxesUnits::RADIANS), std::runtime_error);

    EXPECT_THROW(converter.calculateMax(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.calculateMax(1, AxesUnits::RADIANS), std::runtime_error);

    EXPECT_THROW(converter.createConvertedAxis(0, AxesUnits::MM), std::runtime_error);
    EXPECT_THROW(converter.createConvertedAxis(1, AxesUnits::DEFAULT), std::runtime_error);

    FixedBinAxis axis("Angles", 100, 0.0, 2.0 * M_PI);
    EXPECT_THROW(UnitConverter1D converter2(m_beam, axis), std::runtime_error);
}

TEST_F(UnitConverter1DTest, UnitConverter1DClone)
{
    UnitConverter1D converter(m_beam, m_axis);
    std::unique_ptr<UnitConverter1D> converter_clone(converter.clone());
    checkMainFunctionality(*converter_clone);
}

TEST_F(UnitConverter1DTest, NonDefaultUnitsInInput)
{
    PointwiseAxis axis("x", std::vector<double>{0.0, 0.5, 1.0});

    EXPECT_THROW(UnitConverter1D(m_beam, axis, AxesUnits::NBINS),
                 std::runtime_error);

    UnitConverter1D converter(m_beam, axis, AxesUnits::DEGREES);
    auto axis_deg_output = converter.createConvertedAxis(0, AxesUnits::DEGREES);
    EXPECT_TRUE(axis.size() == axis_deg_output->size());
    EXPECT_DOUBLE_EQ(axis[0], (*axis_deg_output)[0]);
    EXPECT_DOUBLE_EQ(axis[1], (*axis_deg_output)[1]);
    EXPECT_DOUBLE_EQ(axis[2], (*axis_deg_output)[2]);

    auto values = axis.getBinCenters();
    std::for_each(values.begin(), values.end(), [this](double& value){value = getQ(value);});
    PointwiseAxis q_axis("q", values);
    UnitConverter1D converter2(m_beam, q_axis, AxesUnits::QSPACE);
    auto axis_rad_output = converter2.createConvertedAxis(0, AxesUnits::RADIANS);
    EXPECT_TRUE(axis.size() == axis_rad_output->size());
    EXPECT_DOUBLE_EQ(axis[0], (*axis_rad_output)[0]);
    EXPECT_DOUBLE_EQ(axis[1], (*axis_rad_output)[1]);
    EXPECT_DOUBLE_EQ(axis[2], (*axis_rad_output)[2]);
}

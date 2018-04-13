#include "google_test.h"
#include "BornAgainNamespace.h"
#include "FitObject.h"
#include "GISASSimulation.h"
#include "Units.h"

class FitObjectTest : public ::testing::Test
{
protected:
    ~FitObjectTest();
};

FitObjectTest::~FitObjectTest() = default;

TEST_F(FitObjectTest, StandardPair)
{
    const size_t nx(5), ny(4);
    const double xmin(-1.0*Units::deg), xmax(4.0*Units::deg);
    const double ymin(0.0*Units::deg), ymax(4.0*Units::deg);

    // creating simulation and real data
    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);

    OutputData<double> data;
    // data limits made intentionally arbitrary, they will be set as in simulation
    // on the way from SimulationResult
    const double data_xmin(-1.0*Units::deg), data_xmax(4.0*Units::deg);
    const double data_ymin(0.0*Units::deg), data_ymax(4.0*Units::deg);
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, nx, data_xmin, data_xmax));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, ny, data_ymin, data_ymax));
    double intensity(10.0);
    data.setAllTo(intensity);

    // creating fit object
    double weight(0.5);
    FitObject obj(simulation, data, weight);

    EXPECT_EQ(obj.weight(), weight);
    EXPECT_EQ(obj.numberOfFitElements(), size_t(nx * ny));

    // access to simulation result
    auto sim_result = obj.simulationResult();
    EXPECT_EQ(sim_result.size(), nx*ny);

    // access to experimental data
    auto exp_data = obj.experimentalData();
    EXPECT_EQ(exp_data.size(), nx*ny);

    std::unique_ptr<OutputData<double>> retrieved_exp(exp_data.data());
    EXPECT_EQ(retrieved_exp->getAxis(0).size(), nx);
    EXPECT_EQ(retrieved_exp->getAxis(1).size(), ny);
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(0).getMin(), Units::rad2deg(xmin));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(0).getMax(), Units::rad2deg(xmax));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(1).getMin(), Units::rad2deg(ymin));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(1).getMax(), Units::rad2deg(xmax));
    EXPECT_EQ(retrieved_exp->totalSum(), intensity * nx * ny);
}

//! Test of the case when simulation has ROI.

TEST_F(FitObjectTest, RoiPair)
{
    const size_t nx(5), ny(4);
    const double xmin(-1.0*Units::deg), xmax(4.0*Units::deg);
    const double ymin(0.0*Units::deg), ymax(4.0*Units::deg);

    const double roi_xmin(0.1*Units::deg), roi_xmax(2.9*Units::deg);
    const double roi_ymin(1.1*Units::deg), roi_ymax(3.9*Units::deg);
    const size_t expected_roi_nx(3), expected_roi_ny(3);

    const double expected_roi_xmin(0.0*Units::deg), expected_roi_xmax(3.0*Units::deg);
    const double expected_roi_ymin(1.0*Units::deg), expected_roi_ymax(4.0*Units::deg);

    // creating simulation and real data, setting ROI
    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);
    simulation.setRegionOfInterest(roi_xmin, roi_ymin, roi_xmax, roi_ymax);

    OutputData<double> data;
    // data limits made intentionally arbitrary, they will be set as in simulation
    // on the way from SimulationResult
    const double data_xmin(-1.0*Units::deg), data_xmax(4.0*Units::deg);
    const double data_ymin(0.0*Units::deg), data_ymax(4.0*Units::deg);
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, nx, data_xmin, data_xmax));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, ny, data_ymin, data_ymax));
    for (size_t i=0; i<data.getAllocatedSize(); ++i) {
        data[i] = static_cast<double>(i);
    }

    // creating fit object
    double weight(0.5);
    FitObject obj(simulation, data, weight);

    EXPECT_EQ(obj.weight(), weight);
    EXPECT_EQ(obj.numberOfFitElements(), expected_roi_nx*expected_roi_ny);

    // access to simulation result
    auto sim_result = obj.simulationResult();
    EXPECT_EQ(sim_result.size(), expected_roi_nx*expected_roi_ny);

    // access to experimental data
    auto exp_data = obj.experimentalData();
    EXPECT_EQ(exp_data.size(), expected_roi_nx*expected_roi_ny);

    std::unique_ptr<OutputData<double>> retrieved_exp(exp_data.data());
    EXPECT_EQ(retrieved_exp->getAxis(0).size(), expected_roi_nx);
    EXPECT_EQ(retrieved_exp->getAxis(1).size(), expected_roi_nx);
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(0).getMin(), Units::rad2deg(expected_roi_xmin));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(0).getMax(), Units::rad2deg(expected_roi_xmax));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(1).getMin(), Units::rad2deg(expected_roi_ymin));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(1).getMax(), Units::rad2deg(expected_roi_ymax));

    std::vector<double> expected_amp = {5.0, 6.0, 7.0, 9.0, 10.0, 11.0, 13.0, 14.0, 15.0};
    EXPECT_EQ(retrieved_exp->getRawDataVector(), expected_amp);
}

//! Testing FitObject when real data already clipped to ROI.

TEST_F(FitObjectTest, WhenExpDataIsClipped)
{
    const size_t nx(5), ny(4);
    const double xmin(-1.0*Units::deg), xmax(4.0*Units::deg);
    const double ymin(0.0*Units::deg), ymax(4.0*Units::deg);

    const double roi_xmin(0.1*Units::deg), roi_xmax(2.9*Units::deg);
    const double roi_ymin(1.1*Units::deg), roi_ymax(3.9*Units::deg);

    const double expected_roi_xmin(0.0*Units::deg), expected_roi_xmax(3.0*Units::deg);
    const double expected_roi_ymin(1.0*Units::deg), expected_roi_ymax(4.0*Units::deg);

    // creating simulation
    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);
    simulation.setRegionOfInterest(roi_xmin, roi_ymin, roi_xmax, roi_ymax);

    // creating cropped experimental data
    OutputData<double> data;
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, 3, 42.0, 42.1));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, 3, 42.2, 42.3));

    for (size_t i=0; i<data.getAllocatedSize(); ++i) {
        data[i] = static_cast<double>(i);
    }
    std::vector<double> expectedData = data.getRawDataVector();

    FitObject obj(simulation, data);

    // access to experimental data
    std::unique_ptr<OutputData<double>> retrieved_exp(obj.experimentalData().data());

    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(0).getMin(), Units::rad2deg(expected_roi_xmin));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(0).getMax(), Units::rad2deg(expected_roi_xmax));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(1).getMin(), Units::rad2deg(expected_roi_ymin));
    EXPECT_DOUBLE_EQ(retrieved_exp->getAxis(1).getMax(), Units::rad2deg(expected_roi_ymax));
    EXPECT_EQ(retrieved_exp->getRawDataVector(), expectedData);
}

// Attempt to assign experimental which doesn't fit neither detector or ROI.

TEST_F(FitObjectTest, AssignWrinExpData)
{
    const size_t nx(5), ny(4);
    const double xmin(-1.0*Units::deg), xmax(4.0*Units::deg);
    const double ymin(0.0*Units::deg), ymax(4.0*Units::deg);

    const double roi_xmin(0.1*Units::deg), roi_xmax(2.9*Units::deg);
    const double roi_ymin(1.1*Units::deg), roi_ymax(3.9*Units::deg);

    OutputData<double> data;
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, 4, 42.0, 42.1));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, 3, 42.2, 42.3));

    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);
    simulation.setRegionOfInterest(roi_xmin, roi_ymin, roi_xmax, roi_ymax);

    EXPECT_THROW(FitObject(simulation, data), std::runtime_error);
}

#include "google_test.h"
#include "SimulationResult.h"
#include "GISASSimulation.h"
#include "OutputData.h"

class SimulationResultTest : public ::testing::Test
{
public:
    ~SimulationResultTest();
};

SimulationResultTest::~SimulationResultTest() = default;

TEST_F(SimulationResultTest, initialState)
{
    SimulationResult simres;

    SimulationResult other;
    EXPECT_THROW(other = simres, std::runtime_error);

    EXPECT_THROW(SimulationResult another(other), std::runtime_error);
}

TEST_F(SimulationResultTest, accessToEmptySimulation)
{
    const int nx(5), ny(4);

    GISASSimulation simulation;
    EXPECT_THROW(simulation.result(), std::runtime_error);

    simulation.setDetectorParameters(nx, -1.0, 4.0, ny, 0.0, 4.0);

    // With detector set the data has correct size.
    auto result = simulation.result();
    EXPECT_EQ(result.size(), size_t(nx*ny));

    // OutputData has correct size and amplitudes
    std::unique_ptr<OutputData<double>> data(result.data());
    EXPECT_EQ(data->getAllocatedSize(), size_t(nx*ny));
    EXPECT_EQ(data->totalSum(), 0.0);
}

TEST_F(SimulationResultTest, accessToEmptyRoiSimulation)
{
    const int nx(5), ny(4);

    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, -1.0, 4.0, ny, 0.0, 4.0);
    simulation.setRegionOfInterest(0.1, 1.1, 2.9, 3.9);

    // With detector and roi set the data has correct size.
    auto result = simulation.result();
    EXPECT_EQ(result.size(), 9u);

    // OutputData has correct size and amplitudes
    std::unique_ptr<OutputData<double>> data(result.data());
    EXPECT_EQ(data->getAllocatedSize(), 9u);
    EXPECT_EQ(data->totalSum(), 0.0);
}

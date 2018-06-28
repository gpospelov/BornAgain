#include "google_test.h"
#include "SimDataPair.h"
#include "Parameters.h"
#include "GISASSimulation.h"
#include "Units.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "BornAgainNamespace.h"
#include "MaterialFactoryFuncs.h"

class SimDataPairTest : public ::testing::Test
{
public:
    SimDataPairTest() : m_builder_calls(0) {}
    ~SimDataPairTest();

protected:
    const size_t m_nx = 5;
    const size_t m_ny = 5;
    const double m_xmin = -1.0*Units::deg;
    const double m_xmax = 4.0*Units::deg;
    const double m_ymin = 0.0*Units::deg;
    const double m_ymax = 4.0*Units::deg;

    size_t m_builder_calls;

    std::unique_ptr<Simulation> createSimulation(const Fit::Parameters&) {
        MultiLayer multilayer;
        auto material = HomogeneousMaterial("Shell", 0.0, 0.0);
        multilayer.addLayer(Layer(material));
        multilayer.addLayer(Layer(material));

        std::unique_ptr<GISASSimulation> result(new GISASSimulation(multilayer));
        result->setDetectorParameters(m_nx, m_xmin, m_xmax, m_ny, m_ymin, m_ymax);

        m_builder_calls++;
        return result;
    }

    std::unique_ptr<OutputData<double>> createData(double value) {
        std::unique_ptr<OutputData<double>> result(new OutputData<double>);
        result->addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, m_nx, m_xmin, m_xmax));
        result->addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, m_ny, m_ymin, m_ymax));
        result->setAllTo(value);
        return result;
    }
};

SimDataPairTest::~SimDataPairTest() = default;

TEST_F(SimDataPairTest, standardPair)
{
    simulation_builder_t builder = [=](const Fit::Parameters &pars){
        return this->createSimulation(pars);
    };

    const double exp_value(10.0);
    const double dataset_weight(0.5);
    auto data = createData(exp_value);

    SimDataPair obj(builder, *data, dataset_weight);

    // default state, no simulation has been called yet
    EXPECT_EQ(obj.numberOfFitElements(), 0u);
    EXPECT_EQ(obj.weight(), dataset_weight);
    EXPECT_TRUE(obj.simulation_array().empty());
    EXPECT_TRUE(obj.experimental_array().empty());
    EXPECT_THROW(obj.simulationResult().size(), std::runtime_error);
    EXPECT_THROW(obj.experimentalData().size(), std::runtime_error);

    // calling builder once
    Fit::Parameters params;
    EXPECT_EQ(m_builder_calls, 0u);
    obj.runSimulation(params);
    EXPECT_EQ(m_builder_calls, 1u);

    // checking simulated and experimental data
    const size_t expected_size = m_nx*m_ny;
    EXPECT_EQ(obj.numberOfFitElements(), expected_size);
    EXPECT_EQ(obj.simulationResult().size(), expected_size);
    EXPECT_EQ(obj.experimentalData().size(), expected_size);

    // checking arrays
    auto array = obj.simulation_array();
    EXPECT_EQ(array.size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), 0.0);
    array = obj.experimental_array();
    EXPECT_EQ(obj.experimental_array().size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), expected_size*exp_value);

    // calling builder second time
    obj.runSimulation(params);
    EXPECT_EQ(m_builder_calls, 2u);

    // checking arrays
    array = obj.simulation_array();
    EXPECT_EQ(array.size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), 0.0);
    array = obj.experimental_array();
    EXPECT_EQ(obj.experimental_array().size(), expected_size);
    EXPECT_DOUBLE_EQ(std::accumulate(array.begin(), array.end(), 0), expected_size*exp_value);
}


#include "google_test.h"
#include "Distributions.h"
#include "Exceptions.h"
#include "FixedBinAxis.h"
#include "Histogram1D.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "ParameterPattern.h"
#include "RealParameter.h"
#include "SpecularSimulation.h"
#include "Units.h"
#include "VariableBinAxis.h"
#include <iostream>

class SpecularSimulationTest : public ::testing::Test
{
protected:
    SpecularSimulationTest();
    ~SpecularSimulationTest();

    std::unique_ptr<SpecularSimulation> defaultSimulation();
    void checkBeamState(const SpecularSimulation& sim);

    MultiLayer multilayer;
};

SpecularSimulationTest::SpecularSimulationTest()
{
    Material mat0 = HomogeneousMaterial("ambience", 0.0, 0.0);
    Material mat1 = HomogeneousMaterial("PartA", 5e-6, 0.0);
    Material mat2 = HomogeneousMaterial("substrate", 15e-6, 0.0);

    Layer layer0(mat0);
    Layer layer1(mat1, 10 * Units::nanometer);
    Layer layer2(mat2);

    multilayer.addLayer(layer0);
    multilayer.addLayer(layer1);
    multilayer.addLayer(layer2);
}

SpecularSimulationTest::~SpecularSimulationTest() = default;

TEST_F(SpecularSimulationTest, InitialState)
{
    SpecularSimulation sim;
    ASSERT_THROW(sim.runSimulation(), std::runtime_error);
    ASSERT_THROW(sim.getAlphaAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, sim.sample());
    ASSERT_THROW(sim.result(), std::runtime_error);
}

std::unique_ptr<SpecularSimulation> SpecularSimulationTest::defaultSimulation()
{
    auto result = std::make_unique<SpecularSimulation>();
    result->setBeamParameters(1.0, 10, 0.0 * Units::degree, 2.0 * Units::degree);
    result->setSample(multilayer);
    return result;
}

void SpecularSimulationTest::checkBeamState(const SpecularSimulation& sim)
{
    const auto* inclination = sim.getInstrument().getBeam().parameter(BornAgain::Inclination);
    const auto test_limits = RealLimits::limited(-M_PI_2, M_PI_2);
    EXPECT_EQ(test_limits, inclination->limits());
    EXPECT_EQ(0.0, inclination->value());
}

TEST_F(SpecularSimulationTest, CloneOfEmpty)
{
    SpecularSimulation sim;

    std::unique_ptr<SpecularSimulation> clone(sim.clone());
    ASSERT_THROW(clone->runSimulation(), std::runtime_error);
    ASSERT_THROW(clone->getAlphaAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, clone->sample());
    ASSERT_THROW(clone->result(), std::runtime_error);

    checkBeamState(sim);
    checkBeamState(*clone);
}

TEST_F(SpecularSimulationTest, SetBeamParameters)
{
    SpecularSimulation sim;

    VariableBinAxis axis("axis", 2, std::vector<double>{1.0, 2.0, 3.0});
    sim.setBeamParameters(1.0, axis);

    const auto& beam = sim.getInstrument().getBeam();

    EXPECT_EQ(2u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(3.0, sim.getAlphaAxis()->getMax());
    EXPECT_EQ(1.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    sim.setBeamIntensity(2.0);
    EXPECT_EQ(2.0, beam.getIntensity());

    sim.setBeamParameters(1.0, 10, 1.0 * Units::degree, 10.0 * Units::degree);
    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.getAlphaAxis()->getMax());
    EXPECT_EQ(2.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    EXPECT_THROW(sim.setBeamParameters(1.0, 10, -2.0, 3.0),
                 std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(1.0, 10, 2.0, 1.0),
                 std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(1.0, 0, 1.0, 2.0),
                 std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(-1.0, 1, 1.0, 2.0),
                 std::runtime_error);

    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.getAlphaAxis()->getMax());
    EXPECT_EQ(2.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    sim.setInstrument(Instrument());

    checkBeamState(sim);
}

TEST_F(SpecularSimulationTest, ConstructSimulation)
{
    auto sim = defaultSimulation();

    EXPECT_EQ(3u, sim->sample()->numberOfLayers());

    ASSERT_THROW(sim->result(), std::runtime_error);

    sim->runSimulation();
    auto sim_result = sim->result();

    const std::unique_ptr<Histogram1D> reflectivity(sim_result.histogram1d(AxesUnits::RADIANS));
    EXPECT_EQ(10u, reflectivity->getTotalNumberOfBins());
    EXPECT_EQ(1u, reflectivity->getRank());
    EXPECT_EQ(0.0, reflectivity->getXaxis().getMin());
    EXPECT_EQ(2.0 * Units::degree, reflectivity->getXaxis().getMax());

    const std::unique_ptr<OutputData<double>> output(sim_result.data(AxesUnits::RADIANS));
    EXPECT_EQ(reflectivity->getTotalNumberOfBins(), output->getAllocatedSize());
    EXPECT_EQ(reflectivity->getRank(), output->getRank());
    EXPECT_EQ(reflectivity->getXaxis().getMin(), output->getAxis(0).getMin());
    EXPECT_EQ(reflectivity->getXaxis().getMax(), output->getAxis(0).getMax());
    EXPECT_DOUBLE_EQ(reflectivity->getBinValues()[5], (*output)[5]);

    checkBeamState(*sim);
}

TEST_F(SpecularSimulationTest, SimulationClone)
{
    auto sim = defaultSimulation();

    std::unique_ptr<SpecularSimulation> clone(sim->clone());

    EXPECT_EQ(3u, clone->sample()->numberOfLayers());

    ASSERT_THROW(clone->result(), std::runtime_error);

    checkBeamState(*clone);

    sim->runSimulation();

    std::unique_ptr<SpecularSimulation> clone2(sim->clone());
    auto clone_result = clone2->result();

    std::unique_ptr<Histogram1D> output(clone_result.histogram1d());
    EXPECT_EQ(10u, output->getTotalNumberOfBins());

    const std::unique_ptr<OutputData<double>> output_data(clone_result.data());
    EXPECT_EQ(10u, output_data->getAllocatedSize());

    checkBeamState(*clone2);
}

TEST_F(SpecularSimulationTest, AddingBeamDistributions)
{
    auto sim = defaultSimulation();
    DistributionGaussian distribution(1.0, 2.0);

    ParameterPattern wl_pattern;
    wl_pattern.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
    ParameterPattern incl_ang_pattern;
    incl_ang_pattern.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
    ParameterPattern beam_pattern;
    beam_pattern.beginsWith("*").add(BornAgain::BeamType).add("*");

    EXPECT_THROW(sim->addParameterDistribution(incl_ang_pattern.toStdString(), distribution, 5),
                 std::runtime_error);
    EXPECT_THROW(sim->addParameterDistribution(beam_pattern.toStdString(), distribution, 5),
                 std::runtime_error);
    EXPECT_NO_THROW(sim->addParameterDistribution(wl_pattern.toStdString(), distribution, 5));

    checkBeamState(*sim);

    DistributionGaussian distribution2(0.0, 2.0);
    EXPECT_NO_THROW(
        sim->addParameterDistribution(incl_ang_pattern.toStdString(), distribution2, 5));

    checkBeamState(*sim);
}

TEST_F(SpecularSimulationTest, OutOfRangeAngles)
{
    auto sim = defaultSimulation();
    auto& beam = sim->getInstrument().getBeam();
    beam.parameter(BornAgain::Inclination)->setValue(-0.2 * Units::deg);

    sim->runSimulation();
    auto sim_result = sim->result();

    std::unique_ptr<Histogram1D> result(sim_result.histogram1d());
    EXPECT_EQ(0.0, result->getBinContent(0));
    EXPECT_NE(0.0, result->getBinContent(1));
}

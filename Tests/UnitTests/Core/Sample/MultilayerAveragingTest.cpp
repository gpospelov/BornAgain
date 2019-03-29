#include "FormFactorCylinder.h"
#include "IComputationUtils.h"
#include "google_test.h"
#include "InterferenceFunction2DLattice.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "SimulationOptions.h"

class MultilayerAveragingTest : public ::testing::Test
{
protected:
    MultilayerAveragingTest()
        : vacuum(HomogeneousMaterial("vac", 0.0, 0.0)),
          stone(HomogeneousMaterial("stone", 4e-4, 8e-7))
    {
    }

    ~MultilayerAveragingTest() override;

    const Material vacuum, stone;
};

MultilayerAveragingTest::~MultilayerAveragingTest() = default;

TEST_F(MultilayerAveragingTest, AverageMultilayer)
{
    // particles
    FormFactorCylinder cylinder_ff(1.0, 3.0);
    Particle particle(stone, cylinder_ff);

    // interferences
    InterferenceFunction2DLattice interf_1(10.0, 10.0, 120.0, 0.0);
    InterferenceFunction2DLattice interf_2(10.0, 10.0, 120.0, 0.0);

    // layouts
    ParticleLayout layout_1;
    layout_1.addParticle(particle);
    layout_1.setInterferenceFunction(interf_1);
    EXPECT_DOUBLE_EQ(layout_1.weight(), 1.0);

    ParticleLayout layout_2;
    layout_2.addParticle(particle);
    layout_2.setInterferenceFunction(interf_2);
    EXPECT_DOUBLE_EQ(layout_2.weight(), 1.0);

    std::unique_ptr<MultiLayer> m_layer_1_avr;
    {
        Layer layer_1(vacuum);
        Layer layer_2(stone);

        layer_1.addLayout(layout_1);

        MultiLayer m_layer;
        m_layer.addLayer(layer_1);
        m_layer.addLayer(layer_2);

        SimulationOptions opts;
        opts.setUseAvgMaterials(true);

        m_layer_1_avr =
            IComputationUtils::CreateAveragedMultilayer(*m_layer.cloneSliced(true), opts);
    }

    layout_1.setWeight(0.5);
    EXPECT_DOUBLE_EQ(layout_1.weight(), 0.5);
    layout_2.setWeight(0.5);
    EXPECT_DOUBLE_EQ(layout_2.weight(), 0.5);

    std::unique_ptr<MultiLayer> m_layer_2_avr;
    {
        Layer layer_1(vacuum);
        Layer layer_2(stone);

        layer_1.addLayout(layout_1);
        layer_1.addLayout(layout_2);

        MultiLayer m_layer;
        m_layer.addLayer(layer_1);
        m_layer.addLayer(layer_2);

        SimulationOptions opts;
        opts.setUseAvgMaterials(true);

        m_layer_2_avr =
            IComputationUtils::CreateAveragedMultilayer(*m_layer.cloneSliced(true), opts);
    }

    EXPECT_EQ(m_layer_1_avr->numberOfLayers(), m_layer_2_avr->numberOfLayers());

    for (size_t i = 0; i < m_layer_1_avr->numberOfLayers(); ++i)
    {
        auto mat_1 = m_layer_1_avr->layer(i)->material()->materialData();
        auto mat_2 = m_layer_2_avr->layer(i)->material()->materialData();
        EXPECT_DOUBLE_EQ(mat_1.real(), mat_2.real());
        EXPECT_DOUBLE_EQ(mat_1.imag(), mat_2.imag());
    }
}

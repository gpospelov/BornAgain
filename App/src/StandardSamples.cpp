// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/StandardSamples.cpp
//! @brief     Implements class StandardSamples.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardSamples.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "Units.h"
#include "Particle.h"
#include "FormFactors.h"
#include "ParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Crystal.h"
#include "MesoCrystal.h"
#include "InterferenceFunctions.h"
#include "StochasticGaussian.h"

#include "Numeric.h"
#include "MathFunctions.h"
#include "ParticleBuilder.h"
#include "StochasticSampledParameter.h"
#include "ParticleCoreShell.h"

#include "Particle.h"
#include "PositionParticleInfo.h"

//! 10 nm of ambience on top of substrate.

ISample *StandardSamples::AirOnSubstrate()
{
    const IMaterial *mAmbience =
        MaterialManager::getHomogeneousMaterial
        ("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate =
        MaterialManager::getHomogeneousMaterial
        ("substrate", complex_t(1.0-15e-6, 0) );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);
    mySample->addLayer(lAmbience);

    Layer lAir;
    lAir.setMaterial(mAmbience, 10*Units::nanometer);
    mySample->addLayer(lAir);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);
    mySample->addLayer(lSubstrate);

    return mySample;
}

//! 10 nm of substrate on top of substrate.

ISample *StandardSamples::SubstrateOnSubstrate()
{
    const IMaterial *mAmbience =
        MaterialManager::getHomogeneousMaterial
        ("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate =
        MaterialManager::getHomogeneousMaterial
        ("substrate", complex_t(1.0-15e-6, 0) );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);
    mySample->addLayer(lAmbience);

    Layer likeSubstrate;
    likeSubstrate.setMaterial(mSubstrate, 10*Units::nanometer);
    mySample->addLayer(likeSubstrate);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);
    mySample->addLayer(lSubstrate);

    return mySample;
}

//! Simple multilayer.

ISample *StandardSamples::SimpleMultilayer()
{
    const IMaterial *mAmbience =
        MaterialManager::getHomogeneousMaterial("ambience",
                                                complex_t(1.0, 0.0) );
    const IMaterial *mAg1 =
        MaterialManager::getHomogeneousMaterial("ag1",
                                                complex_t(1.0-5e-6, 0.0) );
    const IMaterial *mCr1 =
        MaterialManager::getHomogeneousMaterial("cr1",
                                                complex_t(1.0-10e-6, 0.0) );
    const IMaterial *mSubstrate =
        MaterialManager::getHomogeneousMaterial("substrate2",
                                                complex_t(1.0-15e-6, 0.0) );

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);

    Layer lAg1;
    lAg1.setMaterial(mAg1, 150.0*Units::nanometer);

    Layer lCr1;
    lCr1.setMaterial(mCr1, 120.0*Units::nanometer);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate, 0);

    MultiLayer *mySample = new MultiLayer;

    // adding layers
    mySample->addLayer(lAmbience);

    LayerRoughness roughness;
    roughness.setSigma(0.0*Units::nanometer);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(5000*Units::nanometer);

    const unsigned nrepetitions = 2;
    for(unsigned i=0; i<nrepetitions; ++i) {
        mySample->addLayerWithTopRoughness(lAg1, roughness);
        mySample->addLayerWithTopRoughness(lCr1, roughness);
    }
    mySample->addLayerWithTopRoughness(lSubstrate, roughness);
    return mySample;
}

//! Multilayer offspecular testcase

ISample *StandardSamples::MultilayerOffspecTestcase1a()
{
    const IMaterial *mAmbience =
        MaterialManager::getHomogeneousMaterial
        ("ambience", complex_t(1.0, 0.0) );
    const IMaterial *mPartA =
        MaterialManager::getHomogeneousMaterial
        ("PartA", complex_t(1.0-5e-6, 0.0) );
    const IMaterial *mPartB =
        MaterialManager::getHomogeneousMaterial
        ("PartB", complex_t(1.0-10e-6, 0.0) );
    const IMaterial *mSubstrate =
        MaterialManager::getHomogeneousMaterial
        ("substrate", complex_t(1.0-15e-6, 0.0) );

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);

    Layer lPartA;
    lPartA.setMaterial(mPartA, 5.0*Units::nanometer);

    Layer lPartB;
    lPartB.setMaterial(mPartB, 10.0*Units::nanometer);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate, 0);

    LayerRoughness roughness;
    roughness.setSigma(1.0*Units::nanometer);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(500*Units::nanometer);

    MultiLayer *mySample = new MultiLayer;

    // adding layers
    mySample->addLayer(lAmbience);

    const unsigned nrepetitions = 10;
    for(unsigned i=0; i<nrepetitions; ++i) {
        mySample->addLayerWithTopRoughness(lPartA, roughness);
        mySample->addLayerWithTopRoughness(lPartB, roughness);
    }

    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

    //mySample->setCrossCorrLength(1e-10);

    return mySample;
}

//! Multilayer offspecular tescase.

ISample *StandardSamples::MultilayerOffspecTestcase1b()
{
    MultiLayer *myOrigSample =
        dynamic_cast<MultiLayer *>
        (StandardSamples::MultilayerOffspecTestcase1a());
    MultiLayer *mySample = myOrigSample->clone();
    delete myOrigSample;
    mySample->setCrossCorrLength(1e10);
    return mySample;
}

//! Multilayer offspecular testcase.

ISample *StandardSamples::MultilayerOffspecTestcase2a()
{
    const IMaterial *mAmbience =
        MaterialManager::getHomogeneousMaterial
        ("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate =
        MaterialManager::getHomogeneousMaterial
        ("substrate", complex_t(1.0-15e-6, 0) );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);
    mySample->addLayer(lAmbience);

    LayerRoughness roughness;
    roughness.setSigma(0.5*Units::nanometer);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(500.*Units::nanometer);

    Layer lAir;
    lAir.setMaterial(mAmbience, 10*Units::nanometer);
    mySample->addLayerWithTopRoughness(lAir, roughness);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);
    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

    return mySample;
}

//! Multilayer offspecular testcase.

ISample *StandardSamples::MultilayerOffspecTestcase2b()
{
    MultiLayer *myOrigSample =
        dynamic_cast<MultiLayer *>
        (StandardSamples::MultilayerOffspecTestcase2a());
    MultiLayer *mySample = myOrigSample->clone();
    delete myOrigSample;
    // changing thickness of middle layer
    mySample->setLayerThickness(1, 0.01*Units::nanometer);
    return mySample;
}


//! IsGISAXS ex#15: Size-spacing correlation approximation.

//ISample *StandardSamples::IsGISAXS15_SSCA()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    InterferenceFunction1DParaCrystal *p_interference_function =
//        new InterferenceFunction1DParaCrystal
//        (15.0*Units::nanometer,5*Units::nanometer, 1e3*Units::nanometer);
//    p_interference_function->setKappa(4.02698);
//    ParticleDecoration particle_decoration;
//    Particle particle_prototype(particle_material, new FormFactorCylinder
//                                (5.0*Units::nanometer, 5.0*Units::nanometer));
//    StochasticDoubleGaussian sg(5.0*Units::nanometer, 1.25*Units::nanometer);
//    StochasticSampledParameter stochastic_radius(sg,30, 2);
//    ParticleBuilder particle_builder;
//    particle_builder.setPrototype
//        (particle_prototype, "/Particle/FormFactorCylinder/radius",
//         stochastic_radius);
//    particle_builder.plantParticles(particle_decoration);

//    // Set height of each particle to its radius (H/R fixed)
//    ParameterPool *p_parameters = particle_decoration.createParameterTree();
//    int nbr_replacements =
//        p_parameters->fixRatioBetweenParameters("height", "radius", 1.0);
//    std::cout << "Number of replacements: " << nbr_replacements << std::endl;

//    particle_decoration.addInterferenceFunction(p_interference_function);

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    return p_multi_layer;
//}

////! First mesocrystal test.

ISample *StandardSamples::MesoCrystal1()
{
    // create mesocrystal
    double nanoparticle_radius = 6.1*Units::nanometer;
    Lattice lat = Lattice::createTrigonalLattice(
        nanoparticle_radius*2.0, nanoparticle_radius*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    complex_t n_particle(1.0-1.5e-5, 1.3e-6);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

    Particle particle(particle_material,
                      new FormFactorFullSphere(nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    Crystal npc(basis, lat);

    MesoCrystal meso(npc.clone(), new FormFactorCylinder
                     (0.2*Units::micrometer, 300*Units::nanometer));
    MesoCrystal meso2(npc.clone(), new FormFactorPyramid
                      (0.2*Units::micrometer,
                       300*Units::nanometer,
                       84*Units::degree));
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-3.5e-6, 7.8e-8);

    const IMaterial *p_air_material =
        MaterialManager::getHomogeneousMaterial("Air2", n_air);
    const IMaterial *p_substrate_material =
        MaterialManager::getHomogeneousMaterial("Substrate2", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_function =
        new InterferenceFunction1DParaCrystal
        (800.0*Units::nanometer, 50*Units::nanometer, 1e7*Units::nanometer);
    ParticleDecoration particle_decoration;
    particle_decoration.addParticle(meso.clone(), 0.0, 0.5);
    particle_decoration.addParticle(meso2.clone(), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setDecoration(particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;

}

////! Second mesocrystal test: Mesocrystal from TestMesocrystal to play with.

//ISample *StandardSamples::MesoCrystal2()
//{
//    double meso_radius = 300*Units::nanometer;
//    double surface_filling_ratio = 0.25;
//    double surface_density = surface_filling_ratio/M_PI/meso_radius/meso_radius;
//    complex_t n_particle(1.0-1.55e-5, 1.37e-6);
//    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
//    complex_t n_avg = std::sqrt(surface_filling_ratio*avg_n_squared_meso +
//                                1.0 - surface_filling_ratio);
//    complex_t n_particle_adapted =
//        std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);

//    const IMaterial *particle_adapted_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle_adapted);


//    FormFactorCylinder ff_meso(0.2*Units::micrometer, meso_radius);

//    // Create multilayer
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-7.57e-6, 1.73e-7);

//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_average_layer_material =
//        MaterialManager::getHomogeneousMaterial("Averagelayer", n_avg);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer avg_layer;
//    avg_layer.setMaterial(p_average_layer_material);
//    avg_layer.setThickness(0.2*Units::micrometer);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    IInterferenceFunction *p_interference_function =
//        new InterferenceFunctionNone();
//    ParticleDecoration particle_decoration;
//    double nanoparticle_radius = 5.4*Units::nanometer;
//    const IFormFactor* p_meso_form_factor =& ff_meso;
//    Lattice lat = Lattice::createTrigonalLattice
//        (nanoparticle_radius*2.0, nanoparticle_radius*2.0*2.3);
//    kvector_t bas_a = lat.getBasisVectorA();
//    kvector_t bas_b = lat.getBasisVectorB();
//    kvector_t bas_c = lat.getBasisVectorC();
//    Particle particle(particle_adapted_material,
//                      new FormFactorFullSphere(nanoparticle_radius));
//    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
//    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
//    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
//    std::vector<kvector_t> pos_vector;
//    pos_vector.push_back(position_0);
//    pos_vector.push_back(position_1);
//    pos_vector.push_back(position_2);
//    LatticeBasis basis(particle, pos_vector);
//    Crystal npc(basis, lat);
//    MesoCrystal *meso_crystal =
//        new MesoCrystal(npc.clone(), p_meso_form_factor->clone());
//    particle_decoration.addParticle(meso_crystal, 0.2*Units::micrometer);
//    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
//    particle_decoration.addInterferenceFunction(p_interference_function);

//    avg_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(avg_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;

//}

//! Functional test: Formfactor of a box.

//ISample *StandardSamples::FormFactor_Box()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorBox(5*Units::nanometer,
//                                        5*Units::nanometer,
//                                        5*Units::nanometer)));
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a cone.

//ISample *StandardSamples::FormFactor_Cone()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorCone(5*Units::nanometer,
//                                         5*Units::nanometer,
//                                         Units::deg2rad(54.73 ))));
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a sphere.

//ISample *StandardSamples::FormFactor_Sphere()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorSphere(5*Units::nanometer,
//                                           5*Units::nanometer)));
//    particle_decoration.addInterferenceFunction
//(new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

// Functional test: Formfactor of an ellipsoidal cylinder.

//ISample *StandardSamples::FormFactor_EllipsoidalCylinder()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorEllipsoidalCylinder(5*Units::nanometer,
//                                              5*Units::nanometer,
//                                              5*Units::nanometer)));
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a full spheroid.

//ISample *StandardSamples::FormFactor_FullSpheroid()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-5, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorFullSpheroid(5*Units::nanometer,
//                                                 7*Units::nanometer )));
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a hemi spheroid.

//ISample *StandardSamples::FormFactor_HemiEllipsoid()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-7, 2e-8);
//    complex_t n_particle(1.0-6e-5, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorHemiEllipsoid(5*Units::nanometer,
//                                                 4*Units::nanometer,
//                                                 2*Units::nanometer)));
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a parallelepiped.

//ISample *StandardSamples::FormFactor_Parallelpiped()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_particle_shell(1.0-1e-4, 2e-8);
//    complex_t n_particle_core(1.0-6e-5, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air11", n_air);

//    const IMaterial *shell_material =
//            MaterialManager::getHomogeneousMaterial("Shell", n_particle_shell);
//    const IMaterial *core_material =
//            MaterialManager::getHomogeneousMaterial("Core", n_particle_core);

//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Particle shell_particle(shell_material,
//                            new FormFactorParallelepiped(8*Units::nanometer,
//                                                         8*Units::nanometer));
//    Particle core_particle(core_material,
//                           new FormFactorParallelepiped(7*Units::nanometer,
//                                                        6*Units::nanometer));
//    kvector_t core_position(0.0, 0.0, 0.0);
//    ParticleCoreShell particle(shell_particle, core_particle, core_position);
//    ParticleDecoration particle_decoration(particle.clone());
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a cylinder.

//ISample *StandardSamples::FormFactor_Cylinder()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_particle_shell(1.0-1e-4, 2e-8);
//    complex_t n_particle_core(1.0-6e-5, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air11", n_air);
//    const IMaterial *shell_material =
//            MaterialManager::getHomogeneousMaterial("Shell", n_particle_shell);
//    const IMaterial *core_material =
//            MaterialManager::getHomogeneousMaterial("Core", n_particle_core);

//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Particle shell_particle(shell_material,
//                            new FormFactorCylinder(8*Units::nanometer,
//                                                   8*Units::nanometer));
//    Particle core_particle(core_material,
//                           new FormFactorCylinder(7*Units::nanometer,
//                                                  6*Units::nanometer));
//    kvector_t core_position(0.0, 0.0, 0.0);
//    ParticleCoreShell particle(shell_particle, core_particle, core_position);
//    ParticleDecoration particle_decoration(particle.clone());
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);


//    p_multi_layer->addLayer(air_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a pyramid.

//ISample *StandardSamples::FormFactor_Pyramid()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorPyramid(5*Units::nanometer,
//                                            5*Units::nanometer,
//                                            Units::deg2rad(54.73 ) ) ) );
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of Prism3.

//ISample *StandardSamples::FormFactor_Prism3()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-7e-6, 2e-8);
//    complex_t n_particle(1.0-8e-4, 2e-8);
//    const IMaterial *p_air_material =
//        MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material =
//        MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    const IMaterial *particle_material =
//            MaterialManager::getHomogeneousMaterial("Particle", n_particle);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration
//        (new Particle(particle_material,
//                      new FormFactorPrism3(5*Units::nanometer,
//                                           5*Units::nanometer)));
//    particle_decoration.addInterferenceFunction
//        (new InterferenceFunctionNone());

//    air_layer.setDecoration(particle_decoration);

//    p_multi_layer->addLayer(air_layer);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}

////! Functional test: Formfactor of a full sphere.

//ISample *StandardSamples::FormFactor_FullSphere()
//{
//     MultiLayer *p_multi_layer = new MultiLayer();
//     complex_t n_air(1.0, 0.0);
//     complex_t n_substrate(1.0-6e-6, 2e-8);
//     complex_t n_particle(1.0-6e-4, 2e-8);
//     const IMaterial *p_air_material =
//         MaterialManager::getHomogeneousMaterial("Air", n_air);
//     const IMaterial *p_substrate_material =
//         MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//     const IMaterial *particle_material =
//             MaterialManager::getHomogeneousMaterial("Particle", n_particle);
//     Layer air_layer;
//     air_layer.setMaterial(p_air_material);
//     Layer substrate_layer;
//     substrate_layer.setMaterial(p_substrate_material);
//     ParticleDecoration particle_decoration
//         (new Particle(particle_material,
//                       new FormFactorFullSphere(5*Units::nanometer ) ) );
//     particle_decoration.addInterferenceFunction
//         (new InterferenceFunctionNone());

//     air_layer.setDecoration(particle_decoration);

//     p_multi_layer->addLayer(air_layer);
//     p_multi_layer->addLayer(substrate_layer);
//     return p_multi_layer;
//}

//! Multilayer specular magnetic testcase

ISample *StandardSamples::MultilayerSpecularMagneticTestCase()
{
    const IMaterial *mAmbience =
        MaterialManager::getHomogeneousMaterial
        ("ambience", 0.0, 0.0 );
    kvector_t magnetic_field(0.0, 1.0, 0.0);
    const IMaterial *mPartA =
        MaterialManager::getHomogeneousMagneticMaterial
        ("PartA", 5e-6, 0.0, magnetic_field);
    const IMaterial *mPartB =
        MaterialManager::getHomogeneousMagneticMaterial
        ("PartB", 8e-6, 0.0, -magnetic_field );
    const IMaterial *mSubstrate =
        MaterialManager::getHomogeneousMaterial
        ("substrate", 15e-6, 0.0 );

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);

    Layer lPartA;
    lPartA.setMaterial(mPartA, 5.0*Units::nanometer);

    Layer lPartB;
    lPartB.setMaterial(mPartB, 5.0*Units::nanometer);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate, 0);

    MultiLayer *mySample = new MultiLayer;

    // adding layers
    mySample->addLayer(lAmbience);

    const unsigned nrepetitions = 10;
    for(unsigned i=0; i<nrepetitions; ++i) {
        mySample->addLayer(lPartA);
        mySample->addLayer(lPartB);
    }

    mySample->addLayer(lSubstrate);

    return mySample;
}

//! Polarized DWBA test case

//ISample *StandardSamples::PolarizedDWBATestCase()
//{
//    const IMaterial *mAmbience =
//        MaterialManager::getHomogeneousMaterial
//        ("ambience", 0.0, 0.0 );
//    kvector_t magnetic_field(0.0, 1.0, 0.0);
//    const IMaterial *mPart =
//        MaterialManager::getHomogeneousMagneticMaterial
//        ("particle", 5e-6, 0.0, magnetic_field);
////    const IMaterial *mPart =
////        MaterialManager::getHomogeneousMaterial
////        ("particle", 5e-6, 0.0);
//    const IMaterial *mSubstrate =
//        MaterialManager::getHomogeneousMaterial
//        ("substrate", 15e-6, 0.0 );

//    Layer lAmbience;
//    lAmbience.setMaterial(mAmbience, 0);

//    Layer lSubstrate;
//    lSubstrate.setMaterial(mSubstrate, 0);

//    ParticleDecoration particle_decoration;

//    particle_decoration.addParticle(
//                new Particle(mPart,
//                             new FormFactorCylinder(
//                                     5.0*Units::nanometer,
//                                     5.0*Units::nanometer)
//                             ));
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

//    //LayerDecorator air_layer_decorator(air_layer, particle_decoration);
//    lAmbience.setDecoration(particle_decoration);

//    MultiLayer *mySample = new MultiLayer;

//    // adding layers
//    mySample->addLayer(lAmbience);

//    mySample->addLayer(lSubstrate);

//    return mySample;
//}


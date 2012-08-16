#include "StandardSamples.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "Units.h"
#include "NanoParticle.h"
#include "FormFactors.h"
#include "Transform3D.h"
#include "NanoParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "LayerDecorator.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "NanoParticleCrystal.h"
#include "MesoCrystal.h"
#include "InterferenceFunction1DParaCrystal.h"


/* ************************************************************************* */
// 10 nm of ambience on top of substrate.
/* ************************************************************************* */
ISample *StandardSamples::AirOnSubstrate()
{
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0) );

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


/* ************************************************************************* */
// 10 nm of substrate on top of substrate.
/* ************************************************************************* */
ISample *StandardSamples::SubstrateOnSubstrate()
{
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0) );

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


/* ************************************************************************* */
// simple multilayer
/* ************************************************************************* */
ISample *StandardSamples::SimpleMultilayer()
{
    MaterialManager &matManager = MaterialManager::instance();

    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience", complex_t(1.0, 0.0) );
    const IMaterial *mAg1 = matManager.addHomogeneousMaterial("ag1", complex_t(1.0-5e-6, 0.0) );
    const IMaterial *mCr1 = matManager.addHomogeneousMaterial("cr1", complex_t(1.0-10e-6, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate2", complex_t(1.0-15e-6, 0.0) );

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


/* ************************************************************************* */
// Multilayer offspecular tescase: 10x2 layers without cross correlataion
// analog of Artur's offspec1.py
// to compare with 'MultilayerOffspecTestcase1b'
/* ************************************************************************* */
ISample *StandardSamples::MultilayerOffspecTestcase1a()
{
    MaterialManager &matManager = MaterialManager::instance();

    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience", complex_t(1.0, 0.0) );
    const IMaterial *mPartA = matManager.addHomogeneousMaterial("PartA", complex_t(1.0-5e-6, 0.0) );
    const IMaterial *mPartB = matManager.addHomogeneousMaterial("PartB", complex_t(1.0-10e-6, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0.0) );

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


/* ************************************************************************* */
// Multilayer offspecular tescase: 10x2 layers with cross correlataion
// analog of Artur's offspec2.py
// to compare with 'MultilayerOffspecTestcase1a'
/* ************************************************************************* */
ISample *StandardSamples::MultilayerOffspecTestcase1b()
{
    MultiLayer *myOrigSample = dynamic_cast<MultiLayer *>(StandardSamples::MultilayerOffspecTestcase1a());
    MultiLayer *mySample = myOrigSample->clone();
    delete myOrigSample;
    mySample->setCrossCorrLength(1e10);
    return mySample;
}


/* ************************************************************************* */
// Multilayer offspecular tescase: air on substrate with roughness
// analog of Artur's offspec3.py
// to compare with 'MultilayerOffspecTestcase2b'
/* ************************************************************************* */
ISample *StandardSamples::MultilayerOffspecTestcase2a()
{
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0) );

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


/* ************************************************************************* */
// Multilayer offspecular tescase: very thin air on substrate with roughness
// analog of Artur's offspec4.py
// to compare with 'MultilayerOffspecTestcase2a'
/* ************************************************************************* */
ISample *StandardSamples::MultilayerOffspecTestcase2b()
{
    MultiLayer *myOrigSample = dynamic_cast<MultiLayer *>(StandardSamples::MultilayerOffspecTestcase2a());
    MultiLayer *mySample = myOrigSample->clone();
    delete myOrigSample;
    // changing thickness of middle layer
    mySample->setLayerThickness(1, 0.01*Units::nanometer);
    return mySample;
}


/* ************************************************************************* */
// IsGISAXS1 functional test: cylinder and prism
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS1_CylinderAndPrism()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration;
    particle_decoration.addNanoParticle(new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),0.0, 0.5);
    particle_decoration.addNanoParticle(new NanoParticle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
// IsGISAXS3 functional test: cylinder on top of substrate
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS3_CylinderDWBA()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration( new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

// IsGISAXS3 functional test: cylinder in the air
ISample *StandardSamples::IsGISAXS3_CylinderBA()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    NanoParticleDecoration particle_decoration( new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

// IsGISAXS3 functional test: cylinder in the air with size distribution
ISample *StandardSamples::IsGISAXS3_CylinderBASize()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    NanoParticleDecoration particle_decoration( new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}


/* ************************************************************************* */
// IsGISAXS9 functional test: pyramid
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS9_Pyramid()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
// IsGISAXS9 functional test: Rotated pyramid
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS9_RotatedPyramid()
{
    const double angle_around_z = 45.*Units::degree;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    NanoParticle *pyramid = new NanoParticle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73)) );

    Geometry::Transform3D *transform = new Geometry::Transform3D();
    *transform = Geometry::RotateZ3D(angle_around_z);

    NanoParticleDecoration particle_decoration;

    particle_decoration.addNanoParticle(pyramid, transform);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
// IsGISAXS10 functional test: cylinders with interference
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS10_CylindersParacrystal1D()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-5e-6, 2e-8);
    complex_t n_particle(1.0-5e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air10", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate10", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,7*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    //    particle_decoration.setTotalParticleSurfaceDensity(1.0/(20.0*Units::nanometer*20.0*Units::nanometer));
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
// first mesco crystal test
/* ************************************************************************* */
ISample *StandardSamples::MesoCrystal1()
{
    // create mesocrystal
    double R = 6.1*Units::nanometer;
    Lattice lat = Lattice::createTrigonalLattice(R*2.0, R*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    complex_t n_particle(1.0-1.5e-5, 1.3e-6);
    NanoParticle particle(n_particle, new FormFactorFullSphere(R));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    NanoParticleCrystal npc(basis, lat);
    MesoCrystal meso(npc.clone(), new FormFactorCylinder(0.2*Units::micrometer, 300*Units::nanometer));
    MesoCrystal meso2(npc.clone(), new FormFactorPyramid(0.2*Units::micrometer, 300*Units::nanometer, 84*Units::degree));

    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-3.5e-6, 7.8e-8);

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air2", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate2", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    //    IInterferenceFunction *p_interference_funtion = new InterferenceFunctionNone();
    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(800.0*Units::nanometer,
        50*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(meso.clone(), 0.0, 0.5);
    particle_decoration.addNanoParticle(meso2.clone(), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;

}

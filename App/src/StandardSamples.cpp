#include "StandardSamples.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "Units.h"
#include "Particle.h"
#include "FormFactors.h"
#include "Transform3D.h"
#include "ParticleDecoration.h"
#include "InterferenceFunctionNone.h"
#include "LayerDecorator.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Crystal.h"
#include "MesoCrystal.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorWeighted.h"
#include "StochasticGaussian.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "ParticleBuilder.h"
#include "StochasticSampledParameter.h"
#include "ParticleCoreShell.h"
#include "FormFactorBox.h"
#include "FormFactorCone.h"
#include "FormFactorSphere.h"
#include "FormFactorEllipsoid.h"
#include "FormFactorFullSpheroid.h"
#include "FormFactorHemiSpheroid.h"
#include "FormFactorFullSphere.h"
#include "FormFactorPrism3.h"

#include "Particle.h"

#include "IsGISAXSMorphologyFileDecoration.h"


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
// Functional test: Box
/* *************************************************************************/
//ISample *StandardSamples::FormFactors_Box()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-4e-6, 2e-8);
//    complex_t n_particle(1.0-5e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration(
//                new Particle(n_particle, new FormFactorBox(5.0*Units::nanometer, 5.0*Units::nanometer, 5.0*Units::nanometer) ) );
//
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
//
//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}
//


/* ************************************************************************* */
// Functional test: Ellipsoid
/* *************************************************************************/
//ISample *StandardSamples::FormFactors_Ellipsoid()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-4e-6, 2e-8);
//    complex_t n_particle(1.0-5e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration(
//                new Particle(n_particle, new FormFactorEllipsoid(4.0*Units::nanometer, 5.0*Units::nanometer, 6.0*Units::nanometer) ) );
//
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
//
//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}



/* ************************************************************************* */
// Functional test: Prism6
/* *************************************************************************/

//ISample *StandardSamples::FormFactors_Prism6()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-5e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration(
//                new Particle(n_particle, new FormFactorPrism6(4.0*Units::nanometer, 5.0*Units::nanometer) ) );
//
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
//
//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}


/* ************************************************************************* */
// Functional test: Full Sphere
/* *************************************************************************/

//ISample *StandardSamples::FormFactors_FullSphere()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-3e-6, 2e-8);
//    complex_t n_particle(1.0-5e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration(
//                new Particle(n_particle, new FormFactorFullSphere(4.0*Units::nanometer) ) );
//
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
//
//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}
//
//


/* ************************************************************************* */
// IsGISAXS1 functional test: cylinder and prism
/* ************************************************************************* */
//ISample *StandardSamples::IsGISAXS1_CylinderAndPrism()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration;
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),0.0, 0.5);
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}


/* ************************************************************************* */
// IsGISAXS2 functional test: Mixture cylinder particles with different size distribution
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS2_CylindersMixture()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    ParticleDecoration particle_decoration;

    // preparing nano particles prototypes for seeding layer's particle_decoration
    double radius1 = 5*Units::nanometer;
    double radius2 = 10*Units::nanometer;
    double height1 = radius1;
    double height2 = radius2;
    FormFactorCylinder *p_ff_cylinder1 = new FormFactorCylinder(height1, radius1);
    Particle cylinder1(n_particle, p_ff_cylinder1 );

    FormFactorCylinder *p_ff_cylinder2 = new FormFactorCylinder(height2, radius2);
    Particle cylinder2(n_particle, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=150;
    double sigma1 = radius1*0.2;
    double sigma2 = radius2*0.02;
    int nfwhm(3); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    StochasticSampledParameter par1(StochasticDoubleGaussian(radius1, sigma1), nbins, nfwhm);
    StochasticSampledParameter par2(StochasticDoubleGaussian(radius2, sigma2), nbins, nfwhm);

    // building nano particles
    ParticleBuilder builder;
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, 0.95);
    builder.plantParticles(particle_decoration);

    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, 0.05);
    builder.plantParticles(particle_decoration);

    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    // making layer holding all whose nano particles
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);

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
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
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
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
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

    ParticleDecoration particle_decoration;

    // preparing prototype of nano particle
    double radius = 5*Units::nanometer;
    double sigma = 0.2*radius;
    FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( 5*Units::nanometer, radius);
    Particle nano_particle(n_particle, p_ff_cylinder);

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins(100), nfwhm(2);
    StochasticSampledParameter par(StochasticDoubleGaussian(radius, sigma), nbins, nfwhm);

    ParticleBuilder builder;
    builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
    builder.plantParticles(particle_decoration);

    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);

    return p_multi_layer;
}

/* ************************************************************************* */
// IsGISAXS4 functional test: cylinders with 1DDL structure factor
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS4_1DDL()
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
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,7*Units::nanometer, 1e3*Units::nanometer);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

// IsGISAXS4 functional test: cylinders with 2DDL structure factor
ISample *StandardSamples::IsGISAXS4_2DDL()
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
    InterferenceFunction2DParaCrystal *p_interference_function = InterferenceFunction2DParaCrystal::createHexagonal(20.0*Units::nanometer, 0.0,
            20.0*Units::micrometer, 20.0*Units::micrometer);
    FTDistribution2DCauchy pdf(1.0*Units::nanometer, 1.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf, pdf);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

/* ************************************************************************* */
// IsGISAXS7 functional test: particle mixture from morphology file
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS7_morphology()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    IsGISAXSMorphologyFileDecoration particle_decoration;
    // add particle number 1:
    FormFactorBox ff1(1.0*Units::nanometer, 1.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos1(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    particle_decoration.addParticle(new Particle(n_particle, ff1), 0, pos1, 0.5);
    // add particle number 2:
    FormFactorBox ff2(1.0*Units::nanometer, 2.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos2(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot2(10*Units::degree);
    Particle particle2(n_particle, ff2);
    particle_decoration.addParticle(particle2, rot2, pos2, 0.5);
    // add particle number 3:
    FormFactorBox ff3(1.0*Units::nanometer, 3.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos3(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot3(20*Units::degree);
    Particle particle3(n_particle, ff3);
    particle_decoration.addParticle(particle3, rot3, pos3, 0.5);
    // add particle number 4:
    FormFactorBox ff4(1.0*Units::nanometer, 4.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos4(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot4(30*Units::degree);
    Particle particle4(n_particle, ff4);
    particle_decoration.addParticle(particle4, rot4, pos4, 0.5);
    // add particle number 5:
    FormFactorBox ff5(1.0*Units::nanometer, 5.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos5(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot5(40*Units::degree);
    Particle particle5(n_particle, ff5);
    particle_decoration.addParticle(particle5, rot5, pos5, 0.5);
    // add particle number 6:
    FormFactorBox ff6(1.0*Units::nanometer, 1.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos6(0.0*Units::nanometer, 0.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot6(50*Units::degree);
    Particle particle6(n_particle, ff6);
    particle_decoration.addParticle(particle6, rot6, pos6, 0.5);
    // add particle number 7:
    FormFactorBox ff7(1.0*Units::nanometer, 2.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos7(5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot7(60*Units::degree);
    Particle particle7(n_particle, ff7);
    particle_decoration.addParticle(particle7, rot7, pos7, 0.5);
    // add particle number 8:
    FormFactorBox ff8(1.0*Units::nanometer, 3.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos8(-5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot8(70*Units::degree);
    Particle particle8(n_particle, ff8);
    particle_decoration.addParticle(particle8, rot8, pos8, 0.5);
    // add particle number 9:
    FormFactorBox ff9(1.0*Units::nanometer, 4.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos9(5.0*Units::nanometer, -5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot9(80*Units::degree);
    Particle particle9(n_particle, ff9);
    particle_decoration.addParticle(particle9, rot9, pos9, 0.5);
    // add particle number 10:
    FormFactorBox ff10(1.0*Units::nanometer, 5.0*Units::nanometer,1.0*Units::nanometer);
    kvector_t pos10(-5.0*Units::nanometer, 5.0*Units::nanometer, 0.0);
    Geometry::RotateZ3D rot10(90*Units::degree);
    Particle particle10(n_particle, ff10);
    particle_decoration.addParticle(particle10, rot10, pos10, 0.5);

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

/* ************************************************************************* */
// IsGISAXS8 functional test: 2D paracrystal lattice
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS8_2DDL_lattice()
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
    InterferenceFunction2DParaCrystal *p_interference_function = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 2.0*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 2.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

// IsGISAXS8 functional test: 2D paracrystal lattice with isotropic pdfs
ISample *StandardSamples::IsGISAXS8_2DDL_lattice2()
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
    InterferenceFunction2DParaCrystal *p_interference_function = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 0.5*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 0.5*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
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
    ParticleDecoration particle_decoration(
                new Particle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
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

    Particle *pyramid = new Particle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73)) );

    Geometry::Transform3D *transform = new Geometry::RotateZ3D(angle_around_z);

    ParticleDecoration particle_decoration;

    particle_decoration.addParticle(pyramid, transform);
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
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,7*Units::nanometer, 1e7*Units::nanometer);
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    //    particle_decoration.setTotalParticleSurfaceDensity(1.0/(20.0*Units::nanometer*20.0*Units::nanometer));
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

/* ************************************************************************* */
// IsGISAXS11 functional test: core shell parallelepiped islands
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS11_CoreShellParticles()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air11", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Particle shell_particle(n_particle_shell, new FormFactorParallelepiped(8*Units::nanometer, 8*Units::nanometer));
    Particle core_particle(n_particle_core, new FormFactorParallelepiped(7*Units::nanometer, 6*Units::nanometer));
    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleDecoration particle_decoration(particle.clone());
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

/* ************************************************************************* */
// IsGISAXS14 functional test: layered sphere on graded interface
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS14_LayeredSpheresOnGradedInterface()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air10", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate10", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(15.0*Units::nanometer,5*Units::nanometer, 1e7*Units::nanometer);
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorSphere(5*Units::nanometer, 5.*2.0*Units::nanometer)));
    //ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorFullSphere(5.0*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);
    //particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    //    particle_decoration.setTotalParticleSurfaceDensity(1.0/(20.0*Units::nanometer*20.0*Units::nanometer));
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);

    return p_multi_layer;
}

/* ************************************************************************* */
// IsGISAXS15 functional test: size-spacing correlation approximation
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS15_SSCA()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    InterferenceFunction1DParaCrystal *p_interference_function = new InterferenceFunction1DParaCrystal(15.0*Units::nanometer,5*Units::nanometer, 1e3*Units::nanometer);
    p_interference_function->setKappa(4.02698);
    ParticleDecoration particle_decoration;
    Particle particle_prototype(n_particle, new FormFactorCylinder(5.0*Units::nanometer, 5.0*Units::nanometer));
    StochasticSampledParameter stochastic_radius(StochasticDoubleGaussian(5.0*Units::nanometer, 1.25*Units::nanometer),
            30, 2);
    ParticleBuilder particle_builder;
    particle_builder.setPrototype(particle_prototype, "/Particle/FormFactorCylinder/radius", stochastic_radius);
    particle_builder.plantParticles(particle_decoration);

    // Set height of each particle to its radius (H/R fixed)
    ParameterPool *p_parameters = particle_decoration.createParameterTree();
    int nbr_replacements = p_parameters->fixRatioBetweenParameters("height", "radius", 1.0);
    std::cout << "Number of replacements: " << nbr_replacements << std::endl;
//    std::cout << *p_parameters << std::endl;

    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

/* ************************************************************************* */
// first mesco crystal test
/* ************************************************************************* */
ISample *StandardSamples::MesoCrystal1()
{
    // create mesocrystal
    double nanoparticle_radius = 6.1*Units::nanometer;
    Lattice lat = Lattice::createTrigonalLattice(nanoparticle_radius*2.0, nanoparticle_radius*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    complex_t n_particle(1.0-1.5e-5, 1.3e-6);
    Particle particle(n_particle, new FormFactorFullSphere(nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    //lat.setSelectionRule(new SimpleSelectionRule(-1, 1, 1, 3));
    Crystal npc(basis, lat);
//    double relative_sigma_np_radius = 0.3;
//    double dw_factor = relative_sigma_np_radius*relative_sigma_np_radius*nanoparticle_radius*nanoparticle_radius/6.0;
//    npc.setDWFactor(dw_factor);

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
//    IInterferenceFunction *p_interference_function = new InterferenceFunctionNone();
    IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(800.0*Units::nanometer,
        50*Units::nanometer, 1e7*Units::nanometer);
    ParticleDecoration particle_decoration;
    particle_decoration.addParticle(meso.clone(), 0.0, 0.5);
    particle_decoration.addParticle(meso2.clone(), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;

}


/* ************************************************************************* */
// second mesco crystal test
// mesocrystal from TestMesocrystal to play with
/* ************************************************************************* */
ISample *StandardSamples::MesoCrystal2()
{
    double meso_radius = 300*Units::nanometer;
    double surface_filling_ratio = 0.25;
    double surface_density = surface_filling_ratio/M_PI/meso_radius/meso_radius;
    complex_t n_particle(1.0-1.55e-5, 1.37e-6);
    complex_t avg_n_squared_meso = 0.7886*n_particle*n_particle + 0.2114;
    complex_t n_avg = std::sqrt(surface_filling_ratio*avg_n_squared_meso + 1.0 - surface_filling_ratio);
    complex_t n_particle_adapted = std::sqrt(n_avg*n_avg + n_particle*n_particle - 1.0);
    FormFactorCylinder ff_meso(0.2*Units::micrometer, meso_radius);

    // Create multilayer
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-7.57e-6, 1.73e-7);

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_average_layer_material = MaterialManager::instance().addHomogeneousMaterial("Averagelayer", n_avg);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer avg_layer;
    avg_layer.setMaterial(p_average_layer_material);
    avg_layer.setThickness(0.2*Units::micrometer);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_function = new InterferenceFunctionNone();
    ParticleDecoration particle_decoration;

    //
    double nanoparticle_radius = 5.4*Units::nanometer;
    const IFormFactor* p_meso_form_factor = &ff_meso;
    Lattice lat = Lattice::createTrigonalLattice(nanoparticle_radius*2.0, nanoparticle_radius*2.0*2.3);
    kvector_t bas_a = lat.getBasisVectorA();
    kvector_t bas_b = lat.getBasisVectorB();
    kvector_t bas_c = lat.getBasisVectorC();
    Particle particle(n_particle_adapted, new FormFactorFullSphere(nanoparticle_radius));
    kvector_t position_0 = kvector_t(0.0, 0.0, 0.0);
    kvector_t position_1 = 1.0/3.0*(2.0*bas_a + bas_b + bas_c);
    kvector_t position_2 = 1.0/3.0*(bas_a + 2.0*bas_b + 2.0*bas_c);
    std::vector<kvector_t> pos_vector;
    pos_vector.push_back(position_0);
    pos_vector.push_back(position_1);
    pos_vector.push_back(position_2);
    LatticeBasis basis(particle, pos_vector);
    Crystal npc(basis, lat);
    MesoCrystal *meso_crystal = new MesoCrystal(npc.clone(), p_meso_form_factor->clone());

    particle_decoration.addParticle(meso_crystal, 0.2*Units::micrometer);

    particle_decoration.setTotalParticleSurfaceDensity(surface_density);
    particle_decoration.addInterferenceFunction(p_interference_function);
    LayerDecorator avg_layer_decorator(avg_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer);
    p_multi_layer->addLayer(avg_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;

}

/* ************************************************************************* */
// functional test: Box
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Box()
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
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorBox(5*Units::nanometer, 5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

/* ************************************************************************* */
//  functional test: Form Factor Cone
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Cone()
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
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorCone(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ))));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
//  functional test: Form Factor Sphere
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Sphere()
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
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorSphere(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

/* ************************************************************************* */
//  functional test: Form Factor Ellipsoid
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Ellipsoid()
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
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorEllipsoid(5*Units::nanometer, 5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ))));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
//  functional test: Form Factor Full Spheroid
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_FullSpheroid()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-5, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorFullSpheroid(5*Units::nanometer, 7*Units::nanometer )));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
//  functional test: Form Factor Hemi Spheroid
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_HemiSpheroid()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-7, 2e-8);
    complex_t n_particle(1.0-6e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorHemiSpheroid(5*Units::nanometer, 4*Units::nanometer, 2*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

/* ************************************************************************* */
// functional test: Form Factor parallelepiped
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Parallelpiped()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air11", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Particle shell_particle(n_particle_shell, new FormFactorParallelepiped(8*Units::nanometer, 8*Units::nanometer));
    Particle core_particle(n_particle_core, new FormFactorParallelepiped(7*Units::nanometer, 6*Units::nanometer));
    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleDecoration particle_decoration(particle.clone());
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}


/* ************************************************************************* */
// functional test: Form Factor Cylinder
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Cylinder()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air11", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Particle shell_particle(n_particle_shell, new FormFactorCylinder(8*Units::nanometer, 8*Units::nanometer));
    Particle core_particle(n_particle_core, new FormFactorCylinder(7*Units::nanometer, 6*Units::nanometer));
    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleDecoration particle_decoration(particle.clone());
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

/* ************************************************************************* */
// Functional test: Pyramid
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Pyramid()
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
    ParticleDecoration particle_decoration(
                new Particle(n_particle, new FormFactorPyramid(5*Units::nanometer, 5*Units::nanometer, Units::deg2rad(54.73 ) ) ) );
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}


/* ************************************************************************* */
// functional test: Prism3
/* ************************************************************************* */
ISample *StandardSamples::FormFactor_Prism3()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-7e-6, 2e-8);
    complex_t n_particle(1.0-8e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    ParticleDecoration particle_decoration(new Particle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

 /************************************************************************** */
 // Functional test: Full Sphere
 /************************************************************************** */
    ISample *StandardSamples::FormFactor_FullSphere()
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
     ParticleDecoration particle_decoration(
                 new Particle(n_particle, new FormFactorFullSphere(5*Units::nanometer ) ) );
     particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
     LayerDecorator air_layer_decorator(air_layer, particle_decoration);

     p_multi_layer->addLayer(air_layer_decorator);
     p_multi_layer->addLayer(substrate_layer);
     return p_multi_layer;
     }

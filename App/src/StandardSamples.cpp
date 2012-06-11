#include "StandardSamples.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "Units.h"

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

//    LayerRoughness roughness;
//    roughness.setSigma(1.0*Units::nanometer);
//    roughness.setHurstParameter(0.3);
//    roughness.setLatteralCorrLength(5000.*Units::nanometer);
//    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

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

//    LayerRoughness roughness;
//    roughness.setSigma(1.0*Units::nanometer);
//    roughness.setHurstParameter(0.3);
//    roughness.setLatteralCorrLength(5000.*Units::nanometer);
//    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

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
    const IMaterial *mAg1 = matManager.addHomogeneousMaterial("ag1", complex_t(0.99999653774962993, 0.0) );
    const IMaterial *mCr1 = matManager.addHomogeneousMaterial("cr1", complex_t(0.99999701914797656, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate2", complex_t(0.99999692440971188, 0.0) );

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

    const unsigned nrepetitions = 2;
    for(unsigned i=0; i<nrepetitions; ++i) {
        mySample->addLayer(lAg1);
        mySample->addLayer(lCr1);
    }
    mySample->addLayer(lSubstrate);
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
    roughness.setSigma(0.5*Units::nanometer);
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

    mySample->setCrossCorrLength(1e-10);

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
    lAir.setMaterial(mAmbience, 0.01*Units::nanometer);
    mySample->addLayerWithTopRoughness(lAir, roughness);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);
    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

    return mySample;
}



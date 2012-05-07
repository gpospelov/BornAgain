#include "StandardSamples.h"
#include "MultiLayer.h"
#include "MaterialManager.h"


/* ************************************************************************* */
// 10 nm of ambience on top of substrate.
/* ************************************************************************* */
ISample *StandardSamples::SampleAirOnSubstrate()
{
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mAir = matManager.addHomogeneousMaterial("air",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0) );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);
    mySample->addLayer(lAmbience);

    Layer lAir;
    lAir.setMaterial(mAir, 10);
    mySample->addLayer(lAir);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);

    LayerRoughness roughness;
    roughness.setSigma(1.0);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(5000.);

    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

    return mySample;
}


/* ************************************************************************* */
// 10 nm of substrate on top of substrate.
/* ************************************************************************* */
ISample *StandardSamples::SampleSubstrateOnSubstrate()
{
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0) );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);
    mySample->addLayer(lAmbience);

    Layer likeSubstrate;
    likeSubstrate.setMaterial(mSubstrate, 10);
    mySample->addLayer(likeSubstrate);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);

    LayerRoughness roughness;
    roughness.setSigma(1.0);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(5000.);

    mySample->addLayerWithTopRoughness(lSubstrate, roughness);

    return mySample;
}



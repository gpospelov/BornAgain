// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/StandardSamples.cpp
//! @brief     Implements class StandardSamples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardSamples.h"
#include "MultiLayer.h"
#include "Materials.h"
#include "Units.h"
#include "Particle.h"
#include "FormFactors.h"
#include "ParticleLayout.h"
#include "InterferenceFunctionNone.h"
#include "Lattice.h"
#include "ParticleComposition.h"
#include "Crystal.h"
#include "MesoCrystal.h"
#include "InterferenceFunctions.h"
#include "Numeric.h"
#include "MathFunctions.h"
#include "ParticleCoreShell.h"
#include "Particle.h"

//! 10 nm of ambience on top of substrate.

ISample *StandardSamples::AirOnSubstrate()
{
    HomogeneousMaterial mAmbience("ambience", 0.0, 0.0 );
    HomogeneousMaterial mSubstrate ("substrate", 15e-6, 0 );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterialAndThickness(mAmbience, 0);
    mySample->addLayer(lAmbience);

    Layer lAir;
    lAir.setMaterialAndThickness(mAmbience, 10*Units::nanometer);
    mySample->addLayer(lAir);

    Layer lSubstrate;
    lSubstrate.setMaterialAndThickness(mSubstrate,0);
    mySample->addLayer(lSubstrate);

    return mySample;
}


//! 10 nm of substrate on top of substrate.
ISample *StandardSamples::SubstrateOnSubstrate()
{
    HomogeneousMaterial mAmbience("ambience", 0.0, 0.0 );
    HomogeneousMaterial mSubstrate("substrate", 15e-6, 0 );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterialAndThickness(mAmbience, 0);
    mySample->addLayer(lAmbience);

    Layer likeSubstrate;
    likeSubstrate.setMaterialAndThickness(mSubstrate, 10*Units::nanometer);
    mySample->addLayer(likeSubstrate);

    Layer lSubstrate;
    lSubstrate.setMaterialAndThickness(mSubstrate,0);
    mySample->addLayer(lSubstrate);

    return mySample;
}


//! Simple multilayer.
ISample *StandardSamples::SimpleMultilayer()
{
    HomogeneousMaterial mAmbience("ambience", 0.0, 0.0 );
    HomogeneousMaterial mAg1("ag1", 5e-6, 0.0 );
    HomogeneousMaterial mCr1("cr1", 10e-6, 0.0 );
    HomogeneousMaterial mSubstrate("substrate2", 15e-6, 0.0 );

    Layer lAmbience;
    lAmbience.setMaterialAndThickness(mAmbience, 0);

    Layer lAg1;
    lAg1.setMaterialAndThickness(mAg1, 150.0*Units::nanometer);

    Layer lCr1;
    lCr1.setMaterialAndThickness(mCr1, 120.0*Units::nanometer);

    Layer lSubstrate;
    lSubstrate.setMaterialAndThickness(mSubstrate, 0);

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
    HomogeneousMaterial mAmbience("ambience", 0.0, 0.0 );
    HomogeneousMaterial mPartA ("PartA", 5e-6, 0.0 );
    HomogeneousMaterial mPartB ("PartB",10e-6, 0.0 );
    HomogeneousMaterial mSubstrate("substrate", 15e-6, 0.0 );

    Layer lAmbience;
    lAmbience.setMaterialAndThickness(mAmbience, 0);

    Layer lPartA;
    lPartA.setMaterialAndThickness(mPartA, 5.0*Units::nanometer);

    Layer lPartB;
    lPartB.setMaterialAndThickness(mPartB, 10.0*Units::nanometer);

    Layer lSubstrate;
    lSubstrate.setMaterialAndThickness(mSubstrate, 0);

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
    HomogeneousMaterial mAmbience("ambience", 0.0, 0.0);
    HomogeneousMaterial mSubstrate("substrate", 15e-6, 0 );

    MultiLayer *mySample = new MultiLayer;

    Layer lAmbience;
    lAmbience.setMaterialAndThickness(mAmbience, 0);
    mySample->addLayer(lAmbience);

    LayerRoughness roughness;
    roughness.setSigma(0.5*Units::nanometer);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(500.*Units::nanometer);

    Layer lAir;
    lAir.setMaterialAndThickness(mAmbience, 10*Units::nanometer);
    mySample->addLayerWithTopRoughness(lAir, roughness);

    Layer lSubstrate;
    lSubstrate.setMaterialAndThickness(mSubstrate,0);
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


//! Multilayer specular magnetic testcase
ISample *StandardSamples::MultilayerSpecularMagneticTestCase()
{
    HomogeneousMaterial mAmbience("ambience", 0.0, 0.0 );
    kvector_t magnetic_field(0.0, 1.0, 0.0);
    HomogeneousMagneticMaterial mPartA("PartA", 5e-6, 0.0, magnetic_field);
    HomogeneousMagneticMaterial mPartB ("PartB", 8e-6, 0.0, -magnetic_field );
    HomogeneousMaterial mSubstrate ("substrate", 15e-6, 0.0 );

    Layer lAmbience;
    lAmbience.setMaterialAndThickness(mAmbience, 0);

    Layer lPartA;
    lPartA.setMaterialAndThickness(mPartA, 5.0*Units::nanometer);

    Layer lPartB;
    lPartB.setMaterialAndThickness(mPartB, 5.0*Units::nanometer);

    Layer lSubstrate;
    lSubstrate.setMaterialAndThickness(mSubstrate, 0);

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


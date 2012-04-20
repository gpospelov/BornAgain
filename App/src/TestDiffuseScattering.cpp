#include "TestDiffuseScattering.h"
#include <iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TApplication.h"

#include "Layer.h"
#include "MultiLayer.h"
#include "HomogeneousMaterial.h"
#include "Exceptions.h"
#include "OpticalFresnel.h"
#include "DrawHelper.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"


TestDiffuseScattering::TestDiffuseScattering()
{
    std::cout << "TestDiffuseScattering::TestDiffuseScattering() -> Info." << std::endl;

}


void TestDiffuseScattering::execute()
{
    std::cout << "TestDiffuseScattering::execute() -> Info." << std::endl;

    // creation of materials
    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mAg1 = matManager.addHomogeneousMaterial( "Ag1",complex_t(0.99999653774962993, 0) );
    const IMaterial *mCr1 = matManager.addHomogeneousMaterial("Cr1",complex_t(0.99999701914797656, 0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(0.99999692440971188, 0) );
    matManager.print();

    // create layers
    MultiLayer mySample;

    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);

    Layer lAg1;
    lAg1.setMaterial(mAg1, 1500.0);

    Layer lCr1;
    lCr1.setMaterial(mCr1, 1200.0);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate, 0);

    // adding layers
    mySample.addLayer(lAmbience);

    const unsigned nrepetitions = 4;
    for(unsigned i=0; i<nrepetitions; ++i) {
        mySample.addLayerWithTopRoughness(lAg1, LayerRoughness(3.,4.,5.) );
        mySample.addLayer(lCr1);
    }
    mySample.addLayer(lSubstrate);

    mySample.print();

    std::cout << "--- Attempt to clone MultiLayer" << std::endl;

    MultiLayer *newSample = mySample.clone();
    newSample->print();

    MultiLayer *newSample2 = newSample->clone();

    delete newSample;

    newSample2->print();

}


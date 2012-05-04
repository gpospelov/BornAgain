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
        mySample.addLayerWithTopRoughness(lAg1, LayerRoughness(3.0, 0.3, 1.0) ); // (double sigma, double hurstParameter, double latteralCorrLength
        mySample.addLayerWithTopRoughness(lCr1, LayerRoughness(3.0, 0.3, 1.0) );
    }
    mySample.addLayerWithTopRoughness(lSubstrate, LayerRoughness(3.0, 0.3, 1.0));

    mySample.print();

//    std::cout << "--- Attempt to clone MultiLayer" << std::endl;
//    MultiLayer *newSample = mySample.clone();
//    newSample->print();
//    MultiLayer *newSample2 = newSample->clone();
//    delete newSample;
//    newSample2->print();

    test1(mySample);
}


// dSigma/dOmega
void TestDiffuseScattering::test1(const MultiLayer &sample)
{
    const size_t npoints = 1000.;
    double alphaMin(0), alphaMax(0.5*M_PI/180.);

    for(size_t i=0; i<npoints; i++) {
        double alpha_i = i*(alphaMax-alphaMin)/double(npoints);
        kvector_t ki;
        ki.setLambdaAlphaPhi(23.0, alpha_i, 0.0);

        kvector_t kf;
        kf.setLambdaAlphaPhi(23.0, alpha_i+180.0, 0.0);

        test1_a(sample, ki, kf);


    }


}


void TestDiffuseScattering::test1_a(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf)
{
    (void)sample;
    (void)ki;
    (void)kf;

    // calculation
//    OpticalFresnel::MultiLayerCoeff_t iniFresnelCoeffs;
//    OpticalFresnel::execute(sample, ki, iniFresnelCoeffs);

//    OpticalFresnel::MultiLayerCoeff_t finFresnelCoeffs;
//    OpticalFresnel::execute(sample, kf, finFresnelCoeffs);

    //const double S = 1.0;
    //double CS = S*ki.mag2()/16./M_PI;

//    for(size_t i=0; i<sample.getNumberOfLayers()-1; i++){
//        complex_t n1 = sample.getLayer(i)->getRefractiveIndex();
//        complex_t n2 = sample.getLayer(i+1)->getRefractiveIndex();
        //const LayerRoughness &m_roughness = sample.getLayerBottomInterface(i)->getRoughness();
        //double corr = m_roughness.getPowerSpectralDensity(ki);

//    }



}


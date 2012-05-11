#include "TestDiffuseScattering.h"
#include <iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TApplication.h"
#include "TStyle.h"

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
//    MaterialManager &matManager = MaterialManager::instance();
//    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
//    const IMaterial *mAg1 = matManager.addHomogeneousMaterial( "air",complex_t(0.99999653774962993, 0) );
//    const IMaterial *mCr1 = matManager.addHomogeneousMaterial("Cr1",complex_t(0.99999701914797656, 0) );
//    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(0.99999692440971188, 0) );
//    matManager.print();
//    // create layers
//    MultiLayer mySample;
//    Layer lAmbience;
//    lAmbience.setMaterial(mAmbience, 0);
//    Layer lAg1;
//    lAg1.setMaterial(mAg1, 1500.0);
//    Layer lCr1;
//    lCr1.setMaterial(mCr1, 1200.0);
//    Layer lSubstrate;
//    lSubstrate.setMaterial(mSubstrate, 0);
//    // adding layers
//    mySample.addLayer(lAmbience);
//    const unsigned nrepetitions = 4;
//    for(unsigned i=0; i<nrepetitions; ++i) {
//        mySample.addLayerWithTopRoughness(lAg1, LayerRoughness(3.0, 0.3, 1.0) ); // (double sigma, double hurstParameter, double latteralCorrLength
//        mySample.addLayerWithTopRoughness(lCr1, LayerRoughness(3.0, 0.3, 1.0) );
//    }
//    mySample.addLayerWithTopRoughness(lSubstrate, LayerRoughness(3.0, 0.3, 1.0));
//    mySample.print();
//    std::cout << "--- Attempt to clone MultiLayer" << std::endl;
//    MultiLayer *newSample = mySample.clone();
//    newSample->print();
//    MultiLayer *newSample2 = newSample->clone();
//    delete newSample;
//    newSample2->print();


    MaterialManager &matManager = MaterialManager::instance();
    const IMaterial *mAmbience = matManager.addHomogeneousMaterial("ambience",complex_t(1.0, 0.0) );
    const IMaterial *mAir = matManager.addHomogeneousMaterial("air",complex_t(1.0, 0.0) );
    const IMaterial *mSubstrate = matManager.addHomogeneousMaterial("substrate", complex_t(1.0-15e-6, 0) );

    MultiLayer mySample;
    Layer lAmbience;
    lAmbience.setMaterial(mAmbience, 0);
    mySample.addLayer(lAmbience);

    Layer lAir;
    lAir.setMaterial(mAir, 10);
    mySample.addLayer(lAir);

    Layer lSubstrate;
    lSubstrate.setMaterial(mSubstrate,0);

    LayerRoughness roughness;
    roughness.setSigma(1.0);
    roughness.setHurstParameter(0.3);
    roughness.setLatteralCorrLength(5000.);

    mySample.addLayerWithTopRoughness(lSubstrate, roughness);

    mySample.print();

    test1(mySample);
}


void TestDiffuseScattering::test1(const MultiLayer &sample)
{
    const size_t npoints = 100.;
    double alphaMin(0), alphaMax(2.*M_PI/180.);
    double d_alpha = (alphaMax-alphaMin)/double(npoints-1);

    double lambda = 1.54;

    TH2F *h2 = new TH2F("h2","h2", npoints, alphaMin-d_alpha/2., alphaMax+d_alpha/2., npoints, alphaMin-d_alpha/2., alphaMax+d_alpha/2.);
    h2->SetContour(50);
    h2->SetMinimum(0.001);
    for(size_t i=1; i<npoints; i++) {
        double alpha_i = i*d_alpha;
        kvector_t ki;
        ki.setLambdaAlphaPhi(lambda, -alpha_i, 0.0);
        for(size_t f=1; f<npoints; f++) {
            double alpha_f = f*d_alpha;
            kvector_t kf;
            kf.setLambdaAlphaPhi(lambda, alpha_f, 0.0);
            double cs = test1_a(sample, ki, kf);
            std::cout << " i:" << i << " " << alpha_i << " f:" <<  f << " alpha_f:" << alpha_f << " cs:" << cs << std::endl;
            h2->Fill(alpha_i, alpha_f,cs);
        } // k
    } // i

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd(); gPad->SetRightMargin(0.2);
    gStyle->SetPalette(1);
    gPad->SetLogz();
    h2->Draw("CONT4 Z");

}


double TestDiffuseScattering::test1_a(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf)
{

    // calculation
    OpticalFresnel::MultiLayerCoeff_t c_f;
    OpticalFresnel::execute(sample, ki, c_f);

    OpticalFresnel::MultiLayerCoeff_t c_i;
    OpticalFresnel::execute(sample, kf, c_i);


//    MultiLayerCoeff x(OpticalFresnel::execute, sample);
//    x.setSample(sample);
//    x.evaluate(sample, q);
//    x.getR(i);
//    x.


    double sum(0);
    for(size_t i=0; i<sample.getNumberOfLayers()-1; i++){
        complex_t n1 = sample.getLayer(i)->getRefractiveIndex();
        complex_t n2 = sample.getLayer(i+1)->getRefractiveIndex();
        const LayerRoughness &rough = sample.getLayerBottomInterface(i)->getRoughness();
        double sigma = rough.getSigma();

        kvector_t q = ki - kf;
        double qz1 = ki.z() + kf.z();
        double qz2 = -ki.z() - kf.z();
        double qz3 = ki.z() - kf.z();
        double qz4 = -ki.z() + kf.z();
        complex_t term1 = c_i[i+1].T*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz1 ,2) );
        complex_t term2 = c_i[i+1].R*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz2 ,2) );
        complex_t term3 = c_i[i+1].T*c_f[i+1].R * std::exp( -0.5*std::pow(sigma * qz3 ,2) );
        complex_t term4 = c_i[i+1].R*c_f[i+1].T * std::exp( -0.5*std::pow(sigma * qz4 ,2) );

        sum += std::norm( std::pow(n1,2)-std::pow(n2,2) ) * std::norm(term1 + term2 + term3 + term4) * rough.getSpectralFun(q);
    }

    const double S = 1.0;
    double CS = sum*S*ki.mag2()/16./M_PI;
    return CS;
}


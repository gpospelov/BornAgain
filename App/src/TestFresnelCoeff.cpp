#include "TestFresnelCoeff.h"
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


TestFresnelCoeff::TestFresnelCoeff()
{
    std::cout << "TestFresnelCoeff::TestFresnelCoeff() -> Info." << std::endl;
}


/* ****************************************************************************
Creates some multilayer system, runs calculation of Fresnel R,T coefficients for
all layers, makes plots.
**************************************************************************** */
void TestFresnelCoeff::execute()
{
    std::cout << "TestFresnelCoeff::execute() -> Info." << std::endl;

    MultiLayer mySample;

    // creation of materials and layers
    HomogeneousMaterial mAmbience( complex_t(1.0, 0.0) );
    HomogeneousMaterial mAg1( complex_t(0.99999653774962993, 0) );
    HomogeneousMaterial mCr1( complex_t(0.99999701914797656, 0) );
    HomogeneousMaterial mSubstrate( complex_t(0.99999692440971188, 0) );

    Layer lAmbience;
    lAmbience.setMaterial(&mAmbience, 0);

    Layer lAg1;
    lAg1.setMaterial(&mAg1, 1500.0);

    Layer lCr1;
    lCr1.setMaterial(&mCr1, 1200.0);

    Layer lSubstrate;
    lSubstrate.setMaterial(&mSubstrate, 0);

    // adding layers
    mySample.add(&lAmbience);

    const unsigned nrepetitions = 4;
    for(unsigned i=0; i<nrepetitions; ++i) {
        mySample.add(&lAg1);
        mySample.add(&lCr1);
    }
    mySample.add(&lSubstrate);

    // -------------------
    // calculation of Fresnel coefficients for multi-layers system
    // -------------------

    const size_t npoints = 1000.;
    double alphaMin(0), alphaMax(0.5*M_PI/180.);

    MyDataSet_t myDataSet;
    for(size_t i=0; i<npoints; i++) {
        double alpha_i = i*(alphaMax-alphaMin)/double(npoints);
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(23.0, alpha_i, 0.0);

        // calculation
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        OpticalFresnel::execute(mySample, kvec, coeffs);

        // saving data for later drawing
        MyData myData;
        myData.alpha_i = alpha_i;
        myData.coeffs = coeffs;
        myDataSet.push_back(myData);
    }

    //new TApplication("theApp", 0, 0);
    Draw(mySample, myDataSet);

}


void TestFresnelCoeff::Draw(const MultiLayer &sample, const MyDataSet_t &data)
{
    //size_t nlayers = data.front().coeffs.size();
    size_t nlayers = sample.getNumberOfLayers();

    // creation of graphics to plot R,T coefficients in layers as a function of alpha_i
    std::vector<TGraph *> gr_absR;
    std::vector<TGraph *> gr_absT;
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
      gr_absR.push_back(new TGraph() );
      gr_absT.push_back(new TGraph() );
    }
    TGraph *gr_absSum = new TGraph(); // |R_top|+|T_bottom|

    for(size_t i_point=0; i_point<data.size(); ++i_point) {
        double alpha_i = data[i_point].alpha_i;
        // Filling graphics for R,T as a function of alpha_i
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            gr_absR[i_layer]->SetPoint(i_point, alpha_i*180./M_PI, std::abs(data[i_point].coeffs[i_layer].R) );
            gr_absT[i_layer]->SetPoint(i_point, alpha_i*180./M_PI, std::abs(data[i_point].coeffs[i_layer].T) );
        }
        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
        int nlast = nlayers - 1;
        complex_t nx = sample.getLayer(nlast)->getRefractiveIndex();
        complex_t n1 = sample.getLayer(0)->getRefractiveIndex();
        //std::complex<double> kk = (1./(n1*std::sin(theta_i)))*std::sqrt(std::pow(nx,2)-cos(theta_i)*cos(theta_i)*std::pow(n1,2));
        complex_t kk = std::sqrt((complex_t(1,0) - cos(alpha_i)*cos(alpha_i)/nx/nx) ) / sin(alpha_i);
        double sum = std::norm(data[i_point].coeffs[0].R) + std::abs(kk)*std::norm(data[i_point].coeffs[nlast].T);
        // calculation for sum is not valid, when outgoing angle in the bottom layer is parallel to the surfaced
        double alpha_bottom = std::abs(n1/nx)*cos(alpha_i);
        if(1-alpha_bottom < 0.0) sum = std::norm(data[i_point].coeffs[0].R);

        gr_absSum->SetPoint(i_point, alpha_i*180./M_PI, sum);
    }

    TCanvas *c1 = new TCanvas("c1","c1",1024,768);
//    BDrawHelper *drawHelper = BDrawHelper::instance();
//    drawHelper->SetMagnifier(c1);

    int ndivy = sqrt(nlayers);
    int ndivx = nlayers/ndivy + 1;
    c1->Divide(ndivx, ndivy);

    TH1F *h1ref = new TH1F("h1ref","h1ref",100,0.0,0.3);
    h1ref->SetMinimum(0.01);
    h1ref->SetMaximum(3.0);
    h1ref->SetStats(0);
    h1ref->SetTitle("");
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
      c1->cd(i_layer+1); //gPad->SetLogy();
      h1ref->Draw();

      TGraph *gr = gr_absR[i_layer];
      gr->SetLineColor(kBlue);
      gr->SetMarkerColor(kBlue);
      gr->SetMarkerStyle(21);
      gr->SetMarkerSize(0.2);
      gr->Draw("pl same");

      gr = gr_absT[i_layer];
      gr->SetMarkerStyle(21);
      gr->SetMarkerSize(0.2);
      gr->SetLineColor(kRed);
      gr->SetMarkerColor(kRed);
      gr->Draw("pl same");
    }
    TGraph *gr = gr_absSum;
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(0.2);
    gr->SetLineColor(kMagenta);
    gr->SetMarkerColor(kMagenta);
    gr->Draw("pl same");

}




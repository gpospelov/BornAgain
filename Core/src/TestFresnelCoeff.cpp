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
    lAmbience.setMaterial(&mAmbience);

    Layer lAg1;
    lAg1.setThickness(1500.0);
    lAg1.setMaterial(&mAg1);

    Layer lCr1;
    lCr1.setThickness(1200.0);
    lCr1.setMaterial(&mCr1);

    Layer lSubstrate;
    lSubstrate.setMaterial(&mSubstrate);

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

    TApplication theApp("theApp",0,0);
    Draw(myDataSet);

    theApp.Run();

}


void TestFresnelCoeff::Draw(const MyDataSet_t &data)
{
    size_t nlayers = data.front().coeffs.size();

    std::vector<TGraph *> gr_absR;
    std::vector<TGraph *> gr_absT;
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
      gr_absR.push_back(new TGraph() );
      gr_absT.push_back(new TGraph() );
    }
    //TGraph *gr_absSum = new TGraph();

    for(size_t i_point=0; i_point<data.size(); ++i_point) {
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            double alpha_i = data[i_point].alpha_i*180./M_PI;
            gr_absR[i_layer]->SetPoint(i_point, alpha_i, std::abs(data[i_point].coeffs[i_layer].R) );
            gr_absT[i_layer]->SetPoint(i_point, alpha_i, std::abs(data[i_point].coeffs[i_layer].T) );
        }
    }
//    int nlast = m_sample->GetNlayers() - 1;
//      complex_t nx = (*m_sample)[nlast].GetRefrIndex();
//      complex_t n1 = (*m_sample)[0].GetRefrIndex();
//      //std::complex<double> kk = (1./(n1*std::sin(theta_i)))*std::sqrt(std::pow(nx,2)-cos(theta_i)*cos(theta_i)*std::pow(n1,2));
//      complex_t kk = std::sqrt((complex_t(1,0) - cos(theta_i)*cos(theta_i)/nx/nx) ) / sin(theta_i);
//      double sum = std::norm(m_FresnelCoeff[0].R) + std::abs(kk)*std::norm(m_FresnelCoeff[nlast].T);
//      gr_absSum->SetPoint(i, theta_i*180./M_PI, sum);
//    }

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
      gr->Draw("p same");

      gr = gr_absT[i_layer];
      gr->SetMarkerStyle(21);
      gr->SetMarkerSize(0.2);
      gr->SetLineColor(kRed);
      gr->SetMarkerColor(kRed);
      gr->Draw("pl same");
    }
//    TGraph *gr = gr_absSum;
//    gr->SetMarkerStyle(21);
//    gr->SetMarkerSize(0.2);
//    gr->SetLineColor(kMagenta);
//    gr->SetMarkerColor(kMagenta);
//    gr->Draw("pl same");




}




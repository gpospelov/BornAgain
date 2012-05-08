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
#include "DrawHelper.h"
#include "SampleFactory.h"
#include "Units.h"
#include "OutputData.h"

TestFresnelCoeff::TestFresnelCoeff()
{
    std::cout << "TestFresnelCoeff::TestFresnelCoeff() -> Info." << std::endl;
}


/* ************************************************************************* */
//! generation of set of Fresnel Coefficients for several standard samples
/* ************************************************************************* */
void TestFresnelCoeff::execute()
{
    std::cout << "TestFresnelCoeff::execute() -> Info." << std::endl;

    //size_t nsamples = SampleFactory::instance().getNumberOfSamples();
    for(int i_sample=0; i_sample<2; i_sample++){
        MultiLayer *mySample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createStandard(i_sample));

        m_coeffs = new OutputData<OpticalFresnel::MultiLayerCoeff_t >;

        NamedVector<double> *alpha_axis = new NamedVector<double>(std::string("alpha_axis"), 0.01*Units::degree, 2.0*Units::degree, 200);
        m_coeffs->addAxis(alpha_axis);

        MultiIndex &index = m_coeffs->getIndex();
        while (!index.endPassed())
        {
            size_t index_y = index.getCoordinate("alpha_axis");
            double alpha_i = (*alpha_axis)[index_y];
            kvector_t kvec = kvector_t::LambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);

            OpticalFresnel::MultiLayerCoeff_t coeffs;
            OpticalFresnel::execute(*mySample, kvec, coeffs);

            m_coeffs->currentValue() = coeffs;

            ++index;
        } // alpha_i

        Draw(mySample);

        delete mySample;
        delete m_coeffs;
    } // i_sample

}


void TestFresnelCoeff::Draw(const MultiLayer *sample)
{
    static int ncall = 0;
    //size_t nlayers = data.front().coeffs.size();
    size_t nlayers = sample->getNumberOfLayers();

    // creation of graphics to plot R,T coefficients in layers as a function of alpha_i
    std::vector<TGraph *> gr_absR;
    std::vector<TGraph *> gr_absT;
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
      gr_absR.push_back(new TGraph() );
      gr_absT.push_back(new TGraph() );
    }
    TGraph *gr_absSum = new TGraph(); // |R_top|+|T_bottom|

    MultiIndex& index = m_coeffs->getIndex();
    index.reset();
    NamedVector<double> *alpha_axis = dynamic_cast<NamedVector<double>*>(m_coeffs->getAxis("alpha_axis"));
    int i_point = 0;
    while (!index.endPassed())
    {
        size_t index_alpha = index.getCoordinate("alpha_axis");
        double alpha_i = (*alpha_axis)[index_alpha];
        OpticalFresnel::MultiLayerCoeff_t coeffs = m_coeffs->currentValue();

        // Filling graphics for R,T as a function of alpha_i
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            gr_absR[i_layer]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].R) );
            gr_absT[i_layer]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].T) );
            //std::cout << Units::rad2deg(alpha_i) << " l:" << i_layer << " R:" <<  std::abs(coeffs[i_layer].R) << "T:" << std::abs(coeffs[i_layer].T) << std::endl;
        }

        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
        int nlast = nlayers - 1;
        complex_t nx = sample->getLayer(nlast)->getRefractiveIndex();
        complex_t n1 = sample->getLayer(0)->getRefractiveIndex();
        //std::complex<double> kk = (1./(n1*std::sin(theta_i)))*std::sqrt(std::pow(nx,2)-cos(theta_i)*cos(theta_i)*std::pow(n1,2));
        complex_t kk = std::sqrt((complex_t(1,0) - cos(alpha_i)*cos(alpha_i)/nx/nx) ) / sin(alpha_i);
        double sum = std::norm(coeffs[0].R) + std::abs(kk)*std::norm(coeffs[nlast].T);
        // calculation for sum is not valid, when outgoing angle in the bottom layer is parallel to the surfaced
        double alpha_bottom = std::abs(n1/nx)*cos(alpha_i);
        if(1-alpha_bottom < 0.0) sum = std::norm(coeffs[0].R);

        gr_absSum->SetPoint(i_point, Units::rad2deg(alpha_i), sum);

        ++i_point;
        ++index;
    }

    // create name of canvas different for each new call of this method
    std::ostringstream os;
    os << (ncall++) << std::endl;
    std::string cname = std::string("c1_test_fresnel")+os.str();

    TCanvas *c1 = new TCanvas(cname.c_str(),"Fresnel Coefficients in Multilayer",1024,768);
    //DrawHelper::instance().SetMagnifier(c1);

    int ndivy = sqrt(nlayers);
    int ndivx = nlayers/ndivy + 1;
    //c1->Divide(ndivx, ndivy);
    c1->Divide(2,2);

    TH1F *h1ref = new TH1F("h1ref","h1ref",100,0.0,2.0);
    h1ref->SetMinimum(0.01);
    h1ref->SetMaximum(3.0);
    h1ref->SetStats(0);
    h1ref->SetTitle("");
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
      c1->cd(i_layer+1);
      //gPad->SetLogy();
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
      double xmin, ymin, xmax, ymax;
      gr->ComputeRange(xmin, ymin, xmax, ymax);
      std::cout << i_layer << " xmin:" << xmin << " ymin:" << ymin << " xmax:" << xmax << " ymax:" << ymax << std::endl;
    }
    TGraph *gr = gr_absSum;
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(0.2);
    gr->SetLineColor(kMagenta);
    gr->SetMarkerColor(kMagenta);
    gr->Draw("pl same");

}



///* ****************************************************************************
//Creates some multilayer system, runs calculation of Fresnel R,T coefficients for
//all layers, makes plots.
//**************************************************************************** */
//void TestFresnelCoeff::execute()
//{
//    std::cout << "TestFresnelCoeff::execute() -> Info." << std::endl;

//    size_t nsamples = SampleFactory::instance().getNumberOfSamples();

//     MultiLayer *mySample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createStandard(0));
//     const size_t npoints = 101.;
//     double alphaMin(0), alphaMax(2.0*Units::degree);

//     MyDataSet_t myDataSet;
//     for(size_t i=1; i<npoints; i++) {
//        double alpha_i = alphaMin + i*(alphaMax-alphaMin)/double(npoints-1);
//        kvector_t kvec;
//        std::cout << " alpha_i:" << alpha_i << std::endl;
//        kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);

//        // calculation
//        OpticalFresnel::MultiLayerCoeff_t coeffs;
//        OpticalFresnel::execute(*mySample, kvec, coeffs);

//        // saving data for later drawing
//        MyData myData;
//        myData.alpha_i = alpha_i;
//        myData.coeffs = coeffs;
//        myDataSet.push_back(myData);
//    }

//    Draw(mySample, myDataSet);
//}


//void TestFresnelCoeff::Draw(const MultiLayer *sample, const MyDataSet_t &data)
//{
//    //size_t nlayers = data.front().coeffs.size();
//    size_t nlayers = sample->getNumberOfLayers();

//    // creation of graphics to plot R,T coefficients in layers as a function of alpha_i
//    std::vector<TGraph *> gr_absR;
//    std::vector<TGraph *> gr_absT;
//    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
//      gr_absR.push_back(new TGraph() );
//      gr_absT.push_back(new TGraph() );
//    }
//    TGraph *gr_absSum = new TGraph(); // |R_top|+|T_bottom|

//    for(size_t i_point=0; i_point<data.size(); ++i_point) {
//        double alpha_i = data[i_point].alpha_i;
//        // Filling graphics for R,T as a function of alpha_i
//        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
//            std::cout << i_layer << " " << alpha_i*180./M_PI << " R:"  << data[i_point].coeffs[i_layer].R << " " << std::abs(data[i_point].coeffs[i_layer].R)
//                      << " T:" << data[i_point].coeffs[i_layer].T << " " << std::abs(data[i_point].coeffs[i_layer].T) << std::endl;
//            gr_absR[i_layer]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(data[i_point].coeffs[i_layer].R) );
//            gr_absT[i_layer]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(data[i_point].coeffs[i_layer].T) );
//        }
//        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
//        int nlast = nlayers - 1;
//        complex_t nx = sample->getLayer(nlast)->getRefractiveIndex();
//        complex_t n1 = sample->getLayer(0)->getRefractiveIndex();
//        //std::complex<double> kk = (1./(n1*std::sin(theta_i)))*std::sqrt(std::pow(nx,2)-cos(theta_i)*cos(theta_i)*std::pow(n1,2));
//        complex_t kk = std::sqrt((complex_t(1,0) - cos(alpha_i)*cos(alpha_i)/nx/nx) ) / sin(alpha_i);
//        double sum = std::norm(data[i_point].coeffs[0].R) + std::abs(kk)*std::norm(data[i_point].coeffs[nlast].T);
//        // calculation for sum is not valid, when outgoing angle in the bottom layer is parallel to the surfaced
//        double alpha_bottom = std::abs(n1/nx)*cos(alpha_i);
//        if(1-alpha_bottom < 0.0) sum = std::norm(data[i_point].coeffs[0].R);

//        gr_absSum->SetPoint(i_point, Units::rad2deg(alpha_i), sum);
//    }

//    TCanvas *c1 = new TCanvas("c1_test_fresnel","Fresnel Coefficients in Multilayer",1024,768);
//    DrawHelper &drawHelper = DrawHelper::instance();
//    drawHelper.SetMagnifier(c1);

//    int ndivy = sqrt(nlayers);
//    int ndivx = nlayers/ndivy + 1;
//    c1->Divide(ndivx, ndivy);
//    //c1->Divide(2,2);

//    TH1F *h1ref = new TH1F("h1ref","h1ref",100,0.0,2.0);
//    h1ref->SetMinimum(0.01);
//    h1ref->SetMaximum(3.0);
//    h1ref->SetStats(0);
//    h1ref->SetTitle("");
//    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
//      c1->cd(i_layer+1); gPad->SetLogy();
//      h1ref->Draw();

//      TGraph *gr = gr_absR[i_layer];
//      gr->SetLineColor(kBlue);
//      gr->SetMarkerColor(kBlue);
//      gr->SetMarkerStyle(21);
//      gr->SetMarkerSize(0.2);
//      gr->Draw("pl same");

//      gr = gr_absT[i_layer];
//      gr->SetMarkerStyle(21);
//      gr->SetMarkerSize(0.2);
//      gr->SetLineColor(kRed);
//      gr->SetMarkerColor(kRed);
//      gr->Draw("pl same");
//      double xmin, ymin, xmax, ymax;
//      gr->ComputeRange(xmin, ymin, xmax, ymax);
//      std::cout << i_layer << " xmin:" << xmin << " ymin:" << ymin << " xmax:" << xmax << " ymax:" << ymax << std::endl;
//    }
//    TGraph *gr = gr_absSum;
//    gr->SetMarkerStyle(21);
//    gr->SetMarkerSize(0.2);
//    gr->SetLineColor(kMagenta);
//    gr->SetMarkerColor(kMagenta);
//    gr->Draw("pl same");

//}




#include "TestFresnelCoeff.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "HomogeneousMaterial.h"
#include "Exceptions.h"
#include "OpticalFresnel.h"
#include "DrawHelper.h"
#include "SampleFactory.h"
#include "Units.h"
#include "OutputData.h"
#include "Numeric.h"
#include "ICompositeIterator.h"
#include "MaterialManager.h"
#include "TStyle.h"

#include <iostream>
#include <sstream>

#include <iomanip>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TLatex.h"
#include "TLegend.h"
#include "FitMultiParameter.h"


TestFresnelCoeff::TestFresnelCoeff()
{
    std::cout << "TestFresnelCoeff::TestFresnelCoeff() -> Info." << std::endl;
}


/* ************************************************************************* */
//! test fresnel coefficients
/* ************************************************************************* */
void TestFresnelCoeff::execute()
{
    std::cout << "TestFresnelCoeff::execute() -> Info." << std::endl;

    // calculate fresnel coefficients for several standard multi-layer samples
    test_standard_samples();

    // calculate fresnel coefficients for multi-layer with different roughnesses
    test_roughness_set();
}


/* ************************************************************************* */
//! calculate fresnel coefficients .vs. alpha_i for several standard samples
/* ************************************************************************* */
void TestFresnelCoeff::test_standard_samples()
{
    std::vector<std::string > snames;
//    snames.push_back("AirOnSubstrate");
//    snames.push_back("SubstrateOnSubstrate");
//    snames.push_back("SimpleMultilayer");
//    snames.push_back("MultilayerOffspecTestcase2a");
//    snames.push_back("MultilayerOffspecTestcase2b");
    snames.push_back("MultilayerOffspecTestcase1a");

    // loop over standard samples defined in SampleFactory and StandardSamples
    for(size_t i_sample=0; i_sample<snames.size(); i_sample++){
        m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample(snames[i_sample]));

        m_coeffs = new OutputData<OpticalFresnel::MultiLayerCoeff_t >;
        m_coeffs->addAxis(std::string("alpha_i"), 0.0*Units::degree, 2.0*Units::degree, 2000);
        m_coeffs->resetIndex();
        while (m_coeffs->hasNext()) {
            double alpha_i = m_coeffs->getCurrentValueOfAxis<double>("alpha_i");
            kvector_t kvec;
            kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);

            OpticalFresnel::MultiLayerCoeff_t coeffs;
            OpticalFresnel fresnelCalculator;
            fresnelCalculator.execute(*m_sample, kvec, coeffs);

            m_coeffs->next() = coeffs;

        } // alpha_i

        draw_standard_samples();

        delete m_sample;
        delete m_coeffs;
        //break;
    } // i_sample
}


/* ************************************************************************* */
//! draw test results
/* ************************************************************************* */
void TestFresnelCoeff::draw_standard_samples()
{
    static int ncall = 0;

    size_t nlayers = m_sample->getNumberOfLayers();

    // graphics for R,T coefficients in layers as a function of alpha_i
    size_t ncoeffs = 2;
    enum key_coeffs { kCoeffR, kCoeffT};
    const char *coeffs_title[]={" |R| "," |T| "};
    int coeffs_color[] = {kBlue, kRed};

    std::vector<std::vector<TGraph *> > gr_coeff; // [nlayers][ncoeffs]
    gr_coeff.resize(nlayers);
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
        gr_coeff[i_layer].resize(ncoeffs,0);
        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++) {
            gr_coeff[i_layer][i_coeff] = new TGraph();
        }
    }
    TGraph *gr_absSum = new TGraph(); // |R_top|+|T_bottom|

    m_coeffs->resetIndex();
    int i_point = 0;
    while (m_coeffs->hasNext())
    {
        double alpha_i = m_coeffs->getCurrentValueOfAxis<double>("alpha_i");
        OpticalFresnel::MultiLayerCoeff_t coeffs = m_coeffs->next();

        // debug printing
//        size_t index_alpha = i_point;
//        if( index_alpha%100==0 ) {
//            std::cout << "alpha_i: " << index_alpha << " " <<std::setprecision(20) << alpha_i << std::endl;
//            for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
//                std::cout << std::setprecision(12) << " L:" << i_layer
//                          << " kz:" << coeffs[i_layer].kz/10.
//                          << " rt:"
//                          << coeffs[i_layer].r
//                          << coeffs[i_layer].t
//                          << coeffs[i_layer].rb
//                          << coeffs[i_layer].tb
//                          << "X:" << coeffs[i_layer].X
//                          << "R:" << coeffs[i_layer].R
//                          << "T:" << coeffs[i_layer].T
//                          << std::endl;
//                //if(index_alpha%100==0) std::cout << " L:" << i_layer << " R:" << coeffs[i_layer].R << " T:" << coeffs[i_layer].T << std::endl;
//            }
//        }

        // Filling graphics for R,T as a function of alpha_i
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            gr_coeff[i_layer][kCoeffR]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].R) );
            gr_coeff[i_layer][kCoeffT]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].T) );
        }

        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
        int nlast = nlayers - 1;
        double sum;
        if(coeffs[0].kz.real()!=0.0) {
            sum = std::norm(coeffs[0].R) + std::norm(coeffs[nlast].T)*coeffs[nlast].kz.real()/coeffs[0].kz.real();
        } else {
            sum = 1.0;
            std::cout << "Re(k_{z,0}) = 0 for alpha_i = " << alpha_i << std::endl;
            std::cout << " and Re(k_{z,N+1}) = " << coeffs[nlast].kz.real() << std::endl;
        }
        gr_absSum->SetPoint(i_point++, Units::rad2deg(alpha_i), sum);

    }

    // create name of canvas different for each new call of this method
    std::ostringstream os;
    os << (ncall++) << std::endl;
    std::string cname = std::string("c1_test_fresnel_sample")+os.str();
    TCanvas *c1 = new TCanvas(cname.c_str(),"Fresnel Coefficients in Multilayer",1024,768);
    DrawHelper::instance().SetMagnifier(c1);

    // estimate subdivision of canvas (we need place for 'nlayers' and for one sample picture)
    int ndiv(2);
    if( nlayers+1 > 4 ) ndiv = int(sqrt(nlayers+1)+1);
    c1->Divide(ndiv,ndiv);

    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
        c1->cd(i_layer+1);
        gPad->SetLogy();

        // calculating histogram limits common for all graphs on given pad
        double xmin(0), ymin(0), xmax(0), ymax(0);
        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++){
            double x1(0), y1(0), x2(0), y2(0);
            gr_coeff[i_layer][kCoeffT]->ComputeRange(x1, y1, x2, y2);
            if(x1 < xmin ) xmin= x1;
            if(x2 > xmax ) xmax = x2;
            if(y1 < ymin ) ymin = y1;
            if(y2 > ymax ) ymax = y2;
        }
        TH1F h1ref("h1ref","h1ref",100, xmin, xmax);
        h1ref.SetMinimum(1e-6);
        h1ref.SetMaximum(10);
        h1ref.SetStats(0);
        h1ref.SetTitle("");
        h1ref.GetXaxis()->SetTitle("angle, deg");
        h1ref.GetYaxis()->SetTitle("|R|, |T|");
        h1ref.DrawCopy();

        TLegend *leg = new TLegend(0.725,0.7,0.89,0.88);
        leg->SetTextSize(0.04);
        leg->SetBorderSize(1);
        leg->SetFillStyle(0);
        std::ostringstream os;
        os << " layer #" << i_layer;
        leg->SetHeader(os.str().c_str());

        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++) {
            TGraph *gr = gr_coeff[i_layer][i_coeff];
            gr->SetLineColor( coeffs_color[i_coeff] );
            gr->SetMarkerColor( coeffs_color[i_coeff] );
            gr->SetMarkerStyle(21);
            gr->SetMarkerSize(0.2);
            gr->Draw("pl same");
            leg->AddEntry(gr, coeffs_title[i_coeff],"pl");
        }
        leg->Draw();
    }
    TGraph *gr = gr_absSum;
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(0.2);
    gr->SetLineColor(kMagenta);
    gr->SetMarkerColor(kMagenta);
    gr->Draw("pl same");
    TLegend *leg = new TLegend(0.625,0.6,0.89,0.69);
    leg->SetTextSize(0.04);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(gr, "|R_top|+|T_bottom|","pl");
    leg->Draw();

    // drawing sample geometry
    c1->cd(nlayers+1);
    DrawHelper::instance().DrawMultilayer(m_sample);
}



/* ************************************************************************* */
//! calculate fresnel coefficients .vs. alpha_i for set of roughnesses
/* ************************************************************************* */
void TestFresnelCoeff::test_roughness_set()
{
    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MultilayerOffspecTestcase1a"));
//    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("SubstrateOnSubstrate"));

    std::cout << *m_sample << std::endl;
    std::cout << "-----" << std::endl;
    ParameterPool *newpool = m_sample->createParameterTree();
    std::cout << *newpool << std::endl;

//    std::cout << "-----" << std::endl;
    FitMultiParameter multipar;
//    double x = 9.0;
//    FitMultiParameter::parameter_t p(&x);
//    std::cout << p  << " " << &x << std::endl;
//    multipar.addParameter(p);

//    multipar.addMatchedParametersFromPool("/multilayer/interface0/roughness/sigma",newpool);
    multipar.addMatchedParametersFromPool("/*/*/*/sigma",newpool);
    std::cout << "multipar: " << multipar << std::endl;
//    multipar.setValue(0.0);

    std::cout << *m_sample << std::endl;

    m_coeffs = new OutputData<OpticalFresnel::MultiLayerCoeff_t >;
    m_coeffs->addAxis(std::string("alpha_i"), 0.0*Units::degree, 2.0*Units::degree, 1000);
    m_coeffs->addAxis(std::string("roughness"), 0.0, 12.0*Units::nanometer, 6);
    m_coeffs->resetIndex();
    while (m_coeffs->hasNext()) {
        double alpha_i = m_coeffs->getCurrentValueOfAxis<double>("alpha_i");
        double roughness = m_coeffs->getCurrentValueOfAxis<double>("roughness");
        multipar.setValue(roughness);

        kvector_t kvec;
        kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        OpticalFresnel fresnelCalculator;
        fresnelCalculator.execute(*m_sample, kvec, coeffs);
        m_coeffs->next() = coeffs;
        //std::cout << alpha_i << " " << roughness << " " << coeffs[0].R << std::endl;
    }

    draw_roughness_set();

}



/* ************************************************************************* */
//! draw test results
/* ************************************************************************* */
void TestFresnelCoeff::draw_roughness_set()
{
    static int ncall = 0;

    size_t nlayers = m_sample->getNumberOfLayers();

    // graphics for R,T coefficients in layers as a function of alpha_i
    size_t ncoeffs = 2;
    enum key_coeffs { kCoeffR, kCoeffT};

    m_coeffs->resetIndex();
    MultiIndex& index = m_coeffs->getIndex();
    //NamedVector<double> *p_alpha = dynamic_cast<NamedVector<double>*>(m_coeffs->getAxis("alpha_i"));
    const NamedVector<double> *p_rough = dynamic_cast<const NamedVector<double>*>(m_coeffs->getAxis("roughness"));
    size_t nroughness = p_rough->getSize();


    std::vector<std::vector<std::vector<TGraph *> > > gr_coeff; // [nlayers][ncoeffs][nroughness]
    gr_coeff.resize(nlayers);
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
        gr_coeff[i_layer].resize(ncoeffs);
        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++) {
            gr_coeff[i_layer][i_coeff].resize(nroughness,0);
            for(size_t i_rough =0; i_rough<nroughness; i_rough++){
                gr_coeff[i_layer][i_coeff][i_rough] = new TGraph();
            }
        }
    }
//    TGraph *gr_absSum = new TGraph(); // |R_top|+|T_bottom|


    while (!index.endPassed())
    {
        double alpha_i = m_coeffs->getCurrentValueOfAxis<double>("alpha_i");
        //double roughness = m_coeffs->getCurrentValueOfAxis<double>("roughness");
        size_t i_alpha = index.getCurrentIndexOfAxis("alpha_i");
        size_t i_rough = index.getCurrentIndexOfAxis("roughness");

        OpticalFresnel::MultiLayerCoeff_t coeffs = m_coeffs->currentValue();

        // Filling graphics for R,T as a function of alpha_i
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            gr_coeff[i_layer][kCoeffR][i_rough]->SetPoint(i_alpha, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].R) );
            gr_coeff[i_layer][kCoeffT][i_rough]->SetPoint(i_alpha, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].T) );
        }

//        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
//        int nlast = nlayers - 1;
//        double sum;
//        if(coeffs[0].kz.real()!=0.0) {
//            sum = std::norm(coeffs[0].R) + std::norm(coeffs[nlast].T)*coeffs[nlast].kz.real()/coeffs[0].kz.real();
//        } else {
//            sum = 1.0;
//            std::cout << "Re(k_{z,0}) = 0 for alpha_i = " << alpha_i << std::endl;
//            std::cout << " and Re(k_{z,N+1}) = " << coeffs[nlast].kz.real() << std::endl;
//        }
//        gr_absSum->SetPoint(i_point++, Units::rad2deg(alpha_i), sum);
        ++index;
    }

    // create name of canvas different for each new call of this method
    std::ostringstream os;
    os << (ncall++) << std::endl;
    std::string cname = std::string("c1_test_fresnel_roughness")+os.str();
    TCanvas *c1 = new TCanvas(cname.c_str(),"Fresnel Coefficients in Multilayer",1024,768);
    DrawHelper::instance().SetMagnifier(c1);

    // estimate subdivision of canvas (we need place for 'nlayers' and for one sample picture)
    int ndiv(2);
    if( nlayers+1 > 4 ) ndiv = int(sqrt(nlayers+1)+1);
    c1->Divide(ndiv,ndiv);

    int i_coeff_sel = kCoeffR;
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
        c1->cd(i_layer+1);
        gPad->SetLogy();

        // calculating histogram limits common for all graphs on given pad
        double xmin(0), ymin(0), xmax(0), ymax(0);
        for(size_t i_rough=0; i_rough<nroughness; i_rough++){
            double x1(0), y1(0), x2(0), y2(0);
            gr_coeff[i_layer][i_coeff_sel][i_rough]->ComputeRange(x1, y1, x2, y2);
            if(x1 < xmin ) xmin= x1;
            if(x2 > xmax ) xmax = x2;
            if(y1 < ymin ) ymin = y1;
            if(y2 > ymax ) ymax = y2;
        }
        TH1F h1ref("h1ref","h1ref",100, xmin, xmax);
        h1ref.SetMinimum(1e-6);
        h1ref.SetMaximum(10);
        h1ref.SetStats(0);
        h1ref.SetTitle("");
        h1ref.GetXaxis()->SetTitle("angle, deg");
        h1ref.GetYaxis()->SetTitle("|R|, |T|");
        h1ref.DrawCopy();

//        TLegend *leg = new TLegend(0.725,0.7,0.89,0.88);
        TLegend *leg = new TLegend(0.18,0.20,0.28,0.69);
        leg->SetTextSize(0.04);
        leg->SetBorderSize(1);
        leg->SetFillStyle(0);
        std::ostringstream os;
        os << " layer #" << i_layer;
        leg->SetHeader(os.str().c_str());

        for(size_t i_rough=0; i_rough<nroughness; i_rough++) {
            TGraph *gr = gr_coeff[i_layer][i_coeff_sel][i_rough];
            gr->SetLineColor( i_rough+1 );
            gr->SetMarkerColor(  i_rough+1 );
            gr->SetMarkerStyle(21);
            gr->SetMarkerSize(0.2);
            gr->Draw("pl same");
            std::ostringstream os;
            os << "rgh " << i_rough;
            leg->AddEntry(gr, os.str().c_str(),"pl");
        }
        leg->Draw();
    }
////    TGraph *gr = gr_absSum;
////    gr->SetMarkerStyle(21);
////    gr->SetMarkerSize(0.2);
////    gr->SetLineColor(kMagenta);
////    gr->SetMarkerColor(kMagenta);
////    gr->Draw("pl same");
//    TLegend *leg = new TLegend(0.625,0.6,0.89,0.69);
//    leg->SetTextSize(0.04);
//    leg->SetBorderSize(0);
//    leg->SetFillStyle(0);
//    leg->AddEntry(gr, "|R_top|+|T_bottom|","pl");
//    leg->Draw();

    // drawing sample geometry
    c1->cd(nlayers+1);
    DrawHelper::instance().DrawMultilayer(m_sample);
}


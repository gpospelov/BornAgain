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

#include <iostream>
#include <iomanip>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TApplication.h"
#include "TLatex.h"
#include "TLegend.h"



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

    std::vector<std::string > snames;
    snames.push_back("AirOnSubstrate");
    snames.push_back("SubstrateOnSubstrate");
    snames.push_back("SimpleMultilayer");

    // loop over standard samples defined in SampleFactory and StandardSamples
    for(size_t i_sample=0; i_sample<snames.size(); i_sample++){
        m_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem(snames[i_sample]));

        m_coeffs = new OutputData<OpticalFresnel::MultiLayerCoeff_t >;

        m_coeffs->addAxis(std::string("alpha_i"), 0.0*Units::degree, 2.0*Units::degree, 1024);

        m_coeffs->resetIndex();
        while (m_coeffs->hasNext())
        {
            double alpha_i = m_coeffs->getCurrentValueOfAxis<double>("alpha_i");
            kvector_t kvec = kvector_t::LambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);

            OpticalFresnel::MultiLayerCoeff_t coeffs;
            OpticalFresnel::execute(*m_sample, kvec, coeffs);

            m_coeffs->next() = coeffs;

        } // alpha_i

        draw();

        delete m_sample;
        delete m_coeffs;
        //break;
    } // i_sample
}

//void TestFresnelCoeff::execute()
//{
//    std::cout << "TestFresnelCoeff::execute() -> Info." << std::endl;
//
//    m_sample =
//            dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem(2));
//
//    m_coeffs = new OutputData<OpticalFresnel::MultiLayerCoeff_t>;
//
//    NamedVector<double> *alpha_axis = new NamedVector<double>(
//            std::string("alpha_i"), 0.0 * Units::degree,
//            2.0 * Units::degree, 3);
//    m_coeffs->addAxis(alpha_axis);
//
//    MultiIndex &index = m_coeffs->getIndex();
//    while (!index.endPassed())
//    {
//        size_t index_y = index.getCoordinate("alpha_i");
//        double alpha_i = (*alpha_axis)[index_y];
//        kvector_t kvec = kvector_t::LambdaAlphaPhi(0.04 * Units::angstrom,
//                -alpha_i, 0.0);
//
//        OpticalFresnel::MultiLayerCoeff_t coeffs;
//        OpticalFresnel::execute(*m_sample, kvec, coeffs);
//
//        m_coeffs->currentValue() = coeffs;
//
//        ++index;
//    } // alpha_i
//
//    draw();
//
//    delete m_sample;
//    delete m_coeffs;
//}



/* ************************************************************************* */
//! drawing fresnel coefficients in a layer as a function of alpha
/* ************************************************************************* */
void TestFresnelCoeff::draw()
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

        // Filling graphics for R,T as a function of alpha_i
        //if(index_alpha%100==0) std::cout << "alpha_i: " << index_alpha << " " <<std::setprecision(12) << alpha_i << std::endl;
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            gr_coeff[i_layer][kCoeffR]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].R) );
            gr_coeff[i_layer][kCoeffT]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].T) );
            //if(index_alpha%100==0) std::cout << " L:" << i_layer << " R:" << coeffs[i_layer].R << " T:" << coeffs[i_layer].T << std::endl;
        }

        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
        int nlast = nlayers - 1;
        double sum;
        if(coeffs[0].kz.real()!=0.0) {
            sum = std::norm(coeffs[0].R) + std::norm(coeffs[nlast].T)*coeffs[nlast].kz.real()/coeffs[0].kz.real();
        }
        else {
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




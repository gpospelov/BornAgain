#include "TestDiffuseReflection.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DWBADiffuseReflection.h"
#include "OutputData.h"

#include <iostream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TApplication.h"
#include "TStyle.h"




TestDiffuseReflection::TestDiffuseReflection()
{

}


void TestDiffuseReflection::execute()
{
    std::cout << "TestDiffuseScattering::execute() -> Info." << std::endl;

    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("MultilayerWithRoughness"));

    const size_t npoints = 101.;
    double alphaMin(0.0*Units::degree), alphaMax(2.*Units::degree);
    double dalpha = (alphaMax - alphaMin) / (npoints-1);

    TH2F *h2 = new TH2F("h2","h2", npoints, alphaMin-dalpha/2., alphaMax+dalpha/2., npoints, alphaMin-dalpha/2., alphaMax+dalpha/2.);
    h2->SetContour(50);
    h2->SetMinimum(0.001);
    TGraph *gr = new TGraph(npoints);

    OutputData<double > *m_data = new OutputData<double >;
    kvector_t ki;
    kvector_t kf;

    // alpha_i = alpha_f
    m_data->addAxis(std::string("alpha_i"), alphaMin, alphaMax, npoints);
    m_data->resetIndex();
    while (m_data->hasNext()) {
        double alpha_i = m_data->getCurrentValueOfAxis<double>("alpha_i");

        ki.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
        kf.setLambdaAlphaPhi(1.54*Units::angstrom, alpha_i, 0.0);

        double cs = DWBADiffuseReflection::execute(*m_sample, ki, kf);
        gr->SetPoint(m_data->getCoordinate("alpha_i"), alpha_i, cs);

        m_data->next();
    }

    // off specular
    m_data->addAxis(std::string("alpha_f"), alphaMin, alphaMax, npoints);
    m_data->resetIndex();
    while (m_data->hasNext()) {
        double alpha_i = m_data->getCurrentValueOfAxis<double>("alpha_i");
        double alpha_f = m_data->getCurrentValueOfAxis<double>("alpha_f");

        ki.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
        kf.setLambdaAlphaPhi(1.54*Units::angstrom, alpha_f, 0.0);

        double cs = DWBADiffuseReflection::execute(*m_sample, ki, kf);

        m_data->next() = cs;
        h2->Fill(alpha_i, alpha_f,cs);

    } // alpha_i

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->Divide(2,2);

    c1->cd(1);
    gr->Draw("apl");

    c1->cd(2);
    gPad->SetRightMargin(0.2);
    gStyle->SetPalette(1);
    gPad->SetLogz();
    h2->Draw("CONT4 Z");

    delete m_sample;
    delete m_data;
}


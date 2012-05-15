#include "TestDiffuseReflection.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DWBADiffuseReflection.h"

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

    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("SimpleMultilayer"));


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
            double cs = DWBADiffuseReflection::execute(*m_sample, ki, kf);
            std::cout << " i:" << i << " " << alpha_i << " f:" <<  f << " alpha_f:" << alpha_f << " cs:" << cs << std::endl;
            h2->Fill(alpha_i, alpha_f,cs);
        } // k
    } // i

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd(); gPad->SetRightMargin(0.2);
    gStyle->SetPalette(1);
    gPad->SetLogz();
    h2->Draw("CONT4 Z");

    delete m_sample;
}


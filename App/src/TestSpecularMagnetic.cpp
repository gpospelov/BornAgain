// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestSpecularMagnetic.cpp
//! @brief     Implements class TestSpecularMagnetic.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestSpecularMagnetic.h"

#include "SampleFactory.h"
#include "Units.h"
#include "EigenCore.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "DrawHelper.h"
#include "TH1F.h"
#include "TLegend.h"

TestSpecularMagnetic::TestSpecularMagnetic()
: mp_sample(0)
, mp_coeffs(0)
{
    std::cout << "TestSpecularMagnetic::TestSpecularMagnetic() -> Info."
            << std::endl;
}

void TestSpecularMagnetic::execute()
{
    std::cout << "TestSpecularMagnetic::execute() -> Info." << std::endl;

    // calculate amplitudes for a standard multi-layer sample
    test_standard_sample();
}

void TestSpecularMagnetic::test_standard_sample()
{
    std::vector<std::string > snames;
    snames.push_back("MultilayerSpecularMagneticTestCase");

    // loop over standard samples defined in SampleFactory and StandardSamples
    for(size_t i_sample=0; i_sample<snames.size(); i_sample++){
        mp_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample(
                snames[i_sample]));

        mp_coeffs = new OutputData<SpecularMagnetic::MultiLayerCoeff_t >;
        mp_coeffs->addAxis(std::string("alpha_i"), 2000, 0.0*Units::degree,
                2.0*Units::degree);
        OutputData<SpecularMagnetic::MultiLayerCoeff_t >::iterator it =
                mp_coeffs->begin();
        while (it != mp_coeffs->end()) {
            double alpha_i = mp_coeffs->getAxisValue(it.getIndex(), "alpha_i");
            kvector_t kvec;
            kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);

            SpecularMagnetic::MultiLayerCoeff_t coeffs;
            SpecularMagnetic magneticCalculator;
            magneticCalculator.execute(*mp_sample, kvec, coeffs);

            *it = coeffs;
            ++it;

        } // alpha_i

        draw_standard_sample();

        delete mp_sample;
        delete mp_coeffs;
    } // i_sample
}

void TestSpecularMagnetic::draw_standard_sample()
{
    static int ncall = 0;

    std::vector<TGraph *> gr_coeff; // different polarization combinations
    gr_coeff.resize(4);
    for(size_t i=0; i<4; ++i) {
        gr_coeff[i] = new TGraph();
    }

    OutputData<SpecularMagnetic::MultiLayerCoeff_t >::const_iterator it =
            mp_coeffs->begin();
    int i_point = 0;
    while (it != mp_coeffs->end()) {
        double alpha_i = mp_coeffs->getAxisValue(it.getIndex(), "alpha_i");
        const SpecularMagnetic::MultiLayerCoeff_t coeffs = *it++;

        // Filling graphics for R coefficients as a function of alpha_i
        Eigen::Vector2cd rp = coeffs[0].R1plus() + coeffs[0].R2plus();
        Eigen::Vector2cd rm = coeffs[0].R1min() + coeffs[0].R2min();
        gr_coeff[0]->SetPoint(i_point, Units::rad2deg(alpha_i),
                std::abs( (complex_t)rp(0) ) );
        gr_coeff[1]->SetPoint(i_point, Units::rad2deg(alpha_i),
                std::abs( (complex_t)rp(1) ) );
        gr_coeff[2]->SetPoint(i_point, Units::rad2deg(alpha_i),
                std::abs( (complex_t)rm(0) ) );
        gr_coeff[3]->SetPoint(i_point++, Units::rad2deg(alpha_i),
                std::abs( (complex_t)rm(1) ) );
    }

    // create name of canvas different for each new call of this method
    std::ostringstream os;
    os << (ncall++) << std::endl;
    std::string cname = std::string("c1_test_specular_magnetic")+os.str();
    TCanvas *c1 = new TCanvas(cname.c_str(),
            "Reflection/transmission Coefficients in Magnetic Multilayer",
            1024,768);
    DrawHelper::SetMagnifier(c1);

    // create subdivision of canvas
    int ndiv(2);
    c1->Divide(ndiv,ndiv);

    for(size_t i=0; i<4; ++i) {
        c1->cd((int)i+1);
        gPad->SetLogy();

        // calculating histogram limits common for all graphs on given pad
        double xmin(0), ymin(0), xmax(0), ymax(0);
        gr_coeff[i]->ComputeRange(xmin, ymin, xmax, ymax);
        TH1F h1ref("h1ref","h1ref",100, xmin, xmax);
        h1ref.SetMinimum(1e-6);
        h1ref.SetMaximum(10);
        h1ref.SetStats(0);
        h1ref.SetTitle("");
        h1ref.GetXaxis()->SetTitle("angle, deg");
        h1ref.GetYaxis()->SetTitle("|R|");
        h1ref.DrawCopy();

        TGraph *gr = gr_coeff[i];
        gr->SetLineColor( kBlue );
        gr->SetMarkerColor( kBlue );
        gr->SetMarkerStyle(21);
        gr->SetMarkerSize(0.2);
        gr->Draw("pl same");
    }
}

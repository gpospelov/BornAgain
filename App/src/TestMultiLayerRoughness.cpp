// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestMultiLayerRoughness.cpp
//! @brief     Implements TestMultiLayerRoughness.execute().
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestMultiLayerRoughness.h"
#include "BornAgainNamespace.h"
#include "GISASSimulation.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "SampleFactory.h"
#include "OutputData.h"

#include "TCanvas.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TStyle.h"


void TestMultiLayerRoughness::execute()
{
    ISample *sample = SampleFactory::createSample("MultilayerOffspecTestcase1a");

    std::cout << *sample << std::endl;
    sample->printSampleTree();

    int npoints=100;
    double alphaMax = 2.0;
    double alphaMin = 0.0;
    double dalpha = (alphaMax-alphaMin)/double(npoints-1);
    TH2D *h2 = new TH2D ("h2","h2", npoints, alphaMin-dalpha/2., alphaMax+dalpha/2., npoints, alphaMin-dalpha/2., alphaMax+dalpha/2. );
    h2->SetContour(50);

    OutputData<double> *p_data_alpha_i = new OutputData<double>();
    p_data_alpha_i->addAxis(std::string("alpha_i"), npoints, 0.0*Units::degree, 2.0*Units::degree);
    OutputData<double>::const_iterator it_alpha_i = p_data_alpha_i->begin();
    while (it_alpha_i != p_data_alpha_i->end()) {
        double alpha_i = p_data_alpha_i->getAxisValue(it_alpha_i.getIndex(), "alpha_i");
        size_t index_alpha_i = p_data_alpha_i->getAxisValue(it_alpha_i.getIndex(), "alpha_i");
        if(index_alpha_i%10 == 0) std::cout << index_alpha_i << " of " << npoints << std::endl;

        // setting simulation
        GISASSimulation simulation(mp_options);
        simulation.setSample(*sample);
        simulation.setDetectorParameters(2, 0.0*Units::degree, 0.00001*Units::degree, npoints, 0.0*Units::degree, 2.0*Units::degree);
        simulation.setBeamParameters(1.54*Units::angstrom, alpha_i, 0.0*Units::degree);

        simulation.runSimulation();

        const OutputData<double> *output = simulation.getOutputData();
        OutputData<double>::const_iterator it_output = output->begin();
        while (it_output != output->end()) {
            double phi_f = output->getAxisValue(it_output.getIndex(), BornAgain::PHI_AXIS_NAME);
            double alpha_f = output->getAxisValue(it_output.getIndex(), BornAgain::ALPHA_AXIS_NAME);
            double intensity = *it_output++;
            if(phi_f == 0) {
                h2->Fill(Units::rad2deg(alpha_i), Units::rad2deg(alpha_f), intensity);
            }
        }
        ++it_alpha_i;
    }

    gStyle->SetPalette(1);
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd(); gPad->SetLogz(); gPad->SetRightMargin(0.2);
    //h2->Draw("CONT4 Z");
    h2->Draw("colz");
}



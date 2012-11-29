#include "TestMultiLayerRoughness.h"
#include "GISASExperiment.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "SampleFactory.h"
#include "OutputData.h"

#include "TCanvas.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TStyle.h"

TestMultiLayerRoughness::TestMultiLayerRoughness()
{

}




void TestMultiLayerRoughness::execute()
{

    ISample *sample = SampleFactory::instance().createItem("MultilayerOffspecTestcase1a");

    std::cout << *sample << std::endl;
    sample->print_structure();

    int npoints=100;
    double alphaMax = 2.0;
    double alphaMin = 0.0;
    double dalpha = (alphaMax-alphaMin)/double(npoints-1);
    TH2D *h2 = new TH2D ("h2","h2", npoints, alphaMin-dalpha/2., alphaMax+dalpha/2., npoints, alphaMin-dalpha/2., alphaMax+dalpha/2. );
    h2->SetContour(50);

    OutputData<double> *p_data_alpha_i = new OutputData<double>();
    p_data_alpha_i->addAxis(std::string("alpha_i"), 0.0*Units::degree, 2.0*Units::degree, npoints);
    OutputData<double>::const_iterator it_alpha_i = p_data_alpha_i->begin();
    while (it_alpha_i != p_data_alpha_i->end()) {
        double alpha_i = p_data_alpha_i->getValueOfAxis<double>("alpha_i", it_alpha_i.getIndex());
        size_t index_alpha_i = p_data_alpha_i->getIndexOfAxis("alpha_i", it_alpha_i.getIndex());
        if(index_alpha_i%10 == 0) std::cout << index_alpha_i << " of " << npoints << std::endl;

        // setting experiment
        GISASExperiment experiment(mp_options);
        experiment.setSample(*sample);
        experiment.setDetectorParameters(2, 0.0*Units::degree, 0.00001*Units::degree, npoints, 0.0*Units::degree, 2.0*Units::degree, false);
        experiment.setBeamParameters(1.54*Units::angstrom, -alpha_i, 0.0*Units::degree);

        experiment.runSimulation();

        const OutputData<double> *output = experiment.getOutputData();
        OutputData<double>::const_iterator it_output = output->begin();
        while (it_output != output->end()) {
            double phi_f = output->getValueOfAxis<double>("phi_f", it_output.getIndex());
            double alpha_f = output->getValueOfAxis<double>("alpha_f", it_output.getIndex());
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

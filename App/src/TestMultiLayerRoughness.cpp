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
    sample->walk_and_print();

    int npoints=101;
    double alphaMax = 2.0;
    double alphaMin = 0.0;
    double dalpha = (alphaMax-alphaMin)/double(npoints-1);
    TH2D *h2 = new TH2D ("h2","h2", npoints, alphaMin-dalpha/2., alphaMax+dalpha/2., npoints, alphaMin-dalpha/2., alphaMax+dalpha/2. );
    h2->SetContour(50);

    OutputData<double > *data_alpha_i = new OutputData<double >;
    data_alpha_i->addAxis(std::string("alpha_i"), 0.0*Units::degree, 2.0*Units::degree, npoints);
    data_alpha_i->resetIndex();
    while (data_alpha_i->hasNext()) {
        double alpha_i = data_alpha_i->getCurrentValueOfAxis<double>("alpha_i");
        size_t index_alpha_i = data_alpha_i->getCurrentIndexOfAxis("alpha_i");
        //alpha_i = 0.2*Units::degree;
        if(index_alpha_i%10 == 0) std::cout << index_alpha_i << " of " << npoints << std::endl;

        // setting experiment
        GISASExperiment experiment;
        experiment.setDetectorParameters(2, 0.0*Units::degree, 0.00001*Units::degree, npoints, 0.0*Units::degree, 2.0*Units::degree, false);
        experiment.setBeamParameters(1.54*Units::angstrom, -alpha_i, 0.0*Units::degree);
        experiment.setSample(sample);
        experiment.runSimulation();

        const OutputData<double> *output = experiment.getOutputData();
        output->resetIndex();
        while (output->hasNext()) {
            double phi_f = output->getCurrentValueOfAxis<double>("phi_f");
            double alpha_f = output->getCurrentValueOfAxis<double>("alpha_f");
            //size_t index_phi = output->getCurrentIndexOfAxis("phi_f");
            double intensity = output->next();
            //std::cout << "alpha_i " << alpha_i << " alpha_f " << alpha_f << " phi_f " << phi_f << " inten " << intensity << std::endl;
            if(phi_f == 0) {
                h2->Fill(Units::rad2deg(alpha_i), Units::rad2deg(alpha_f), intensity);
            }
        }

        data_alpha_i->next();
    }

    gStyle->SetPalette(1);
    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd(); gPad->SetLogz(); gPad->SetRightMargin(0.2);
    //h2->Draw("CONT4 Z");
    h2->Draw("colz");
}

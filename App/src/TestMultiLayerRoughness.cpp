#include "TestMultiLayerRoughness.h"
#include "GISASExperiment.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "SampleFactory.h"

#include "TCanvas.h"

TestMultiLayerRoughness::TestMultiLayerRoughness()
{

}




void TestMultiLayerRoughness::execute()
{

//    std::vector<std::string > snames;
//    snames.push_back("MultilayerOffspecTestcase1a");
//    snames.push_back("MultilayerOffspecTestcase1b");
////    snames.push_back("MultilayerOffspecTestcase2a");
////    snames.push_back("MultilayerOffspecTestcase2b");

//    std::vector<MultiLayer *> samples;
//    for(size_t i_sample=0; i_sample<snames.size(); i_sample++){
//        samples.push_back( dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem(snames[i_sample])) );
//    }


    ISample *sample = SampleFactory::instance().createItem("MultilayerOffspecTestcase1a");

    // setting experiment
    GISASExperiment experiment;
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    experiment.setSample(sample);
    experiment.runSimulation();

    const OutputData<double> *output = experiment.getOutputData();

    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    c1->cd();
    IsGISAXSTools::drawOutputDataInPad(*output, "CONT4 Z", "Calculated pyramid FF");
}

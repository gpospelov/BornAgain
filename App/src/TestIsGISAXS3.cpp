#include "TestIsGISAXS3.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "GISASExperiment.h"
#include "FormFactors.h"
#include "SampleFactory.h"
#include "DrawHelper.h"

#include "TCanvas.h"

void TestIsGISAXS3::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS3_Cylinder"));

    GISASExperiment experiment;
    experiment.setSample(sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();

    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_DWBA.ima");
}


void TestIsGISAXS3::finalise()
{
    std::string isgi_file(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_DWBA.ima");
    std::string this_file(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_DWBA.ima");

    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_file, 10);
    OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_file, 10);

    //TCanvas *c1 = new TCanvas("TestIsGISAXS3_c1", "Cylinder DWBA Formfactor", 1024, 768);
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS3_c1", "Cylinder DWBA Formfactor");
    c1->Divide(2,2);

    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our cylinder FF");

    // isgisaxs data
    c1->cd(2); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs mean FF");

    // difference
    c1->cd(3);
    IsGISAXSTools::setMinimum(-0.0001);
    IsGISAXSTools::setMaximum(0.0001);
    IsGISAXSTools::drawOutputDataDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

    // difference
    c1->cd(4);
    IsGISAXSTools::resetMinimumAndMaximum();
    IsGISAXSTools::setMinimum(1);
    IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

    delete isgi_data;
    delete our_data;

}

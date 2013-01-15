#include "TestIsGISAXS2.h"
#include "GISASExperiment.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "IsGISAXSTools.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"


#include "TCanvas.h"


TestIsGISAXS2::TestIsGISAXS2() : IFunctionalTest("TestIsGISAXS2")
{
    std::cout << "TestIsGISAXS2::TestIsGISAXS2() -> Info" << std::endl;
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-2/");
}


void TestIsGISAXS2::execute()
{
    GISASExperiment experiment(mp_options);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // cylinders of two types
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS2_CylindersMixture"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_bimodal.ima");

}


void TestIsGISAXS2::finalise()
{
    std::string isgi_file(m_data_path+"isgi_bimodal.ima.gz");
    std::string this_file(m_data_path+"this_bimodal.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS2_c1", "Mixture of cylindrical particles with different size distribution");

    c1->Divide(2,2);

    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our mean FF");

    // isgisaxs data
    c1->cd(2); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs mean FF");

    // difference
    c1->cd(3);
    IsGISAXSTools::setMinimum(-0.0001);
    IsGISAXSTools::setMaximum(0.0001);
    IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

    // difference
    c1->cd(4);
    IsGISAXSTools::resetMinimumAndMaximum();
    IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

    delete isgi_data;
    delete our_data;
}

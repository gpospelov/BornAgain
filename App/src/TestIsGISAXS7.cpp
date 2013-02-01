#include "TestIsGISAXS7.h"
#include "TCanvas.h"
#include "Utils.h"
#include "Units.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "IsGISAXSTools.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"


TestIsGISAXS7::TestIsGISAXS7() : IFunctionalTest("TestIsGISAXS7")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-7/");
}

void TestIsGISAXS7::execute()
{
    GISASExperiment experiment(mp_options);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 1.0*Units::degree,
            100, 0.0*Units::degree, 1.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, 0.0*Units::degree, 0.0*Units::degree);
    SimulationParameters sim_params;
    sim_params.me_if_approx = SimulationParameters::ISGISAXSMOR;
    experiment.setSimulationParameters(sim_params);

    MultiLayer *sample = dynamic_cast<MultiLayer *>(
            SampleFactory::instance().createItem("IsGISAXS7_mor"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), m_data_path+"this_morphology.ima");
}

void TestIsGISAXS7::finalise()
{
    std::vector< CompareStruct > tocompare;
     tocompare.push_back( CompareStruct("isgi_morphology.ima.gz", "this_morphology.ima",
             "Morphology file") );

     for(size_t i=0; i<tocompare.size(); ++i) {
         OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].isginame);
         OutputData<double> *our_data = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].thisname);

         std::ostringstream os;
         os<<i;
         std::string cname = getName()+"_c"+os.str();
         TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas(cname.c_str(), tocompare[i].descr);
         c1->Divide(2,2);

         IsGISAXSTools::setMinimum(1.);
         // our calculations
         c1->cd(1); gPad->SetLogz();
         IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our morphology FF");

         // isgisaxs data
         c1->cd(2); gPad->SetLogz();
         IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs morphology FF");

         // difference
         c1->cd(3);
         IsGISAXSTools::setMinimum(-0.0001);
         IsGISAXSTools::setMaximum(0.0001);
         IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

         // difference
         c1->cd(4);
         IsGISAXSTools::resetMinimumAndMaximum();
         //IsGISAXSTools::setMinimum(1);
         IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

         IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
         delete isgi_data;
         delete our_data;
     }
}

#include "TestIsGISAXS6.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "GISASExperiment.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"


#include "TCanvas.h"
#include <gsl/gsl_errno.h>

TestIsGISAXS6::TestIsGISAXS6() : IFunctionalTest("TestIsGISAXS6")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-6/");
}

void TestIsGISAXS6::execute()
{
    gsl_set_error_handler_off();

    GISASExperiment experiment(mp_options);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;

    experiment.setSimulationParameters(sim_params);
    // normal lattice
    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_lattice"));
    experiment.setSample(*p_sample);
    experiment.runSimulation();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), m_data_path+"this_lattice.ima");
    delete p_sample;

//    // centered lattice
//    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_centered"));
//    experiment.setSample(*p_sample);
//    experiment.runSimulation();
//    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), m_data_path+"this_centered.ima");
//    delete p_sample;
//
//    // rotated lattice
//    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_rotated"));
//    experiment.setSample(*p_sample);
//    experiment.runSimulation();
//    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), m_data_path+"this_rotated.ima");
//    delete p_sample;
//
//    // lattice variants
//    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS6_variants"));
//    experiment.setSample(*p_sample);
//    experiment.runSimulation();
//    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), m_data_path+"this_variants.ima");
//    delete p_sample;

}


void TestIsGISAXS6::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgi_lattice.ima.gz",      "this_lattice.ima",      "Cylinder 2D lattice") );
//    tocompare.push_back( CompareStruct("isgi_centered.ima.gz",      "this_centered.ima",      "Cylinder 2D lattice centered") );
//    tocompare.push_back( CompareStruct("isgi_rotated.ima.gz",      "this_rotated.ima",      "Cylinder 2D lattice rotated") );
//    tocompare.push_back( CompareStruct("isgi_variants.ima.gz",      "this_variants.ima",      "Cylinder 2D lattice variants") );

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
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our lattice IF");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs lattice IF");

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

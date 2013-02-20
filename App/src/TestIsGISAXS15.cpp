#include "TestIsGISAXS15.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "Simulation.h"
#include "SampleFactory.h"
#include "DrawHelper.h"

#include "TCanvas.h"
#include <gsl/gsl_errno.h>

TestIsGISAXS15::TestIsGISAXS15() : IFunctionalTest("TestIsGISAXS15")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-15/");
}

void TestIsGISAXS15::execute()
{
    gsl_set_error_handler_off();

    Simulation simulation(mp_options);
    simulation.setDetectorParameters(150, 0.05*Units::degree, 1.5*Units::degree, 150, 0.05*Units::degree, 1.5*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_if_approx = SimulationParameters::SSCA;
    simulation.setSimulationParameters(sim_params);

    // create sample and run simulation
    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS15_SSCA"));
    simulation.setSample(*p_sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), m_data_path+"this_SSCA.ima");
    delete p_sample;
}


void TestIsGISAXS15::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgi_SSCA.ima",      "this_SSCA.ima",      "SSCA Cylinders") );

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData( m_data_path+tocompare[i].isginame );
        OutputData<double> *our_data = OutputDataIOFactory::getOutputData( m_data_path+tocompare[i].thisname );

        std::ostringstream os;
        os<<i;
        std::string cname = getName()+"_c"+os.str();
        TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas(cname.c_str(), tocompare[i].descr);
        c1->Divide(2,2);

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our cylinder SSCA");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs cylinder SSCA");

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

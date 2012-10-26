#include "TestIsGISAXS4.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "GISASExperiment.h"
#include "SampleFactory.h"
#include "DrawHelper.h"

#include "TCanvas.h"
#include <gsl/gsl_errno.h>

TestIsGISAXS4::TestIsGISAXS4() : IFunctionalTest("TestIsGISAXS4")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-4/");
}

void TestIsGISAXS4::execute()
{
    gsl_set_error_handler_off();

    GISASExperiment experiment(mp_options);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    MultiLayer *p_sample(0);

//    // 1DDL
    p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS4_1DDL"));
    experiment.setSample(*p_sample);
    experiment.runSimulation();
    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_1DDL.ima");
    delete p_sample;

    // 2DDL
    p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS4_2DDL"));
    experiment.setSample(*p_sample);
    experiment.runSimulation();
    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_2DDLh.ima");
    delete p_sample;
}


void TestIsGISAXS4::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgi_1DDL.ima",      "this_1DDL.ima",      "Cylinder 1DDL") );
    tocompare.push_back( CompareStruct("isgi_2DDLh.ima",      "this_2DDLh.ima",      "Cylinder 2DDL") );

    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile( m_data_path+tocompare[i].isginame );
        OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile( m_data_path+tocompare[i].thisname );

        std::ostringstream os;
        os<<i;
        std::string cname = getName()+"_c"+os.str();
        TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas(cname.c_str(), tocompare[i].descr);
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

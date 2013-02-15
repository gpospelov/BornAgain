#include "TestIsGISAXS8.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "Simulation.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"


#include "TCanvas.h"
#include <gsl/gsl_errno.h>

TestIsGISAXS8::TestIsGISAXS8() : IFunctionalTest("TestIsGISAXS8")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-8/");
}

void TestIsGISAXS8::execute()
{
    Simulation simulation(mp_options);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // 2DDL_lattice
    MultiLayer *p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS8_2DDL_lattice"));
    simulation.setSample(*p_sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), m_data_path+"this_2DDL_lattice.ima");
    delete p_sample;

    // 2DDL_lattice with isotropic pdfs
    p_sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS8_2DDL_lattice2"));
    simulation.setSample(*p_sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), m_data_path+"this_2DDL_lattice2.ima");
    delete p_sample;
}


void TestIsGISAXS8::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgi_2DDL_lattice.ima.gz",      "this_2DDL_lattice.ima",      "Cylinder 2DDL lattice") );
    tocompare.push_back( CompareStruct("isgi_2DDL_lattice2.ima.gz",      "this_2DDL_lattice2.ima",      "Cylinder 2DDL lattice with isotropic pdfs") );

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
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our paracrystal lattice");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs paracrystal lattice");

        // difference
        c1->cd(3);
        IsGISAXSTools::setMinimum(-1e-4);
        IsGISAXSTools::setMaximum(1e-4);
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

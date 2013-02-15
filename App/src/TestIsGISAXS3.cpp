#include "TestIsGISAXS3.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "Simulation.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"

#include <sstream>
#include "TCanvas.h"


TestIsGISAXS3::TestIsGISAXS3() : IFunctionalTest("TestIsGISAXS3")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/");
}


void TestIsGISAXS3::execute()
{
    Simulation simulation(mp_options);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // cylinder in BA
    MultiLayer *sample = dynamic_cast<MultiLayer *>(
            SampleFactory::instance().createItem("IsGISAXS3_CylinderBA"));
    simulation.setSample(*sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_cylinder_BA.ima");

    // cylinder in BA with size distribution
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS3_CylinderBASize"));
    simulation.setSample(*sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_cylinder_BA_size.ima");

    // cylinder in DWBA
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS3_CylinderDWBA"));
    simulation.setSample(*sample);
    simulation.runSimulation();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_cylinder_DWBA.ima");
}


void TestIsGISAXS3::finalise()
{
    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgi_cylinder_BA.ima.gz",      "this_cylinder_BA.ima",
            "Cylinder BA Formfactor") );
    tocompare.push_back( CompareStruct("isgi_cylinder_BA_size.ima.gz", "this_cylinder_BA_size.ima",
            "Cylinder BA Formfactor with size distribution") );
    tocompare.push_back( CompareStruct("isgi_cylinder_DWBA.ima.gz",    "this_cylinder_DWBA.ima",
            "Cylinder DWBA Formfactor") );

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

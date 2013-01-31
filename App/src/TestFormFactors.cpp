#include "TestFormFactors.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "TCanvas.h"
#include "OutputDataIOFactory.h"


void TestFormFactors::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Box"));
    GISASExperiment experiment(mp_options);
    experiment.setSample(*sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/");
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Box.ima");

     //Cone
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Cone"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Cone.ima");

     //Ellipsoid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Ellipsoid"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Ellipsoid.ima");

     //Sphere
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Sphere"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Sphere.ima");

     //Full Spheroid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_FullSpheroid"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSpheroid.ima");

     //Hemi Spheroid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_HemiSpheroid"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_HemiSpheroid.ima");

     //Pyramid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Pyramid"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Pyramid.ima");

     //Cylinder
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Cylinder"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Cylinder.ima");

     //Full Sphere
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_FullSphere"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSphere.ima");

     //Prism3
     sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("FormFactor_Prism3"));
     experiment.setSample(*sample);
     experiment.runSimulation();
     OutputDataIOFactory::writeOutputData(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Prism3.ima");


    //OutputData<double > *mp_intensity_output = experiment.getOutputDataClone();
}




void TestFormFactors::finalise()
{
    std::vector<std::string > this_files;
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Box.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Cone.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Sphere.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Ellipsoid.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSpheroid.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_HemiSpheroid.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Parallelpiped.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Cylinder.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Pyramid.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSphere.ima");
//    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Prism3.ima");

    int ncomparison = (int)this_files.size();
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("Form Factors", "TestFormFactors");
    c1->Divide(4,5);

    for(int i=0; i<ncomparison; i++) {
            OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_files[i]);

            IsGISAXSTools::setMinimum(1.);
            // our calculations
            c1->cd(i+1); gPad->SetLogz();
            IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our Form Factors");

            IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
//            delete our_data;
        }
    }


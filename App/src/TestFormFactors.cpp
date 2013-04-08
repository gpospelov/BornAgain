// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFormFactors.cpp
//! @brief     Implements class TestFormFactors.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFormFactors.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "TCanvas.h"
#include "OutputDataIOFactory.h"


void TestFormFactors::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Box"));
    Simulation simulation(mp_options);
    simulation.setSample(*sample);
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    simulation.runSimulation();
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/");
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Box.ima");

     //Cone
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Cone"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Cone.ima");

     //Ellipsoid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Ellipsoid"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Ellipsoid.ima");

     //Sphere
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Sphere"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Sphere.ima");

     //Full Spheroid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_FullSpheroid"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSpheroid.ima");

     //Hemi Spheroid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_HemiSpheroid"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_HemiSpheroid.ima");

     //Pyramid
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Pyramid"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Pyramid.ima");

     //Cylinder
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Cylinder"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Cylinder.ima");

     //Full Sphere
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_FullSphere"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSphere.ima");

     //Prism3
     sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("FormFactor_Prism3"));
     simulation.setSample(*sample);
     simulation.runSimulation();
     OutputDataIOFactory::writeOutputData(*simulation.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Prism3.ima");
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
    TCanvas *c1 = DrawHelper::createAndRegisterCanvas("Form Factors", "TestFormFactors");
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




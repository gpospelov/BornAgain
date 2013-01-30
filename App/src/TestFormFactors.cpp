#include "TestFormFactors.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DrawHelper.h"

#include "TCanvas.h"



void TestFormFactors::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_Box"));
    GISASExperiment experiment(mp_options);
    experiment.setSample(*sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    //m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/");
//    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Box.ima");



    // cylinder in BA
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_CylinderBA"));
    experiment.setSample(*sample);
    experiment.runSimulation();
   // IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_cylinder_BA.ima");


    // cylinder in BA with size distribution
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_CylinderBASize"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    //IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_cylinder_BA_size.ima");


    // cylinder in DWBA
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_CylinderDWBA"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    //IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_cylinder_DWBA.ima");


    // pyramid
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_Pyramid"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    //IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_Pyramid_Z0.ima");

    //rorated pyramid
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_RotatedPyramid"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    //IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), m_data_path+"this_Pyramid_Z0.ima");

    //core shell particles
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_CoreShellParticles"));
    experiment.setSample(*sample);
    experiment.runSimulation();
//    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_core_shell_qxqy.ima");


    //cylinder and prism
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_CylinderAndPrism"));
    experiment.setSample(*sample);
    experiment.runSimulation();
//    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_2-types-of-islands-ewald.ima");



    //ellipsoid
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_Ellipsoid"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    //IsGISAXSTools::writeOutputDataToFile(*this_files, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_Ellipsoid.ima");
//    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Ellipsoid.ima");

    //prism6
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_Prism6"));
    experiment.setSample(*sample);
    experiment.runSimulation();
//    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Prism6.ima");



    //full sphere
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS_FullSphere"));
    experiment.setSample(*sample);
    experiment.runSimulation();
//    IsGISAXSTools::writeOutputDataToFile(*experiment.getOutputData(), Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSphere.ima");




    //OutputData<double > *mp_intensity_output = experiment.getOutputDataClone();

}



void TestFormFactors::finalise()
{

    std::vector<std::string > this_files;

      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_cylinder_BA.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_cylinder_BA_size.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_cylinder_DWBA.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_pyramid_Z0.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_pyramid_Z45.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Box.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_core_shell_qxqy.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_2-types-of-islands-ewald.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Prism6.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_Ellipsoid.ima");
      this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/FormFactors/this_FullSphere.ima");




    size_t ncomparison = this_files.size();
    //canvaces[0] = DrawHelper::instance().createAndRegisterCanvas("Form Factors", "TestFormFactors");
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("Form Factors", "TestFormFactors");
    c1->Divide(4,5);

    for(size_t i=0; i<ncomparison; i++) {
//            OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_files[i], 10);


            IsGISAXSTools::setMinimum(1.);
            // our calculations
            c1->cd((int)i+1); gPad->SetLogz();
//            IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our pyramid FF");

            IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
//            delete our_data;
        }
    }





































































//std::vector<std::string > isgi_files;
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_Box.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_BA.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_BA_size.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_DWBA.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_pyramid_Z0.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_core_shell_qxqy.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_2-types-of-islands-ewald.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_Prism6.ima");
//isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_Ellipsoid.ima");



/*
void TestFormFactors::finalise()
{


    std::vector<std::string > isgi_files;
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_pyramid_Z0.ima");
   // isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_Box.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_BA.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_BA_size.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_DWBA.ima");

    std::vector<std::string > this_files;
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_pyramid_Z0.ima");
    //isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_Box.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_BA_Box.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_BA_Box_size.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_DWBA_Box.ima");


    int ncomparison = m_results.size();

    TCanvas *canvaces[2];
    canvaces[0] = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS9_c1", "Pyramid DWBA formfactor");


    for(int i_comparison=0; i_comparison<ncomparison; i_comparison++) {
        OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_files[i_comparison], 10);
        OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_files[i_comparison], 10);

        TCanvas *c1 = canvaces[i_comparison];
        c1->Divide(2,2);

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our pyramid FF");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs pyramid FF");

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

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
    }
}






IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(4*i+1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our Pyramid FF");



      // isgisaxs data
        c1->cd(4*i+2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs mean FF");

        // difference
        c1->cd(4*i+3);
        IsGISAXSTools::setMinimum(-0.0001);
        IsGISAXSTools::setMaximum(0.0001);
        IsGISAXSTools::drawOutputDataDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

        // difference
        c1->cd(4*i+4);
        IsGISAXSTools::resetMinimumAndMaximum();
        //IsGISAXSTools::setMinimum(1);
        IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");



        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
        delete isgi_data;
        delete our_data;
    }

}














void TestFormFactors::finalise()
{
    std::vector< CompareStruct > tocompare;
   // tocompare.push_back( CompareStruct("isgi_Box.ima",              "this_Box.ima",              "Box         TestFormFactors") );
    tocompare.push_back( CompareStruct("isgi_cylinder_BA.ima",      "this_cylinder_BA.ima",      "Cylinder BA TestFormFactors") );
    tocompare.push_back( CompareStruct("isgi_cylinder_BA_size.ima", "this_cylinder_BA_size.ima", "Cylinder BA TestFormFactors with size distribution") );
    tocompare.push_back( CompareStruct("isgi_cylinder_DWBA.ima",    "this_cylinder_DWBA.ima",    "Cylinder DWBA TestFormFactors") );

  //  std::ostringstream os;
    //os<<i;
    //std::string cname = getName()+"_c"+os.str();
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("Form Factors", "TestFormFactors");
    //c1->Divide(2,2);
    c1->Divide(4,tocompare.size());

    for(size_t i=0; i<tocompare.size(); ++i){
        OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile( m_data_path+tocompare[i].isginame );
        OutputData<double> *our_data =  IsGISAXSTools::readOutputDataFromFile( m_data_path+tocompare[i].thisname );

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(4*i+1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our cylinder FF");

        // isgisaxs data
        c1->cd(4*i+2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs mean FF");

        // difference
        c1->cd(4*i+3);
        IsGISAXSTools::setMinimum(-0.0001);
        IsGISAXSTools::setMaximum(0.0001);
        IsGISAXSTools::drawOutputDataDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

        // difference
        c1->cd(4*i+4);
        IsGISAXSTools::resetMinimumAndMaximum();
        //IsGISAXSTools::setMinimum(1);
        IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
        delete isgi_data;
        delete our_data;
    }

}








void TestFormFactors::finalise()
{
    std::vector<std::string > isgi_files;
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/isgi_Box_qxqy.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_BA_qxqy.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_BA_size.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/isgi_cylinder_DWBA.ima");

    std::vector<std::string > this_files;
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/this_Box_qxqy.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_BA_qxqy.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_BA_size.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/this_cylinder_DWBA.ima");



   // int ncomparison = m_results.size();

    TCanvas *canvaces[4];
    canvaces[0] = DrawHelper::instance().createAndRegisterCanvas("TestFormFactors_c1", "Box TestFormFactors");
    canvaces[1] = DrawHelper::instance().createAndRegisterCanvas("TestFormFactors_c2", "cylinder BA TestFormFactors");
    canvaces[2] = DrawHelper::instance().createAndRegisterCanvas("TestFormFactors_c3", "cylinder BA size TestFormFactors");
    canvaces[4] = DrawHelper::instance().createAndRegisterCanvas("TestFormFactors_c4", "cylinder DWBA TestFormFactors");


    //for(int i_comparison=0; i_comparison<ncomparison; i_comparison++) {

    for(int i_comparison=0; i_comparison<ncomparison; i_comparison++) {
        OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_files[i_comparison], 10);
        OutputData<double> *our_data  = IsGISAXSTools::readOutputDataFromFile(this_files[i_comparison], 10);

        TCanvas *c1 = canvaces[i_comparison];
        c1->Divide(2,2);

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our cylinder FF");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs cylinder FF");

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

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
    }
}











void TestIsGISAXS12::finalise()
{
    std::string isgi_file(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/isgi_Box_qxqy.ima");
    std::string this_file(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/this_Box_qxqy.ima");

    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_file);
    OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_file);

    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS12_c1", "Box islands");
    c1->Divide(2,2);

    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our Box Particles");

    // isgisaxs data
    c1->cd(2); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs Box particles");

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

*/

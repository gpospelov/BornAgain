#include "TestIsGISAXS10.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "DrawHelper.h"

#include "TCanvas.h"

void TestIsGISAXS10::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS10_CylindersParacrystal1D"));

    GISASExperiment experiment(mp_options);
    experiment.setSample(*sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
//    experiment.setBeamIntensity(1e7);
    experiment.runSimulation();
//    experiment.normalize();
    OutputData<double > *mp_intensity_output = experiment.getOutputDataClone();
//    double total_count = mp_intensity_output->total();
//    std::cout << "Total count in detector: " << total_count << std::endl;
//    std::cout << "Scattered percentage in detector: " << 100*total_count/experiment.getBeam().getIntensity() << std::endl;
//    IsGISAXSTools::drawLogOutputData(*mp_intensity_output, "c1_test_isgisaxs_10", "1D paracrystal islands",
//            "CONT4 Z");
    IsGISAXSTools::writeOutputDataToFile(*mp_intensity_output, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-10/this_para1dcyl.ima");
}


void TestIsGISAXS10::finalise()
{
    std::string isgi_file(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-10/isgi_para1dcyl.ima");
    std::string this_file(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-10/this_para1dcyl.ima");

    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_file);
    OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_file);

    //TCanvas *c1 = new TCanvas("TestIsGISAXS10_c1", "1D paracrystal cylinder islands", 1024, 768);
    TCanvas *c1 = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS10_c1", "1D paracrystal cylinder islands");
    c1->Divide(2,2);

    IsGISAXSTools::setMinimum(1.);
    // our calculations
    c1->cd(1); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our cylinder islands");

    // isgisaxs data
    c1->cd(2); gPad->SetLogz();
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs cylinder islands");

    // difference
    c1->cd(3);
    IsGISAXSTools::setMinimum(-0.0001);
    IsGISAXSTools::setMaximum(0.0001);
    IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

    // difference
    c1->cd(4);
    IsGISAXSTools::resetMinimumAndMaximum();
    IsGISAXSTools::setMinimum(1);
    IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

    delete isgi_data;
    delete our_data;

}


// The next sample was for testing particles inside substrate and is now obsolete
//void TestIsGISAXS10::initializeSample2()
//{
//    delete mp_sample;
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-5e-6, 2e-8);
//    complex_t n_particle(1.0-5e-5, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    IInterferenceFunction *p_interference_funtion_1 = new InterferenceFunctionNone();
////    IInterferenceFunction *p_interference_funtion_2 = new InterferenceFunctionNone();
//    ParticleDecoration particle_decoration;
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),
//                0*Units::nanometer, 0.5);
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)),
//            0*Units::nanometer, 0.5);
//    particle_decoration.addInterferenceFunction(p_interference_funtion_1);
////    particle_decoration.addInterferenceFunction(p_interference_funtion_2);
//    LayerDecorator substrate_layer_decorator(substrate_layer, particle_decoration);
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    mp_sample = p_multi_layer;
//}


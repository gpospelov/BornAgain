#include "IsGISAXS03.h"
#include "MultiLayer.h"
//#include "ParticleDecoration.h"
//#include "LayerDecorator.h"
//#include "InterferenceFunctionNone.h"
//#include "FormFactorCylinder.h"
//#include "FormFactorPrism3.h"
//#include "Units.h"
//#include "MaterialManager.h"
//#include "OutputDataIOFactory.h"
#include "GISASExperiment.h"
#include "Utils.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS03::IsGISAXS03()
    : m_name("IsGISAXS03")
    , m_description("cylinder on top of substrate")
    , m_result(0)
{ }

void FunctionalTests::IsGISAXS03::run()
{
    // ---------------------
    // building sample
    // ---------------------


    // ---------------------
    // building experiment
    // ---------------------


    // ---------------------
    // running experiment
    // ---------------------



    // ---------------------
    // copying data
    // ---------------------
    m_result = experiment.getOutputDataClone();

}


int FunctionalTests::IsGISAXS03::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data
   // std::string filename = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS03/isgisaxs03_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}

//Rest done
#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS03 test;
    test.run();

    return test.analyseResults();
}
#endif


////////////////////////////
// IsGISAXS01.cpp
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"

#include "InterferenceFunctionNone.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "GISASExperiment.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

void FunctionalTests::IsGISAXS01::run()
{
    // ---------------------
    // building sample
    // ---------------------
    MultiLayer multi_layer;
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    ParticleDecoration particle_decoration;
    complex_t n_particle(1.0-6e-4, 2e-8);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    multi_layer.addLayer(air_layer_decorator);
    multi_layer.addLayer(substrate_layer);

    // ---------------------
    // building experiment
    // ---------------------
    GISASExperiment experiment;
    experiment.setDetectorParameters(100,-1.0*Units::degree, 1.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running experiment
    // ---------------------
    experiment.setSample(multi_layer);
    experiment.runSimulation();

    // ---------------------
    // copying data
    // ---------------------
    m_result = experiment.getOutputDataClone();

}


int FunctionalTests::IsGISAXS01::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data
    std::string filename = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS01/isgisaxs01_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS01 test;
    test.run();

    return test.analyseResults();
}
#endif

//////////////////////////////////////////////////////////
//StandardSamples.cpp
/* ************************************************************************* */
// IsGISAXS3 functional test: cylinder on top of substrate
/* ************************************************************************* */
ISample *StandardSamples::IsGISAXS3_CylinderDWBA()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_substrate(1.0-6e-6, 2e-8);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(air_layer_decorator);
    p_multi_layer->addLayer(substrate_layer);
    return p_multi_layer;
}

// IsGISAXS3 functional test: cylinder in the air
ISample *StandardSamples::IsGISAXS3_CylinderBA()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

// IsGISAXS3 functional test: cylinder in the air with size distribution
ISample *StandardSamples::IsGISAXS3_CylinderBASize()
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    ParticleDecoration particle_decoration;

    // preparing prototype of nano particle
    double radius = 5*Units::nanometer;
    double sigma = 0.2*radius;
    FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( 5*Units::nanometer, radius);
    Particle nano_particle(n_particle, p_ff_cylinder);

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins(100), nfwhm(2);
    StochasticSampledParameter par(StochasticDoubleGaussian(radius, sigma), nbins, nfwhm);

    ParticleBuilder builder;
    builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
    builder.plantParticles(particle_decoration);

    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);

    return p_multi_layer;
}
///////////////////////////
//TestIsGISAXS03.cpp
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "GISASExperiment.h"
#include "FormFactors.h"
#include "SampleFactory.h"
#include "DrawHelper.h"
#include "OutputDataIOFactory.h"

#include <sstream>

TestIsGISAXS3::TestIsGISAXS3() : IFunctionalTest("TestIsGISAXS3")
{
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-3/");
}


void TestIsGISAXS3::execute()
{
    GISASExperiment experiment(mp_options);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // cylinder in BA
    MultiLayer *sample = dynamic_cast<MultiLayer *>(
            SampleFactory::instance().createItem("IsGISAXS3_CylinderBA"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),m_data_path+"this_cylinder_BA.ima");

    // cylinder in BA with size distribution
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS3_CylinderBASize"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),m_data_path+"this_cylinder_BA_size.ima");

    // cylinder in DWBA
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS3_CylinderDWBA"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),m_data_path+"this_cylinder_DWBA.ima");
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
        IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
        delete isgi_data;
        delete our_data;
    }
}


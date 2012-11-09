#include "TestIsGISAXS12.h"
#include "Utils.h"
#include "OutputData.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "MaterialManager.h"
#include "Particle.h"
#include "ParticleDecoration.h"
#include "FormFactorCylinder.h"
#include "StochasticSampledParameter.h"
#include "ParticleBuilder.h"
#include "LayerDecorator.h"
#include "Units.h"
#include "StochasticGaussian.h"
#include "InterferenceFunctionNone.h"



#include <iostream>
#include <fstream>
#include "TCanvas.h"

TestIsGISAXS12::TestIsGISAXS12() : IFunctionalTest("TestIsGISAXS12")
{
    std::cout << "TestIsGISAXS12::TestIsGISAXS12() -> Info" << std::endl;
    m_data_path = std::string(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-12/");

}


void TestIsGISAXS12::execute()
{

    //read_isgisaxs_datfile(m_data_path+"/isgi_fitconstraints.dat");

    OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile( m_data_path+"/isgi_fitconstraints.ima" );

    TCanvas *c1 = new TCanvas("c1","c1",1024,768);
    c1->cd(); gPad->SetLogz();
    IsGISAXSTools::setMinimum(100);
    IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "Our mean FF");

}


void TestIsGISAXS12::finalise()
{

}


//void GISASExperiment::initializeAnglesIsgisaxs(NamedVector<double> *p_axis, double start, double end, size_t size) {
//    double start_sin = std::sin(start);
//    double end_sin = std::sin(end);
//    double step = (end_sin-start_sin)/(size-1);
//    for(size_t i=0; i<size; ++i) {
//        p_axis->push_back(std::asin(start_sin + step*i));
//    }
//    return;
//}


void TestIsGISAXS12::read_isgisaxs_datfile(const std::string &filename)
{
    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    std::string sline;
    while( std::getline(fin, sline))
    {
        std::cout << sline << std::endl;
    }

    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

}



/* ************************************************************************* */
//
/* ************************************************************************* */
TestIsGISAXS12::TestSampleBuilder::TestSampleBuilder()
{

}


/* ************************************************************************* */
//
/* ************************************************************************* */
ISample *TestIsGISAXS12::TestSampleBuilder::buildSample() const
{
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    ParticleDecoration particle_decoration;

    // preparing nano particles prototypes for seeding layer's particle_decoration
    double radius1 = 5*Units::nanometer;
    double radius2 = 10*Units::nanometer;
    double height1 = radius1;
    double height2 = radius2;
    FormFactorCylinder *p_ff_cylinder1 = new FormFactorCylinder(height1, radius1);
    Particle cylinder1(n_particle, p_ff_cylinder1 );

    FormFactorCylinder *p_ff_cylinder2 = new FormFactorCylinder(height2, radius2);
    Particle cylinder2(n_particle, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=150;
    double sigma1 = radius1*0.2;
    double sigma2 = radius2*0.02;
    int nfwhm(3); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM
    StochasticSampledParameter par1(StochasticDoubleGaussian(radius1, sigma1), nbins, nfwhm);
    StochasticSampledParameter par2(StochasticDoubleGaussian(radius2, sigma2), nbins, nfwhm);

    // building nano particles
    ParticleBuilder builder;
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, 0.95);
    builder.plantParticles(particle_decoration);

    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, 0.05);
    builder.plantParticles(particle_decoration);

    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    // making layer holding all whose nano particles
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    p_multi_layer->addLayer(air_layer_decorator);
    return p_multi_layer;
}

void TestIsGISAXS12::TestSampleBuilder::init_parameters()
{

}





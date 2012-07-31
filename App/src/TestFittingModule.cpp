#include "TestFittingModule.h"
#include "Units.h"
#include "MathFunctions.h"
#include "GISASExperiment.h"
#include "IsGISAXSTools.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "NanoParticleDecoration.h"
#include "LayerDecorator.h"
#include "NanoParticle.h"
#include "FormFactors.h"

#include "Math/GSLMinimizer.h"
#include "Minuit2/Minuit2Minimizer.h"
#include "Math/Functor.h"

MultiLayer *gp_fit_sample = 0;

TestFittingModule::TestFittingModule()
: mp_exact_data(0)
, mp_real_data(0)
, mp_simulated_data(0)
, mp_sample(0)
{
}

TestFittingModule::~TestFittingModule()
{
    delete mp_exact_data;
    delete mp_real_data;
    delete mp_simulated_data;
    delete mp_sample;
}

void TestFittingModule::execute()
{
    // Generate exact sample simulation
    if (mp_exact_data) delete mp_exact_data;
    initializeSample();
    gp_fit_sample = dynamic_cast<MultiLayer *>(mp_sample);
    GISASExperiment experiment;
    experiment.setSample(mp_sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree
            ,100 , 0.0*Units::degree, 2.0*Units::degree);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    mp_exact_data = experiment.getOutputDataClone();
    // Generate noisy version
    generateRealData(0.2);
    // Perform the actual fitting
    //   Initialize global data:
    Fitting::p_experiment = &experiment;
    ChiSquaredModule csm(*mp_real_data);
    Fitting::p_chi_squared_module = &csm;
    ParameterPool *p_param_pool = mp_sample->createParameterTree();
    std::cout << *p_param_pool;
    FitMultiParameter fmp1;
    fmp1.addParameterFromPool("/MultiLayer/Layer0/thickness", p_param_pool);
    Fitting::fit_params.push_back(&fmp1);
    //   Execute the fitting with ROOT:
    ROOT::Minuit2::Minuit2Minimizer min ( ROOT::Minuit2::kMigrad );
//    ROOT::Math::GSLMinimizer min;
    min.SetMaxFunctionCalls(1000000);
    min.SetMaxIterations(100000);
    min.SetTolerance(0.001);

    ROOT::Math::Functor f(&Fitting::functionToMinimize, 1);
    double step[1] = { 5*Units::nanometer };
    double variable[1] = { 12*Units::nanometer };

    min.SetFunction(f);

      // Set the free variables to be minimized!
    min.SetVariable(0,"x",variable[0], step[0]);

    min.Minimize();
    mp_simulated_data = experiment.getOutputDataClone();

    std::cout << "Layer thickness fit: " << min.X()[0] << " nanometer" << std::endl;

    IsGISAXSTools::drawLogOutputData(*mp_real_data, "c1_test_fitting", "fitting", "CONT4 Z");
//    IsGISAXSTools::writeOutputDataToFile(*mp_real_data, Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-10/para1dcyl.ima");
}

void TestFittingModule::initializeSample()
{
    delete mp_sample;
    MultiLayer *p_multi_layer = new MultiLayer();
    complex_t n_air(1.0, 0.0);
    complex_t n_layer(1.0-2e-6, 2e-8);
    complex_t n_substrate(1.0-5e-6, 2e-8);
    complex_t n_particle(1.0-5e-5, 2e-8);
    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", n_air);
    const IMaterial *p_layer_material = MaterialManager::instance().addHomogeneousMaterial("Layer", n_layer);
    const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", n_substrate);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer layer_layer;
    layer_layer.setMaterial(p_layer_material);
    layer_layer.setThickness(10.0*Units::nanometer);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    IInterferenceFunction *p_interference_funtion = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,
            7*Units::nanometer, 1e7*Units::nanometer);
    NanoParticleDecoration particle_decoration(
                new NanoParticle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),
                0*Units::nanometer, 1.0);
    particle_decoration.addInterferenceFunction(p_interference_funtion);
    LayerDecorator layer_decorator(air_layer, particle_decoration);

    p_multi_layer->addLayer(layer_decorator);
    p_multi_layer->addLayer(layer_layer);
    p_multi_layer->addLayer(substrate_layer);
    mp_sample = p_multi_layer;
}

void TestFittingModule::generateRealData(double noise_factor)
{
    if (mp_exact_data==0) {
        return;
    }
    if (mp_real_data) {
        delete mp_real_data;
    }
    mp_real_data = mp_exact_data->clone();
    mp_real_data->resetIndex();
    while (mp_real_data->hasNext()) {
        double current = mp_real_data->currentValue();
        double sigma = noise_factor*current;
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        mp_real_data->next() = random;
    }
}

GISASExperiment *Fitting::p_experiment = 0;
ChiSquaredModule *Fitting::p_chi_squared_module = 0;
std::vector<FitMultiParameter *> Fitting::fit_params;

double Fitting::functionToMinimize(const double* p_params)
{
    for (size_t i=0; i<Fitting::fit_params.size(); ++i) {
        std::cout << "param " << i+1 << ": " << p_params[i] << std::endl;
        Fitting::fit_params[i]->setValue(p_params[i]);
    }
    std::cout << "thickness of layer 1: " << gp_fit_sample->getLayer(1)->getThickness() << std::endl;
    Fitting::p_experiment->runSimulation();
    const OutputData<double> *p_simulated_data = Fitting::p_experiment->getOutputData();
    double chi_squared = Fitting::p_chi_squared_module->calculateChiSquared(p_simulated_data);
    std::cout << "chi squared = " << chi_squared << std::endl;
    return chi_squared;
}

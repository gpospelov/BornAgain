#include "TestFit01.h"
#include "MaterialManager.h"
#include "MessageService.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "InterferenceFunctions.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "FitSuite.h"
#include "MinimizerFactory.h"

#include "TBenchmark.h"

#include <iostream>
#include <iomanip>
#include <boost/format.hpp>

using namespace FunctionalTests;


TestFit01::TestFit01()
    : m_test_name("TestFit01")
    , m_test_description("Two parameters fit using variety of minimizers.")
    , m_cylinder_height(5.0*Units::nanometer)
    , m_cylinder_radius(5.0*Units::nanometer)
{
    m_minimizers.push_back( Minimizer("Minuit2","Migrad") );
    m_minimizers.push_back( Minimizer("Minuit2","Fumili") );
    m_minimizers.push_back( Minimizer("GSLMultiMin","BFGS") );
    m_minimizers.push_back( Minimizer("GSLMultiMin","SteepestDescent") );
    m_minimizers.push_back( Minimizer("GSLMultiFit","") ); // this is Levenberg-Marquard
//    m_minimizers.push_back( Minimizer("GSLSimAn","") );
//    m_minimizers.push_back( Minimizer("Genetic","") );
}


TestFit01::~TestFit01()
{

}

// run several minimization rounds using different minimizers
int TestFit01::run()
{
    std::cout << "*************************************"
            "*********************************" <<std::endl;
    std::cout << "*  Starting  TestFit01               "
            "                                *" <<std::endl;
    std::cout << "*************************************"
            "*********************************" <<std::endl;

    bool status_ok(true);
    for(size_t i=0; i<m_minimizers.size(); ++i ) {
        std::cout << boost::format("Test %1%: %|5t| %2%(%3%)\n") % i %
                m_minimizers[i].name % m_minimizers[i].algorithm;

        bool result = run_fitting(m_minimizers[i].name, m_minimizers[i].algorithm);
        status_ok &= result;
    }

    std::cout << m_test_name << " " << m_test_description << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


// run fitting using dedicated minimizer, return true in the case of success
bool TestFit01::run_fitting(const std::string &minimizer_name,
        const std::string &minimizer_algorithm)
{
    TBenchmark mb;
    mb.Start("test");

    ISample *sample = buildSample();
    Simulation *simulation = createSimulation();
    simulation->setSample(*sample);

    // Creating real data, which is simply results of our simulation with default values
    simulation->runSimulation();
    OutputData<double> *real_data = simulation->getOutputDataClone();

    // setting fitting
    FitSuite *fitSuite = new FitSuite();
    fitSuite->setMinimizer( MinimizerFactory::createMinimizer(
            minimizer_name, minimizer_algorithm) );
    fitSuite->addFitParameter("*height", 4.*Units::nanometer,
            0.04*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addFitParameter("*radius", 6.*Units::nanometer,
            0.06*Units::nanometer, AttLimits::lowerLimited(0.01) );
    fitSuite->addSimulationAndRealData(*simulation, *real_data);

    // run fit
    fitSuite->runFit();

    double height_found = fitSuite->getMinimizer()->getValueOfVariableAtMinimum(0);
    double height_diff = std::fabs(height_found - m_cylinder_height)/m_cylinder_height;
    double radius_found = fitSuite->getMinimizer()->getValueOfVariableAtMinimum(1);
    double radius_diff = std::fabs(radius_found - m_cylinder_radius)/m_cylinder_radius;

    mb.Stop("test");
    std::cout << boost::format("%|12t| %-10s : %-6.3f \n") % "RealTime" %
            mb.GetRealTime("test");
    std::cout << boost::format("%|12t| %-10s : %-6.3f \n") % "CpuTime" %
            mb.GetCpuTime("test");
    std::cout << boost::format("%|12t| %-10s : %-4d \n") % "NCalls" %
            fitSuite->getNCalls();
    std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) \n") %
            "Par1" % height_found % height_diff;
    std::cout << boost::format("%|12t| %-10s : %-6.4f (diff %6.4g) \n") %
            "Par2" % radius_found % radius_diff;

    delete sample;
    delete simulation;
    delete real_data;
    delete fitSuite;

    const double diff = 1.0e-02;
    bool isSuccess = true;
    if( (height_diff > diff) || (radius_diff > diff) ) isSuccess=false;
    return isSuccess;
}


// create cylinders in the air
ISample *TestFit01::buildSample()
{
    MultiLayer *multi_layer = new MultiLayer();
    const IMaterial *air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    Layer air_layer(air_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration( new Particle(n_particle,
            new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer->addLayer(air_layer_decorator);
    return multi_layer;
}


// create simulation
Simulation *TestFit01::createSimulation()
{
    Simulation *simulation = new Simulation();
    simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100 , 0.0*Units::degree, 2.0*Units::degree);
    simulation->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    simulation->setBeamIntensity(1e10);
    return simulation;
}


#ifdef STANDALONE
int main()
{
//    MSG::SetLevel(MSG::INFO);
    FunctionalTests::TestFit01 test;
    return test.run();
}
#endif


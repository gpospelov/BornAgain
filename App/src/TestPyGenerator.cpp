#include <iostream>
#include <fstream>
#include <set>
#include <typeinfo>
#include <exception>
#include "FormFactors.h"
#include "ICompositeSample.h"
#include "INamed.h"
#include "ISample.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "InterferenceFunctionNone.h"
#include "ISample.h"
#include "LabelSample.h"
#include "Materials.h"
#include "Samples.h"
#include "Simulation.h"
#include "SimulationRegistry.h"
#include "TestPyGenerator.h"
#include "InterferenceFunction2DLattice.h"
#include "PositionParticleInfo.h"
#include "ParticleCoreShell.h"

TestPyGenerator::TestPyGenerator()
{

}

bool TestPyGenerator::testPythonScript(Simulation *simulation)
{
    simulation->runSimulation();
    ISample *iSample = simulation->getSample();
    MultiLayer *multiLayer = dynamic_cast<MultiLayer *>(iSample);
    //multiLayer->printSampleTree();
    VisitSampleTree(*multiLayer, visitor);
    std::ofstream pythonFile;
    pythonFile.open("PythonScript.py");
    pythonFile << visitor.genPyScript(simulation, "output");
    pythonFile.close();
    std::string command = "python PythonScript.py";
    system(command.c_str());
    m_reference_data = simulation->getOutputData();
    m_simulated_data = IntensityDataIOFactory::readIntensityData("output.int");
    double diff = IntensityDataFunctions::getRelativeDifference(*m_simulated_data,*m_reference_data);
    std::cout << "diff = " << diff << std::endl;
    if (diff == 0)
        return 1;
    else
        return 0;
}

void TestPyGenerator::execute()
{
    std::cout << "\n\n\n\n";
    SimulationRegistry simulationRegistry;
    //Simulation *simulation = makeSimulation();
    Simulation *simulation = simulationRegistry.createSimulation("isgisaxs01");
    testPythonScript(simulation);
}


MultiLayer *TestPyGenerator::makeSample()
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);

    complex_t n_particle_shell(1.0-1e-4, 2e-8);
    complex_t n_particle_core(1.0-6e-5, 2e-8);

    HomogeneousMaterial shell_material("Shell", n_particle_shell);
    HomogeneousMaterial core_material("Core", n_particle_core);

    Layer air_layer(air_material);

    FormFactorBox ff_box1(16*Units::nanometer, 16*Units::nanometer, 8*Units::nanometer);
    Particle shell_particle(shell_material, ff_box1);

    FormFactorBox ff_box2(12*Units::nanometer, 12*Units::nanometer, 7*Units::nanometer);
    Particle core_particle(core_material, ff_box2);

    kvector_t core_position(0.0, 0.0, 0.0);
    ParticleCoreShell particle(shell_particle, core_particle, core_position);
    ParticleLayout particle_layout(particle.clone());
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    return multi_layer;
}

Simulation *TestPyGenerator::makeSimulation()
{
    m_simulation = new Simulation();
    m_simulation->setDetectorParameters(400,-1.0*Units::degree, 1.0*Units::degree, 400,0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(2.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    MultiLayer *multiLayer = makeSample();
    m_simulation->setSample(*multiLayer);
    return m_simulation;

}

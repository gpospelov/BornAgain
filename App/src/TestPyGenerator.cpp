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

TestPyGenerator::TestPyGenerator()
{
    testSamples.push_back("gui_isgisaxs01");
    testSamples.push_back("gui_isgisaxs04_1DDL");
    testSamples.push_back("gui_isgisaxs04_2DDL");
    testSamples.push_back("gui_isgisaxs11");
    testSamples.push_back("gui_isgisaxs06a");
    testSamples.push_back("gui_isgisaxs07");
}

bool TestPyGenerator::testPythonScript(Simulation *simulation)
{
    simulation->runSimulation();
    ISample *iSample = simulation->getSample();
    MultiLayer *multiLayer = dynamic_cast<MultiLayer *>(iSample);
    //multiLayer->printSampleTree();
    PyGenVisitor visitor;
    VisitSampleTree(*multiLayer, visitor);
    std::ofstream pythonFile;
    pythonFile.open("PythonScript.py");
    pythonFile << visitor.genPyScript(simulation,"output");
    pythonFile.close();
    std::string command = "python PythonScript.py";
    system(command.c_str());
    m_reference_data = simulation->getIntensityData();
    m_simulated_data = IntensityDataIOFactory::readIntensityData("output.int");
    double diff = IntensityDataFunctions::getRelativeDifference(*m_simulated_data,*m_reference_data);
    if (diff < 5e-10)
        return true;
    else
        std::cout << "Relative Difference between python script and reference sample: = " << diff << std::endl;
        return false;
}

void TestPyGenerator::execute()
{
    std::cout << "\n\n\n\n";
    SimulationRegistry simulationRegistry;
    for (std::list<std::string>::iterator it = testSamples.begin(); it != testSamples.end(); it++)
    {
        Simulation *simulation = simulationRegistry.createSimulation(*it);
        bool test = testPythonScript(simulation);
        std::cout << *it << " Python Script Generation Test: ";
        if (test == true)
            std::cout << "Passed\n";
        else
            std::cout << "Failed\n";
    }


}

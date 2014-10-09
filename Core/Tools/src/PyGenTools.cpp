#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "PyGenTools.h"
#include "Simulation.h"

void PyGenTools::genPyScript(Simulation *simulation,
                                std::string pyScriptName,
                                std::string outputDataFileName = "")
{
    simulation->runSimulation();
    ISample *iSample = simulation->getSample();
    MultiLayer *multiLayer = dynamic_cast<MultiLayer *>(iSample);
    PyGenVisitor visitor;
    VisitSampleTree(*multiLayer, visitor);
    std::ofstream pythonFile;
    pythonFile.open(pyScriptName.c_str());
    pythonFile << visitor.writePyScript(simulation, outputDataFileName);
    pythonFile.close();
}

std::string PyGenTools::printDouble(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(11);
    if((input-floor(input)) == 0.0)
    {
        inter << input << ".0";
    }
    else
    {
        inter << input;
    }
    return inter.str();
}

bool PyGenTools::testPyScript(Simulation *simulation)
{
    genPyScript(simulation, "PythonScript.py", "output");
    std::string command = "python PythonScript.py";
    int return_code = std::system(command.c_str());
    (void)return_code;
    /*
    PyObject *pModule = PyImport_AddModule("PythonScript.py");
    PyObject *pDict = PyModule_GetDict(pModule);
    PyObject *pRunSimulation = PyDict_GetItemString(pDict, "runSimulation");
    PyObject *pResult = PyObject_CallObject(pRunSimulation, NULL);
    Simulation *pSimulation = boost::python::extract<Simulation *>(pResult);

    boost::scoped_ptr<const OutputData<double> > reference_data(
                simulation->getIntensityData());
    boost::scoped_ptr<const OutputData<double> > simulated_data(
                pSimulation->getIntensityData()); */
    boost::scoped_ptr<const OutputData<double> > reference_data(
                simulation->getIntensityData());
    boost::scoped_ptr<const OutputData<double> > simulated_data(
                IntensityDataIOFactory::readIntensityData("output.int"));
    double diff = IntensityDataFunctions::getRelativeDifference(
                *simulated_data,*reference_data);
    if (diff < 5e-10)
        return true;
    else
        std::cout << "Relative Difference between python script and"
                     " reference sample: = " << diff << std::endl;
        return false;
}

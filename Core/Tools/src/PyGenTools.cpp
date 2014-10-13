#include <boost/scoped_ptr.hpp>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Python.h>
#include <boost/python.hpp>
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "PyGenTools.h"
#include "Simulation.h"

void PyGenTools::genPyScript(Simulation *simulation,
                                std::string pyScriptName)
{
    simulation->runSimulation();
    ISample *iSample = simulation->getSample();
    MultiLayer *multiLayer = dynamic_cast<MultiLayer *>(iSample);
    PyGenVisitor visitor;
    VisitSampleTree(*multiLayer, visitor);
    std::ofstream pythonFile;
    pythonFile.open(pyScriptName.c_str());
    pythonFile << visitor.writePyScript(simulation);
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
    genPyScript(simulation, "PythonScript.py");
//    Py_Initialize();
//    std::string path("sys.path.append('");
//    path.append("/home/abhishekskhanna/BornAgain-Build");
//    path.append("')");
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString(path.c_str());
//    PyObject *pName = PyString_FromString("PythonScript");
//    PyObject *pModule = PyImport_Import(pName);
//    PyObject *pDict = PyModule_GetDict(pModule);
//    PyObject *pRunSimulation = PyDict_GetItemString(pDict, "runSimulation");
//    PyObject *pResult = PyObject_CallObject(pRunSimulation, NULL);
//    Simulation *pSimulation = boost::python::extract<Simulation *>(pResult);
//    Py_Finalize();
//    boost::scoped_ptr<const OutputData<double> > reference_data(
//                simulation->getIntensityData());
//    boost::scoped_ptr<const OutputData<double> > simulated_data(
//                    pSimulation->getIntensityData());
    std::string command = "python PythonScript.py";
    int return_code = std::system(command.c_str());
    (void)return_code;

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

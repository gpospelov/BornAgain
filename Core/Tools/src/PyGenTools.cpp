// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/PyGenTools.cpp
//! @brief     Implements functions from PyGenTools namespace.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <boost/scoped_ptr.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <Python.h>
#include <boost/python.hpp>
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "PyGenTools.h"
#include "Simulation.h"
#include "BAPython.h"

std::string PyGenTools::genPyScript(Simulation *simulation)
{
    simulation->prepareSimulation();
    ISample *iSample = simulation->getSample();
    MultiLayer *multiLayer = dynamic_cast<MultiLayer *>(iSample);
    PyGenVisitor visitor;
    VisitSampleTree(*multiLayer, visitor);
    std::ostringstream result;
    result << visitor.writePyScript(simulation);
    return result.str();
}

bool PyGenTools::isSquare(double length1, double length2, double angle)
{
    if(length1 == length2 && Numeric::areAlmostEqual(angle, M_PI/2.0)) {
        return true;
    }
    return false;
}


bool PyGenTools::isHexagonal(double length1, double length2, double angle)
{
    if(length1 == length2 && Numeric::areAlmostEqual(angle, 2*M_PI/3.0)) {
        return true;
    }
    return false;
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
    std::ofstream pythonFile;
    pythonFile.open("PythonScript.py");
    pythonFile << "import sys\n";
    pythonFile << "import os\n";
    pythonFile << "sys.path.append(os.path.abspath("
               << "os.path.join(os.path.split(os.path.realpath(__file__))[0],"
               << "'..', '..', '..', 'lib')))\n\n";
    pythonFile << genPyScript(simulation);
    pythonFile.close();

//    Py_Initialize();
//    std::string path("sys.path.append('");
//    path.append("/home/abhishekskhanna/BornAgain-Build");
//    path.append("')");
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString(path.c_str());
//    PyObject *pName = PyString_FromString("PythonScript");
//    if (!pName)
//        throw std::runtime_error("PyGenTools::testPyScript -> pName is NULL");
//    PyObject *pModule = PyImport_Import(pName);
//    if (!pModule)
//        throw std::runtime_error("PyGenTools::testPyScript -> pModule is NULL");
//    PyObject *pDict = PyModule_GetDict(pModule);
//    if (!pDict)
//        throw std::runtime_error("PyGenTools::testPyScript -> pDict is NULL");
//    PyObject *pRunSimulation = PyDict_GetItemString(pDict, "runSimulation");
//    if (!pRunSimulation)
//        throw std::runtime_error(
//                "PyGenTools::testPyScript -> pRunSimulation is NULL");
//    PyObject *pResult = PyObject_CallObject(pRunSimulation, NULL);
//    if (!pResult)
//        throw std::runtime_error("PyGenTools::testPyScript -> pResult is NULL");
//    Simulation *pSimulation = boost::python::extract<Simulation *>(pResult);
//    Py_Finalize();
//    boost::scoped_ptr<const OutputData<double> > reference_data(
//                simulation->getIntensityData());
//    boost::scoped_ptr<const OutputData<double> > simulated_data(
//                    pSimulation->getIntensityData());
    std::string command = std::string(BORNAGAIN_PYTHON_EXE ) + " PythonScript.py";
    int return_code = std::system(command.c_str());
    (void)return_code;
    if (std::remove("PythonScript.py") != 0) {
        throw RuntimeErrorException("PyGenTools::testPyScript: "
            "PythonScript.py could not be removed from filesystem");
    }

    simulation->runSimulation();
    boost::scoped_ptr<const OutputData<double> > reference_data(
                simulation->getIntensityData());
    boost::scoped_ptr<const OutputData<double> > simulated_data(
                IntensityDataIOFactory::readIntensityData("output.int"));
    if (std::remove("output.int") != 0) {
        throw RuntimeErrorException("PyGenTools::testPyScript: "
            "output.int could not be removed from filesystem");
    }
    double diff = IntensityDataFunctions::getRelativeDifference(
                *simulated_data,*reference_data);
    if (diff < 5e-10)
        return true;
    else
        std::cout << "Relative Difference between python script and"
                     " reference sample: = " << diff << std::endl;
        return false;
}

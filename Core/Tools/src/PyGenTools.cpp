// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/PyGenTools.cpp
//! @brief     Implements functions from PyGenTools namespace.
//!
//! @homepage  http://www.bornagainproject.org
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
#include "GISASSimulation.h"
#include "Distributions.h"
#include "BAPython.h"

std::string PyGenTools::genPyScript(GISASSimulation *simulation)
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

std::string PyGenTools::printDouble(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(11);
    if (std::abs(input) < 1e-11) {
        inter << "0.0";
        return inter.str();
    }
    inter << input;
    if(inter.str().find('.') == std::string::npos)
    {
        inter << ".0";
    }
    return inter.str();
}

std::string PyGenTools::printDegrees(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(11);
    double in_degrees = input*180.0/M_PI;
    inter << in_degrees;
    if(inter.str().find('.') == std::string::npos)
    {
        inter << ".0";
    }
    inter << "*degree";
    return inter.str();
}

bool PyGenTools::isSquare(double length1, double length2, double angle)
{
    if(length1 == length2 && Numeric::areAlmostEqual(angle, Units::PI/2.0)) {
        return true;
    }
    return false;
}


bool PyGenTools::isHexagonal(double length1, double length2, double angle)
{
    if(length1 == length2 && Numeric::areAlmostEqual(angle, 2*Units::PI/3.0)) {
        return true;
    }
    return false;
}

bool PyGenTools::testPyScript(GISASSimulation *simulation)
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

    std::string command = std::string(BORNAGAIN_PYTHON_EXE) + " PythonScript.py";
    int return_code = std::system(command.c_str());
    (void)return_code;
    if (std::remove("PythonScript.py") != 0) {
        throw RuntimeErrorException("PyGenTools::testPyScript: "
            "PythonScript.py could not be removed from filesystem");
    }

    simulation->runSimulation();
    boost::scoped_ptr<const OutputData<double> > P_reference_data(
                simulation->getIntensityData());
    boost::scoped_ptr<const OutputData<double> > P_simulated_data(
                IntensityDataIOFactory::readIntensityData("output.int"));
    if (std::remove("output.int") != 0) {
        throw RuntimeErrorException("PyGenTools::testPyScript: "
            "output.int could not be removed from filesystem");
    }
    double diff = IntensityDataFunctions::getRelativeDifference(
                *P_simulated_data,*P_reference_data);
    if (diff < 5e-10)
        return true;
    else
        std::cout << "Relative Difference between python script and"
                     " reference sample: = " << diff << std::endl;
        return false;
}


std::string PyGenTools::getRepresentation(const IDistribution1D *distribution)
{
     std::ostringstream result;
     result << std::setprecision(12);

     if(const DistributionGate *d = dynamic_cast<const DistributionGate *>(distribution)) {
        result << "DistributionGate("
               << PyGenTools::printDouble(d->getMin()) << ", "
               << PyGenTools::printDouble(d->getMax()) << ")";
     }
     else if(const DistributionLorentz *d = dynamic_cast<const DistributionLorentz *>(distribution)) {
         result << "DistributionLorentz("
                << PyGenTools::printDouble(d->getMean()) << ", "
                << PyGenTools::printDouble(d->getHWHM()) << ")";
     }
     else if(const DistributionGaussian *d = dynamic_cast<const DistributionGaussian *>(distribution)) {
         result << "DistributionGaussian("
                << PyGenTools::printDouble(d->getMean()) << ", "
                << PyGenTools::printDouble(d->getStdDev()) << ")";
     }
     else if(const DistributionLogNormal *d = dynamic_cast<const DistributionLogNormal *>(distribution)) {
         result << "DistributionLogNormal("
                << PyGenTools::printDouble(d->getMedian()) << ", "
                << PyGenTools::printDouble(d->getScalePar()) << ")";
     }
     else if(const DistributionCosine *d = dynamic_cast<const DistributionCosine *>(distribution)) {
         result << "DistributionCosine("
                << PyGenTools::printDouble(d->getMean()) << ", "
                << PyGenTools::printDouble(d->getSigma()) << ")";
     }
     else {
         throw RuntimeErrorException(
            "PyGenTools::getRepresentation(const IDistribution1D *distribution) "
            "-> Error. Unknown distribution type");
     }
     return result.str();
}


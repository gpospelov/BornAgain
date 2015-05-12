// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPyGenerator.cpp
//! @brief     Implements class TestPyGenerator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <set>
#include <exception>
#include "FormFactors.h"
#include "ICompositeSample.h"
#include "INamed.h"
#include "ISample.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "IMaterial.h"
#include "InterferenceFunctionNone.h"
#include "ISample.h"
#include "SampleLabelHandler.h"
#include "Materials.h"
#include "Samples.h"
#include "Simulation.h"
#include "SimulationRegistry.h"
#include "TestPyGenerator.h"
#include "PyGenTools.h"

TestPyGenerator::TestPyGenerator()
{
    testSamples.push_back("gui_isgisaxs01");
    testSamples.push_back("gui_isgisaxs04_1DDL");
    testSamples.push_back("gui_isgisaxs04_2DDL");
    testSamples.push_back("gui_isgisaxs11");
    testSamples.push_back("gui_isgisaxs06a");
    testSamples.push_back("gui_isgisaxs07");
    testSamples.push_back("gui_multiple_layouts");
}

void TestPyGenerator::execute()
{
    std::cout << "\n\n\n\n";
    SimulationRegistry simulationRegistry;
    for (std::list<std::string>::iterator it = testSamples.begin();
         it != testSamples.end(); it++)
    {
        GISASSimulation *simulation = simulationRegistry.createSimulation(*it);
        bool test = PyGenTools::testPyScript(simulation);
        std::cout << *it << " Python Script Generation Test: ";
        if (test == true)
            std::cout << "Passed\n";
        else
            std::cout << "Failed\n";
    }


}

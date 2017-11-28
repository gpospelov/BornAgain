// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/IStandardTest.h
//! @brief     Defines pure virtual base class IStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "GISASSimulation.h"

IStandardTest::IStandardTest(const std::string& name, const std::string& description,
                             const Simulation& simulation, double threshold)
    : IFunctionalTest(name, description)
    , m_reference_simulation(simulation.clone())
    , m_threshold(threshold)
{}

IStandardTest::~IStandardTest() = default;

GISASSimulation* IStandardTest::gisasSimulation()
{
    if (GISASSimulation* gisas = dynamic_cast<GISASSimulation*>(m_reference_simulation.get())) {
        return gisas;
    } else
        throw std::runtime_error("Error in IStandardTest: cannot downcast Simulation to "
                                 "GISASSimulation. Wrong simulation type is used.");
}


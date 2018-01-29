// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/GISASSimulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IBackground.h"
#include "BornAgainNamespace.h"
#include "DWBAComputation.h"
#include "GISASSimulation.h"
#include "Histogram2D.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "RectangularDetector.h"
#include "SimulationElement.h"
#include "SphericalDetector.h"
#include "UnitConverters.h"

GISASSimulation::GISASSimulation()
{
    initialize();
}

GISASSimulation::GISASSimulation(const MultiLayer& p_sample)
    : Simulation2D(p_sample)
{
    initialize();
}

GISASSimulation::GISASSimulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation2D(p_sample_builder)
{
    initialize();
}

void GISASSimulation::prepareSimulation()
{
    if (m_instrument.getDetectorDimension() != 2)
        throw Exceptions::LogicErrorException("GISASSimulation::prepareSimulation() "
                "-> Error. The detector was not properly configured.");
    getInstrument().initDetector();
    Simulation::prepareSimulation();
}

size_t GISASSimulation::numberOfSimulationElements() const
{
    return getInstrument().getDetector()->numberOfSimulationElements();
}

SimulationResult GISASSimulation::result() const
{
    auto data = std::unique_ptr<OutputData<double>>(
                    m_instrument.createDetectorIntensity(m_sim_elements));
    auto p_det = getInstrument().getDetector();
    if (p_det) {
        auto p_spher_det = dynamic_cast<const SphericalDetector*>(p_det);
        if (p_spher_det) {
            SphericalConverter converter(*p_spher_det, getInstrument().getBeam());
            return SimulationResult(*data, converter);
        }
        auto p_rect_det = dynamic_cast<const RectangularDetector*>(p_det);
        if (p_rect_det) {
            RectangularConverter converter(*p_rect_det, getInstrument().getBeam());
            return SimulationResult(*data, converter);
        }
    }
    throw std::runtime_error("Error in GISASSimulation::result: "
                             "wrong or absent detector type");
}

void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength<=0.0)
        throw Exceptions::ClassInitializationException(
            "Simulation::setBeamParameters() -> Error. Incoming wavelength <= 0.");
    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
}

GISASSimulation::GISASSimulation(const GISASSimulation& other)
    : Simulation2D(other)
{
    initialize();
}

void GISASSimulation::initSimulationElementVector()
{
    auto beam = m_instrument.getBeam();
    m_sim_elements = generateSimulationElements(beam);
    if (m_cache.empty())
        m_cache.resize(m_sim_elements.size(), 0.0);
}

void GISASSimulation::initialize()
{
    setName(BornAgain::GISASSimulationType);
}

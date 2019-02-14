// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularSimulation.h"
#include "Distributions.h"
#include "Histogram1D.h"
#include "IBackground.h"
#include "IFootprintFactor.h"
#include "IMultiLayerBuilder.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "MaterialUtils.h"
#include "ParameterPool.h"
#include "PointwiseAxis.h"
#include "RealParameter.h"
#include "SpecularComputation.h"
#include "SpecularDataHandler.h"
#include "SpecularDetector1D.h"
#include "SpecularSimulationElement.h"
#include "UnitConverter1D.h"

namespace
{
const RealLimits alpha_limits = RealLimits::limited(0.0, M_PI_2);
const double zero_phi_i = 0.0;
const double zero_alpha_i = 0.0;
}

SpecularSimulation::SpecularSimulation() : Simulation()
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const MultiLayer& sample) : Simulation(sample)
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
    : Simulation(sample_builder)
{
    initialize();
}

SpecularSimulation::~SpecularSimulation() = default;

SpecularSimulation* SpecularSimulation::clone() const
{
    return new SpecularSimulation(*this);
}

void SpecularSimulation::prepareSimulation()
{
    if (m_instrument.getDetectorDimension() != 1) // detector must have only one axis
        throw std::runtime_error("Error in SpecularSimulation::prepareSimulation: the detector was "
                                 "not properly configured.");
    getInstrument().initDetector();
    Simulation::prepareSimulation();
    const MultiLayer* sample = m_sample_provider.sample();
    if (sample->containsMagneticMaterial() || sample->externalField() != kvector_t{})
        throw std::runtime_error("Error in SpecularSimulation::prepareSimulation: magnetized "
                                 "samples are not currently handled.");
}

size_t SpecularSimulation::numberOfSimulationElements() const
{
    return getAlphaAxis()->size();
}

SimulationResult SpecularSimulation::result() const
{
    auto data = createIntensityData();
    UnitConverter1D converter(m_instrument.getBeam(), *getAlphaAxis());
    return SimulationResult(*data, converter);
}

void SpecularSimulation::setBeamParameters(double lambda, const IAxis& alpha_axis,
                                           const IFootprintFactor* beam_shape)
{
    if (lambda <= 0.0)
        throw std::runtime_error(
            "Error in SpecularSimulation::setBeamParameters: wavelength must be positive.");
    if (alpha_axis.getMin() < 0.0)
        throw std::runtime_error("Error in SpecularSimulation::setBeamParameters: minimum value on "
                                 "angle axis is negative.");
    if (alpha_axis.getMin() >= alpha_axis.getMax())
        throw std::runtime_error("Error in SpecularSimulation::setBeamParameters: maximal value on "
                                 "angle axis is less or equal to the minimal one.");
    if (alpha_axis.size() == 0)
        throw std::runtime_error(
            "Error in SpecularSimulation::setBeamParameters: angle axis is empty");

    SpecularDetector1D detector(alpha_axis);
    m_instrument.setDetector(detector);
    m_data_handler = std::make_unique<SpecularDataHandlerAng>(
        lambda, std::unique_ptr<IAxis>(alpha_axis.clone()));

    // beam is initialized with zero-valued angles
    // Zero-valued incident alpha is required for proper
    // taking into account beam resolution effects
    m_instrument.setBeamParameters(lambda, zero_alpha_i, zero_phi_i);

    if (beam_shape)
        m_instrument.getBeam().setFootprintFactor(*beam_shape);
}

void SpecularSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min,
                                           double alpha_i_max, const IFootprintFactor* beam_shape)
{
    FixedBinAxis axis("alpha_i", static_cast<size_t>(nbins), alpha_i_min, alpha_i_max);
    setBeamParameters(lambda, axis, beam_shape);
}

void SpecularSimulation::setBeamParameters(double lambda, std::vector<double> incident_angle_values,
                                           const IFootprintFactor* beam_shape)
{
    PointwiseAxis axis("alpha_i", std::move(incident_angle_values));
    setBeamParameters(lambda, axis, beam_shape);
}

const IAxis* SpecularSimulation::getAlphaAxis() const
{
    if (!m_data_handler)
        throw std::runtime_error(
            "Error in SpecularSimulation::getAlphaAxis: coordinate axis was not initialized.");
    return m_data_handler->coordinateAxis();
}

void SpecularSimulation::initSimulationElementVector()
{
    const auto& beam = m_instrument.getBeam();
    m_sim_elements = generateSimulationElements(beam);

    if (!m_cache.empty())
        return;
    m_cache.resize(m_sim_elements.size(), 0);
}

std::vector<SpecularSimulationElement>
SpecularSimulation::generateSimulationElements(const Beam& beam)
{
    if (!m_data_handler)
        throw std::runtime_error("Error in SpecularSimulation::generateSimulationElements: beam "
                                 "parameters were not set.");

    // TODO: remove when pointwise resolution is implemented
    if (m_data_handler->dataType() == SPECULAR_DATA_TYPE::angle) {
        const double wl = beam.getWavelength();
        const double angle_shift = beam.getAlpha();
        std::vector<double> angles = m_data_handler->coordinateAxis()->getBinCenters();
        for (auto& val: angles)
            val += angle_shift;
        SpecularDataHandlerAng data_handler(
            wl, std::make_unique<PointwiseAxis>("alpha_i", std::move(angles)));
        return data_handler.generateSimulationElements();
    }

    return m_data_handler->generateSimulationElements();
}

std::unique_ptr<IComputation>
SpecularSimulation::generateSingleThreadedComputation(size_t start, size_t n_elements)
{
    assert(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    return std::make_unique<SpecularComputation>(*sample(), m_options, m_progress, begin,
                                                 begin + static_cast<long>(n_elements));
}

SpecularSimulation::SpecularSimulation(const SpecularSimulation& other)
    : Simulation(other)
    , m_sim_elements(other.m_sim_elements)
    , m_cache(other.m_cache)
{
    if (other.m_data_handler)
        m_data_handler.reset(other.m_data_handler->clone());
    initialize();
}

void SpecularSimulation::checkCache() const
{
    if (m_sim_elements.size() != m_cache.size())
        throw std::runtime_error("Error in SpecularSimulation: the sizes of simulation element "
                                 "vector and of its cache are different");
}

void SpecularSimulation::validateParametrization(const ParameterDistribution& par_distr) const
{
    const bool zero_mean = par_distr.getDistribution()->getMean() == 0.0;
    if (zero_mean)
        return;

    std::unique_ptr<ParameterPool> parameter_pool(createParameterTree());
    const std::vector<RealParameter*> names
        = parameter_pool->getMatchedParameters(par_distr.getMainParameterName());
    for (const auto par : names)
        if (par->getName().find(BornAgain::Inclination) != std::string::npos && !zero_mean)
            throw std::runtime_error("Error in SpecularSimulation: parameter distribution of "
                                     "beam inclination angle should have zero mean.");
}

void SpecularSimulation::initialize()
{
    setName(BornAgain::SpecularSimulationType);

    // allow for negative inclinations in the beam of specular simulation
    // it is required for proper averaging in the case of divergent beam
    auto inclination = m_instrument.getBeam().parameter(BornAgain::Inclination);
    inclination->setLimits(RealLimits::limited(-M_PI_2, M_PI_2));
}

void SpecularSimulation::normalizeIntensity(size_t index, double beam_intensity)
{
    auto& element = m_sim_elements[index];
    const double alpha_i = incidentAngle(index);
    const auto footprint = m_instrument.getBeam().footprintFactor();
    if (footprint != nullptr)
        beam_intensity *= footprint->calculate(alpha_i);
    element.setIntensity(element.getIntensity() * beam_intensity);
}

void SpecularSimulation::addBackGroundIntensity(size_t start_ind, size_t n_elements)
{
    if (!mP_background)
        return;
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        auto& element = m_sim_elements[i];
        element.setIntensity(mP_background->addBackGround(element.getIntensity()));
    }
}

void SpecularSimulation::addDataToCache(double weight)
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_cache[i] += m_sim_elements[i].getIntensity() * weight;
}

void SpecularSimulation::moveDataFromCache()
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_sim_elements[i].setIntensity(m_cache[i]);
    m_cache.clear();
    m_cache.shrink_to_fit();
}

double SpecularSimulation::incidentAngle(size_t index) const
{
    return getAlphaAxis()->getBinCenter(index);
}

std::unique_ptr<OutputData<double>> SpecularSimulation::createIntensityData() const
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(*getAlphaAxis());

    if (!m_sim_elements.empty()) {
        size_t i = 0;
        for (auto iter = m_sim_elements.begin(); iter != m_sim_elements.end(); ++iter, ++i)
            result->operator[](i) = iter->getIntensity();
    } else
        result->setAllTo(0.0);

    return result;
}

std::vector<double> SpecularSimulation::rawResults() const
{
    std::vector<double> result;
    result.resize(m_sim_elements.size());
    for (unsigned i=0; i<m_sim_elements.size(); ++i) {
        result[i] = m_sim_elements[i].getIntensity();
    }
    return result;
}

void SpecularSimulation::setRawResults(const std::vector<double>& raw_data)
{
    initSimulationElementVector();
    if (raw_data.size() != m_sim_elements.size())
        throw std::runtime_error("SpecularSimulation::setRawResults: size of vector passed as "
                                 "argument doesn't match number of elements in this simulation");
    for (unsigned i=0; i<raw_data.size(); i++) {
        m_sim_elements[i].setIntensity(raw_data[i]);
    }
    transferResultsToIntensityMap();
}

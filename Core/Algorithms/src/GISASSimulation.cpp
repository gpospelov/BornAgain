// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GISASSimulation.h"

#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "DWBASimulation.h"
#include "MessageService.h"
#include "OutputDataFunctions.h"
#include "BornAgainNamespace.h"
#include "ProgressHandlerDWBA.h"
#include "OMPISimulation.h"

#include "Macros.h"
GCC_DIAG_OFF(strict-aliasing);
#include <boost/thread.hpp>
GCC_DIAG_ON(strict-aliasing);
#include <gsl/gsl_errno.h>

GISASSimulation::GISASSimulation()
: m_instrument()
, m_intensity_map()
{
    setName("GISASSimulation");
    init_parameters();
}

GISASSimulation::GISASSimulation(const ProgramOptions *p_options)
: Simulation(p_options)
, m_instrument()
, m_intensity_map()
{
    setName("GISASSimulation");
    init_parameters();
}

GISASSimulation::GISASSimulation(
    const ISample& p_sample, const ProgramOptions *p_options)
: Simulation(p_sample, p_options)
, m_instrument()
, m_intensity_map()
{
    setName("GISASSimulation");
    init_parameters();
}

GISASSimulation::GISASSimulation(
    SampleBuilder_t p_sample_builder, const ProgramOptions *p_options)
: Simulation(p_sample_builder, p_options)
, m_instrument()
, m_intensity_map()
{
    setName("GISASSimulation");
    init_parameters();
}

GISASSimulation *GISASSimulation::clone() const
{
    return new GISASSimulation(*this);
}

void GISASSimulation::prepareSimulation()
{
    if(m_instrument.getDetectorDimension() != 2) {
        throw LogicErrorException("GISASSimulation::prepareSimulation() "
                "-> Error. The detector was not properly configured.");
    }
    if (getWavelength() <= 0.0) {
        throw ClassInitializationException(
                "GISASSimulation::prepareSimulation() "
                "-> Error. Incoming wavelength <= 0.");
    }
    Simulation::prepareSimulation();
}

void GISASSimulation::normalize()
{
    if (!m_is_normalized) {
        m_instrument.normalize(&m_intensity_map);
        m_is_normalized = true;
    }
}

int GISASSimulation::getNumberOfSimulationElements() const
{
    if (m_instrument.getDetectorDimension()!=2) {
        throw RuntimeErrorException("GISASSimulation::getNumberOfSimulationElements: "
                                    "detector is not two-dimensional");
    }
    const IAxis &phi_axis = m_instrument.getDetectorAxis(0);
    if (phi_axis.getName()!=BornAgain::PHI_AXIS_NAME) {
        throw RuntimeErrorException("GISASSimulation::getNumberOfSimulationElements: "
                                    "phi-axis is not correct");
    }
    const IAxis &alpha_axis = m_instrument.getDetectorAxis(1);
    if (alpha_axis.getName()!=BornAgain::ALPHA_AXIS_NAME) {
        throw RuntimeErrorException("GISASSimulation::getNumberOfSimulationElements: "
                                    "alpha-axis is not correct");
    }
    return phi_axis.getSize()*alpha_axis.getSize();
}

OutputData<double> *GISASSimulation::getIntensityData() const
{
    OutputData<double> *result = m_intensity_map.clone();
    m_instrument.applyDetectorResolution(result);
    return result;
}

void GISASSimulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMap();
}

void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength<=0.0) {
        throw ClassInitializationException(
                "Simulation::setBeamParameters() "
                "-> Error. Incoming wavelength <= 0.");
    }

    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
}

void GISASSimulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

void GISASSimulation::setBeamPolarization(const kvector_t &bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

void GISASSimulation::setDetectorParameters(const OutputData<double >& output_data)
{
    m_instrument.matchDetectorParameters(output_data);

    m_intensity_map.clear();
    m_intensity_map.copyShapeFrom(output_data); // to copy mask too
    m_intensity_map.setAllTo(0.);
}

void GISASSimulation::setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
                                            size_t n_alpha, double alpha_f_min, double alpha_f_max,
                                            bool isgisaxs_style)
{
    m_instrument.setDetectorParameters(n_phi, phi_f_min, phi_f_max, n_alpha, alpha_f_min,
                                       alpha_f_max, isgisaxs_style);
    updateIntensityMap();
}

void GISASSimulation::setDetectorResolutionFunction(
    const IResolutionFunction2D &resolution_function)
{
    m_instrument.setDetectorResolutionFunction(resolution_function);
}

void GISASSimulation::removeDetectorResolutionFunction()
{
    m_instrument.setDetectorResolutionFunction(0);
}

void GISASSimulation::setAnalyzerProperties(const kvector_t &direction, double efficiency,
                                       double total_transmission)
{
    m_instrument.setAnalyzerProperties(direction, efficiency, total_transmission);
}

std::string GISASSimulation::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path =
        IParameterized::addParametersToExternalPool(
            path, external_pool, copy_number);

    // add parameters of the instrument
    m_instrument.addParametersToExternalPool(new_path, external_pool, -1);

    if (mp_sample_builder.get()) {
       // add parameters of the sample builder
        mp_sample_builder->addParametersToExternalPool(
            new_path, external_pool, -1);
    } else if (mp_sample) {
        // add parameters of directly the sample
        mp_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

double GISASSimulation::getWavelength() const
{
    return m_instrument.getBeam().getWavelength();
}

GISASSimulation::GISASSimulation(const GISASSimulation& other)
: Simulation(other)
, m_instrument(other.m_instrument)
, m_intensity_map()
{
    m_intensity_map.copyFrom(other.m_intensity_map);

    setName("GISASSimulation");
    init_parameters();
}

void GISASSimulation::init_parameters()
{
}

void GISASSimulation::initSimulationElementVector()
{
    m_sim_elements.clear();
    Beam beam = m_instrument.getBeam();
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    Eigen::Matrix2cd analyzer_operator = m_instrument.getDetector().getAnalyzerOperator();

    if (m_instrument.getDetectorDimension()!=2) {
        throw RuntimeErrorException("GISASSimulation::initSimulationElementVector: "
                                    "detector is not two-dimensional");
    }
    const IAxis &phi_axis = m_instrument.getDetectorAxis(0);
    if (phi_axis.getName()!=BornAgain::PHI_AXIS_NAME) {
        throw RuntimeErrorException("GISASSimulation::initSimulationElementVector: "
                                    "phi-axis is not correct");
    }
    const IAxis &alpha_axis = m_instrument.getDetectorAxis(1);
    if (alpha_axis.getName()!=BornAgain::ALPHA_AXIS_NAME) {
        throw RuntimeErrorException("GISASSimulation::initSimulationElementVector: "
                                    "alpha-axis is not correct");
    }
    for (size_t phi_index = 0; phi_index < phi_axis.getSize(); ++phi_index) {
        Bin1D phi_bin = phi_axis.getBin(phi_index);
        for (size_t alpha_index = 0; alpha_index < alpha_axis.getSize(); ++alpha_index) {
            Bin1D alpha_bin = alpha_axis.getBin(alpha_index);
            SimulationElement sim_element(wavelength, alpha_i, phi_i, alpha_bin.m_lower,
                                          alpha_bin.m_upper, phi_bin.m_lower, phi_bin.m_upper);
            sim_element.setPolarization(beam_polarization);
            sim_element.setAnalyzerOperator(analyzer_operator);
            m_sim_elements.push_back(sim_element);
        }
    }
}

void GISASSimulation::transferResultsToIntensityMap()
{
    size_t detector_dimension = m_instrument.getDetectorDimension();
    if (detector_dimension!=2) {
        throw RuntimeErrorException("GISASSimulation::transferResultsToIntensityMap: "
                                    "detector is not two-dimensional");
    }
    updateIntensityMap();
    if (m_intensity_map.getAllocatedSize()!=m_sim_elements.size()) {
        throw RuntimeErrorException("GISASSimulation::transferResultsToIntensityMap: "
                                    "intensity map has different size than number of "
                                    "calculated intensities");
    }
    for (size_t i=0; i<m_sim_elements.size(); ++i) {
        m_intensity_map[i] = m_sim_elements[i].getIntensity();
    }
}

void GISASSimulation::updateIntensityMap()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
    }
    m_intensity_map.setAllTo(0.);
}

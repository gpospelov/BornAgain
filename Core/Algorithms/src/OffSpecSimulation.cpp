// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/OffSpecSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OffSpecSimulation.h"
#include "OutputDataFunctions.h"
#include "BornAgainNamespace.h"

#include <boost/scoped_ptr.hpp>

OffSpecSimulation::OffSpecSimulation()
: m_instrument()
, mp_alpha_i_axis(0)
, m_intensity_map()
{
    setName("OffSpecSimulation");
    init_parameters();
}

OffSpecSimulation::OffSpecSimulation(const ProgramOptions* p_options)
: Simulation(p_options)
, m_instrument()
, mp_alpha_i_axis(0)
, m_intensity_map()
{
    setName("OffSpecSimulation");
    init_parameters();
}

OffSpecSimulation::OffSpecSimulation(const ISample& p_sample,
        const ProgramOptions* p_options)
: Simulation(p_sample, p_options)
, m_instrument()
, mp_alpha_i_axis(0)
, m_intensity_map()
{
    setName("OffSpecSimulation");
    init_parameters();
}

OffSpecSimulation::OffSpecSimulation(SampleBuilder_t p_sample_builder,
        const ProgramOptions* p_options)
: Simulation(p_sample_builder, p_options)
, m_instrument()
, mp_alpha_i_axis(0)
, m_intensity_map()
{
    setName("OffSpecSimulation");
    init_parameters();
}

OffSpecSimulation* OffSpecSimulation::clone() const
{
    return new OffSpecSimulation(*this);
}

void OffSpecSimulation::prepareSimulation()
{
    checkInitialization();
    if (getWavelength() <= 0.0) {
        throw ClassInitializationException(
                "OffSpecSimulation::prepareSimulation() "
                "-> Error. Incoming wavelength <= 0.");
    }
    Simulation::prepareSimulation();
}

int OffSpecSimulation::getNumberOfSimulationElements() const
{
    checkInitialization();
    const IAxis &phi_axis = m_instrument.getDetectorAxis(0);
    const IAxis &alpha_axis = m_instrument.getDetectorAxis(1);
    return phi_axis.getSize()*alpha_axis.getSize()*mp_alpha_i_axis->getSize();
}

OutputData<double> *OffSpecSimulation::getIntensityData() const
{
    OutputData<double> *result = m_intensity_map.clone();
    return result;
}

void OffSpecSimulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMap();
}

void OffSpecSimulation::setBeamParameters(
        double lambda, const IAxis &alpha_axis, double phi_i) {
    delete mp_alpha_i_axis;
    mp_alpha_i_axis = alpha_axis.clone();
    if (alpha_axis.getSize()<1) {
        throw ClassInitializationException(
                "OffSpecSimulation::prepareSimulation() "
                "-> Error. Incoming alpha range size < 1.");
    }
    double alpha_start = alpha_axis[0];
    m_instrument.setBeamParameters(lambda, alpha_start, phi_i);
    updateIntensityMap();
}

void OffSpecSimulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

void OffSpecSimulation::setBeamPolarization(const kvector_t &bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

void OffSpecSimulation::setDetectorParameters(const OutputData<double>& output_data)
{
    m_instrument.matchDetectorParameters(output_data);
    updateIntensityMap();
}

void OffSpecSimulation::setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
                                              size_t n_alpha, double alpha_f_min,
                                              double alpha_f_max, bool isgisaxs_style)
{
    m_instrument.setDetectorParameters(n_phi, phi_f_min, phi_f_max, n_alpha, alpha_f_min,
                                       alpha_f_max, isgisaxs_style);
    updateIntensityMap();
}

void OffSpecSimulation::setDetectorParameters(const DetectorParameters& params)
{
    m_instrument.setDetectorParameters(params);
    updateIntensityMap();
}

void OffSpecSimulation::setDetectorResolutionFunction(
        const IResolutionFunction2D &resolution_function)
{
    m_instrument.setDetectorResolutionFunction(resolution_function);
}

void OffSpecSimulation::removeDetectorResolutionFunction()
{
    m_instrument.setDetectorResolutionFunction(0);
}

void OffSpecSimulation::setAnalyzerProperties(const kvector_t &direction, double efficiency,
                                              double total_transmission)
{
    m_instrument.setAnalyzerProperties(direction, efficiency, total_transmission);
}

std::string OffSpecSimulation::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
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

double OffSpecSimulation::getWavelength() const
{
    return m_instrument.getBeam().getWavelength();
}

OffSpecSimulation::OffSpecSimulation(const OffSpecSimulation& other)
: Simulation(other)
, m_instrument(other.m_instrument)
, mp_alpha_i_axis(0)
, m_intensity_map()
{
    if(other.mp_alpha_i_axis) mp_alpha_i_axis = other.mp_alpha_i_axis->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);

    setName("OffSpecSimulation");
    init_parameters();
}

void OffSpecSimulation::init_parameters()
{
}

void OffSpecSimulation::initSimulationElementVector()
{
    m_sim_elements.clear();
    Beam beam = m_instrument.getBeam();
    double wavelength = beam.getWavelength();
    double phi_i = beam.getPhi();
    Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    Eigen::Matrix2cd analyzer_operator = m_instrument.getDetector().getAnalyzerOperator();
    checkInitialization();

    const IAxis &phi_axis = m_instrument.getDetectorAxis(0);
    const IAxis &alpha_axis = m_instrument.getDetectorAxis(1);
    for (size_t alpha_i_index = 0; alpha_i_index < mp_alpha_i_axis->getSize(); ++alpha_i_index) {
        // Incoming angle by convention defined as positive:
        double alpha_i = - mp_alpha_i_axis->getBin(alpha_i_index).getMidPoint();
        for (size_t phi_f_index = 0; phi_f_index < phi_axis.getSize(); ++phi_f_index) {
            Bin1D phi_bin = phi_axis.getBin(phi_f_index);
            for (size_t alpha_f_index = 0; alpha_f_index < alpha_axis.getSize(); ++alpha_f_index) {
                Bin1D alpha_bin = alpha_axis.getBin(alpha_f_index);
                SimulationElement sim_element(wavelength, alpha_i, phi_i, alpha_bin.m_lower,
                                              alpha_bin.m_upper, phi_bin.m_lower, phi_bin.m_upper);
                sim_element.setPolarization(beam_polarization);
                sim_element.setAnalyzerOperator(analyzer_operator);
                m_sim_elements.push_back(sim_element);
            }
        }
    }
}

void OffSpecSimulation::transferResultsToIntensityMap()
{
    checkInitialization();
    updateIntensityMap();
    const IAxis &phi_axis = m_instrument.getDetectorAxis(0);
    size_t phi_f_size = phi_axis.getSize();
    if (phi_f_size*m_intensity_map.getAllocatedSize()!=m_sim_elements.size()) {
        throw RuntimeErrorException("OffSpecSimulation::transferResultsToIntensityMap: "
                                    "intensity map size does not conform to number of "
                                    "calculated intensities");
    }
    for (size_t i=0; i<mp_alpha_i_axis->getSize(); ++i) {
        normalizeAndTransferDetectorImage(i);
    }
}

void OffSpecSimulation::updateIntensityMap()
{
    m_intensity_map.clear();
    if (mp_alpha_i_axis) {
        m_intensity_map.addAxis(*mp_alpha_i_axis);
    }
    size_t detector_dimension = m_instrument.getDetectorDimension();
    if (detector_dimension==2) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(1));
    }
    m_intensity_map.setAllTo(0.);
}

void OffSpecSimulation::normalizeAndTransferDetectorImage(int index)
{
    OutputData<double> detector_image;
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        detector_image.addAxis(m_instrument.getDetectorAxis(dim));
    }
    size_t detector_size = detector_image.getAllocatedSize();
    for (size_t i=0; i<detector_size; ++i) {
        detector_image[i] = m_sim_elements[index*detector_size + i].getIntensity();
    }
    Beam beam = m_instrument.getBeam();
    double wavelength = beam.getWavelength();
    double phi_i = beam.getPhi();
    double alpha_i = mp_alpha_i_axis->getBin(index).getMidPoint();
    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
    m_instrument.normalize(&detector_image);
    m_instrument.applyDetectorResolution(&detector_image);
    size_t alpha_f_size = m_instrument.getDetectorAxis(1).getSize();
    for (size_t i=0; i<detector_size; ++i) {
        m_intensity_map[index*alpha_f_size + i%alpha_f_size] += detector_image[i];
    }
}

void OffSpecSimulation::checkInitialization() const
{
    if (!mp_alpha_i_axis || mp_alpha_i_axis->getSize()<1) {
        throw ClassInitializationException(
                "OffSpecSimulation::checkInitialization() "
                "Incoming alpha range not configured.");
    }
    if (m_instrument.getDetectorDimension()!=2) {
        throw RuntimeErrorException("OffSpecSimulation::checkInitialization: "
                                    "detector is not two-dimensional");
    }
    const IAxis &phi_axis = m_instrument.getDetectorAxis(0);
    if (phi_axis.getName()!=BornAgain::PHI_AXIS_NAME) {
        throw RuntimeErrorException("OffSpecSimulation::checkInitialization: "
                                    "phi-axis is not correct");
    }
    const IAxis &alpha_axis = m_instrument.getDetectorAxis(1);
    if (alpha_axis.getName()!=BornAgain::ALPHA_AXIS_NAME) {
        throw RuntimeErrorException("OffSpecSimulation::checkInitialization: "
                                    "alpha-axis is not correct");
    }
}

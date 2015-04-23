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
#include <boost/scoped_ptr.hpp>

OffSpecSimulation::OffSpecSimulation()
: IParameterized("OffSpecSimulation")
, m_simulation()
, mp_alpha_i_axis(0)
, m_lambda(0.0)
, m_phi(0.0)
{
    init_parameters();
}

OffSpecSimulation::OffSpecSimulation(const ProgramOptions* p_options)
: IParameterized("OffSpecSimulation")
, m_simulation(p_options)
, mp_alpha_i_axis(0)
, m_lambda(0.0)
, m_phi(0.0)
{
    init_parameters();
}

OffSpecSimulation::OffSpecSimulation(const ISample& p_sample,
        const ProgramOptions* p_options)
: IParameterized("OffSpecSimulation")
, m_simulation(p_sample, p_options)
, mp_alpha_i_axis(0)
, m_lambda(0.0)
, m_phi(0.0)
{
    init_parameters();
}

OffSpecSimulation::OffSpecSimulation(SampleBuilder_t p_sample_builder,
        const ProgramOptions* p_options)
: IParameterized("OffSpecSimulation")
, m_simulation(p_sample_builder, p_options)
, mp_alpha_i_axis(0)
, m_lambda(0.0)
, m_phi(0.0)
{
    init_parameters();
}

OffSpecSimulation* OffSpecSimulation::clone() const
{
    return new OffSpecSimulation(*this);
}

void OffSpecSimulation::prepareSimulation()
{
    if (!mp_alpha_i_axis || mp_alpha_i_axis->getSize()<1) {
        throw ClassInitializationException(
                "OffSpecSimulation::prepareSimulation() "
                "-> Error. Incoming alpha range not configured.");
    }
    if (m_lambda<=0.0) {
        throw ClassInitializationException(
                "OffSpecSimulation::prepareSimulation() "
                "-> Error. Incoming wavelength < 0.");
    }
}

void OffSpecSimulation::runSimulation()
{
    prepareSimulation();

    for (size_t i=0; i<mp_alpha_i_axis->getSize(); ++i) {
        double alpha = (*mp_alpha_i_axis)[i];
        m_simulation.setBeamParameters(m_lambda, alpha, m_phi);
        m_simulation.runSimulation();
        m_simulation.normalize();
        addIntegratedIntensity(i);
    }
}

OutputData<double> *OffSpecSimulation::getIntensityData() const
{
    OutputData<double> *result = m_intensity_map.clone();
    return result;
}

OutputData<double>* OffSpecSimulation::getPolarizedIntensityData(
        int row, int column) const
{
    const OutputData<Eigen::Matrix2d > *p_data_pol = getPolarizedOutputData();
    OutputData<double > *result =
            OutputDataFunctions::getComponentData(*p_data_pol, row, column);
    return result;
}

void OffSpecSimulation::setInstrument(const Instrument& instrument) {
    m_simulation.setInstrument(instrument);
    updateIntensityMapAxes();
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
    m_simulation.setBeamParameters(lambda, alpha_start, phi_i);
    m_lambda = lambda;
    m_phi = phi_i;
    updateIntensityMapAxes();
}

void OffSpecSimulation::setDetectorParameters(
        const OutputData<double>& output_data)
{
    m_simulation.setDetectorParameters(output_data);
    updateIntensityMapAxes();
}

void OffSpecSimulation::setDetectorParameters(size_t n_phi, double phi_f_min,
        double phi_f_max, size_t n_alpha, double alpha_f_min,
        double alpha_f_max, bool isgisaxs_style)
{
    m_simulation.setDetectorParameters(n_phi, phi_f_min, phi_f_max,
            n_alpha, alpha_f_min, alpha_f_max, isgisaxs_style);
    updateIntensityMapAxes();
}

void OffSpecSimulation::setDetectorParameters(
        const DetectorParameters& params)
{
    m_simulation.setDetectorParameters(params);
    updateIntensityMapAxes();
}

std::string OffSpecSimulation::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path =
        IParameterized::addParametersToExternalPool(
            path, external_pool, copy_number);

    // add parameters of the embedded simulation object
    m_simulation.addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

OffSpecSimulation::OffSpecSimulation(const OffSpecSimulation& other)
: ICloneable(), IParameterized(other)
, m_simulation(other.m_simulation)
, mp_alpha_i_axis(0)
, m_lambda(other.m_lambda)
, m_phi(other.m_phi)
, m_intensity_map()
, m_polarized_intensity()
{
    if(other.mp_alpha_i_axis) mp_alpha_i_axis = other.mp_alpha_i_axis->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);
    m_polarized_intensity.copyFrom(other.m_polarized_intensity);

    init_parameters();
}

void OffSpecSimulation::init_parameters()
{
}

void OffSpecSimulation::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    if (mp_alpha_i_axis) {
        m_intensity_map.addAxis(*mp_alpha_i_axis);
    }
    const Instrument &instrument = m_simulation.getInstrument();
    size_t detector_dimension = instrument.getDetectorDimension();
    if (detector_dimension==2) {
        m_intensity_map.addAxis(instrument.getDetectorAxis(1));
    }
    m_intensity_map.setAllTo(0.);
}

void OffSpecSimulation::addIntegratedIntensity(size_t index)
{
    boost::scoped_ptr<OutputData<double> > intensity(m_simulation.getOutputData()->clone());

    getInstrument().applyDetectorResolution(intensity.get());

    if (intensity->getRank() != 2) {
        throw LogicErrorException("Embedded GISAS simulation does not"
                " have a two dimensional detector.");
    }
    std::vector<int> offspec_coordinates;
    offspec_coordinates.resize(2);
    offspec_coordinates[0] = (int)index;
    size_t phi_axis_size = intensity->getAxis(0)->getSize();
    size_t alphaf_axis_size = intensity->getAxis(1)->getSize();
    for (size_t alphaf_index=0; alphaf_index<alphaf_axis_size; ++alphaf_index) {
        offspec_coordinates[1] = alphaf_index;
        size_t destination_index = m_intensity_map.toIndex(offspec_coordinates);
        std::vector<int> gisas_coordinates;
        gisas_coordinates.resize(2);
        gisas_coordinates[1] = alphaf_index;
        double sum = 0.0;
        for (size_t phi_index=0; phi_index<phi_axis_size; ++phi_index) {
            gisas_coordinates[0] = phi_index;
            size_t source_index = intensity->toIndex(gisas_coordinates);
            sum += (*intensity)[source_index];
        }
        m_intensity_map[destination_index] = sum;
    }
}

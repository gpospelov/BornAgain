// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DWBASimulation.cpp
//! @brief     Implements class DWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DWBASimulation.h"


DWBASimulation::DWBASimulation()
: mp_polarization_output(0)
, m_alpha_i(0)
, m_thread_info()
, mp_simulation(0)
{
}

DWBASimulation::~DWBASimulation()
{
       delete mp_polarization_output;
       delete mp_simulation;
}

void DWBASimulation::init(const Simulation& simulation)
{
    if (mp_simulation !=& simulation) {
        delete mp_simulation;
        mp_simulation = simulation.clone();
    }
    if (mp_polarization_output) {
        delete mp_polarization_output;
        mp_polarization_output = 0;
    }
    m_dwba_intensity.clear();
    Detector detector = simulation.getInstrument().getDetector();
    size_t detector_dimension = detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_dwba_intensity.addAxis(detector.getAxis(dim));
    }
    if (simulation.getOutputData()->getMask()) {
        m_dwba_intensity.setMask(*simulation.getOutputData()->getMask());
    }
    Beam beam = simulation.getInstrument().getBeam();
    m_ki = beam.getCentralK();
    kvector_t ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    m_alpha_i = std::asin(ki_real.z()/ki_real.mag());
    m_sim_params = simulation.getSimulationParameters();

    // initialize polarization output if needed
    if (checkPolarizationPresent()) {
        mp_polarization_output = new OutputData<Eigen::Matrix2d>();
        for (size_t dim=0; dim<detector_dimension; ++dim) {
            mp_polarization_output->addAxis(detector.getAxis(dim));
        }
        if (simulation.getOutputData()->getMask()) {
            mp_polarization_output->setMask(*simulation.getOutputData()->getMask());
        }
    }
}

const OutputData<double>& DWBASimulation::getDWBAIntensity() const
{
    if (mp_polarization_output) return getPolarizationData();
    return m_dwba_intensity;
}

DWBASimulation *DWBASimulation::clone() const
{
    DWBASimulation *p_result = new DWBASimulation();
    p_result->m_dwba_intensity.copyFrom(m_dwba_intensity);
    p_result->m_ki = m_ki;
    p_result->m_alpha_i = m_alpha_i;
    p_result->m_thread_info = m_thread_info;
    if (mp_simulation)
        p_result->mp_simulation = mp_simulation->clone();
    return p_result;
}

bool DWBASimulation::checkPolarizationPresent() const
{
    if (!mp_simulation) {
        throw ClassInitializationException("DWBASimulation::"
                "checkPolarizationPresent(): simulation not initialized");
    }
    ISample *p_sample = mp_simulation->getSample();
    if (!p_sample) {
        throw ClassInitializationException("DWBASimulation::"
                "checkPolarizationPresent(): sample not initialized");
    }
    return p_sample->containsMagneticMaterial();
}

double DWBASimulation::getWaveLength() const
{
    kvector_t real_ki(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    return 2*M_PI/real_ki.mag();
}

const OutputData<double>& DWBASimulation::getPolarizationData() const
{
    Eigen::Matrix2cd pol_density = mp_simulation->getInstrument()
            .getBeam().getPolarization();
    OutputData<double>::iterator it = m_dwba_intensity.begin();
    OutputData<Eigen::Matrix2d>::const_iterator mat_it =
            mp_polarization_output->begin();
    while (it != m_dwba_intensity.end()) {
        Eigen::Matrix2cd mat = pol_density * (*mat_it);
        *it = std::abs(mat.trace());
        ++it, ++mat_it;
    }
    return m_dwba_intensity;
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DWBASimulation.cpp
//! @brief     Implements class DWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DWBASimulation.h"


DWBASimulation::DWBASimulation()
: m_alpha_i(0)
, m_thread_info()
, mp_simulation(0)
{
    m_beam_polarization.setZero();
    m_detector_polarization.setZero();
}

DWBASimulation::~DWBASimulation()
{
       delete mp_simulation;
}

void DWBASimulation::init(const GISASSimulation& simulation,
                          std::vector<SimulationElement>::iterator begin_it,
                          std::vector<SimulationElement>::iterator end_it)
{
    if (mp_simulation != &simulation) {
        delete mp_simulation;
        mp_simulation = simulation.clone();
    }
    m_begin_it = begin_it;
    m_end_it = end_it;
    m_dwba_intensity.clear();
    Detector detector = simulation.getInstrument().getDetector();
    size_t detector_dimension = detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_dwba_intensity.addAxis(detector.getAxis(dim));
    }
    if (simulation.getOutputData()->getMask()) {
        m_dwba_intensity.setMask(*simulation.getOutputData()->getMask());
    }
    m_detector_polarization = detector.getPolarizationOperator();
    Beam beam = simulation.getInstrument().getBeam();
    m_ki = beam.getCentralK();
    kvector_t ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    m_alpha_i = std::asin(ki_real.z()/ki_real.mag());
    m_beam_polarization = beam.getPolarization();
    m_sim_params = simulation.getSimulationParameters();

    // initialising call backs
    mp_simulation->initProgressHandlerDWBA(&m_progress);
}

const OutputData<double>& DWBASimulation::getDWBAIntensity() const
{
    return m_dwba_intensity;
}

DWBASimulation *DWBASimulation::clone() const
{
    DWBASimulation *p_result = new DWBASimulation();
    p_result->m_dwba_intensity.copyFrom(m_dwba_intensity);
    p_result->m_ki = m_ki;
    p_result->m_alpha_i = m_alpha_i;
    p_result->m_thread_info = m_thread_info;
    p_result->m_progress.setCallback(m_progress.getCallback());
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
    return Units::PI2/real_ki.mag();
}

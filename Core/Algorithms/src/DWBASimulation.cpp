#include "DWBASimulation.h"

DWBASimulation::DWBASimulation()
: m_alpha_i(0)
, m_thread_info()
, mp_experiment(0)
{
}

DWBASimulation::~DWBASimulation()
{
    delete mp_experiment;
}

void DWBASimulation::init(const Experiment& experiment)
{
    if (mp_experiment != &experiment) {
        delete mp_experiment;
        mp_experiment = experiment.clone();
    }
    m_dwba_intensity.clear();
    Detector detector = experiment.getDetector();
    size_t detector_dimension = detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_dwba_intensity.addAxis(detector.getAxis(dim));
    }
    if (experiment.getOutputData()->getMask()) {
        m_dwba_intensity.setMask(*experiment.getOutputData()->getMask());
    }
    Beam beam = experiment.getBeam();
    m_ki = beam.getCentralK();
    kvector_t ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    m_alpha_i = std::asin(ki_real.z()/ki_real.mag());
    m_sim_params = experiment.getSimulationParameters();
}

DWBASimulation *DWBASimulation::clone() const
{
    DWBASimulation *p_result = new DWBASimulation();
    p_result->m_dwba_intensity.copyFrom(m_dwba_intensity);
    p_result->m_ki = m_ki;
    p_result->m_alpha_i = m_alpha_i;
    p_result->m_thread_info = m_thread_info;
    if (mp_experiment) p_result->mp_experiment = mp_experiment->clone();

    return p_result;
}

DWBASimulation::iterator DWBASimulation::begin()
{
    if (m_thread_info.n_threads<2) {
        m_thread_info.n_threads = 1;
        m_thread_info.i_thread = 0;
    }
    iterator result(m_dwba_intensity.begin());
    if (m_thread_info.n_threads>1) {
        MaskIndexModulus thread_mask(m_thread_info.n_threads, m_thread_info.i_thread);
        result.addMask(thread_mask);
    }
    return result;
}

DWBASimulation::const_iterator DWBASimulation::begin() const
{
    size_t n_threads = m_thread_info.n_threads;
    size_t i_thread = m_thread_info.i_thread;
    if (m_thread_info.n_threads<2) {
        n_threads = 1;
        i_thread = 0;
    }
    const_iterator result(m_dwba_intensity.begin());
    if (n_threads>1) {
        MaskIndexModulus thread_mask(n_threads, i_thread);
        result.addMask(thread_mask);
    }
    return result;
}

double DWBASimulation::getWaveLength() const
{
    kvector_t real_ki(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    return 2.0*M_PI/real_ki.mag();
}

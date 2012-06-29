#include "DWBASimulation.h"

DWBASimulation::DWBASimulation()
{
}

DWBASimulation::~DWBASimulation()
{
}

void DWBASimulation::init(const Experiment& experiment)
{
    m_dwba_intensity.clear();
    m_dwba_amplitude.clear();
    Detector detector = experiment.getDetector();
    size_t detector_dimension = detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_dwba_intensity.addAxis(new NamedVector<double>(detector.getAxis(dim)));
        m_dwba_amplitude.addAxis(new NamedVector<double>(detector.getAxis(dim)));
    }
    Beam beam = experiment.getBeam();
    m_ki = beam.getCentralK();
    m_alpha_i = std::asin(m_ki.z()/m_ki.mag());
}

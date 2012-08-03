#include "Experiment.h"

Experiment::Experiment()
: mp_sample(0)
, m_is_normalized(false)
{
}

Experiment::Experiment(ISample* p_sample)
: mp_sample(p_sample)
, m_is_normalized(false)
{
}

void Experiment::runSimulation()
{
    m_is_normalized = false;
}

void Experiment::normalize()
{
    double incident_intensity = m_beam.getIntensity();
    if (!m_is_normalized && incident_intensity!=1.0) {
        m_intensity_map.resetIndex();
        while (m_intensity_map.hasNext()) {
            double old_value = m_intensity_map.currentValue();
            m_intensity_map.next() = incident_intensity*old_value;
        }
        m_is_normalized = true;
    }
}

void Experiment::setSample(ISample* p_sample)
{
	mp_sample = p_sample;  ///< Not owned by Experiment
}

OutputData<double>* Experiment::getOutputDataClone() const
{
	return m_intensity_map.clone();
}

const OutputData<double>* Experiment::getOutputData() const
{
    return &m_intensity_map;
}


void Experiment::setBeamParameters(double lambda, double alpha_i, double phi_i)
{
    m_beam.setCentralK(lambda, alpha_i, phi_i);
}

void Experiment::setBeamIntensity(double intensity)
{
    m_beam.setIntensity(intensity);
}

void Experiment::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(new NamedVector<double>(m_detector.getAxis(dim)));
    }
}


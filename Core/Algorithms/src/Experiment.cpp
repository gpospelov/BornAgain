#include "Experiment.h"

Experiment::Experiment()
: mp_sample(0)
{
}

Experiment::Experiment(ISample* p_sample)
: mp_sample(p_sample)
{
}

void Experiment::runSimulation()
{
}

void Experiment::setSample(ISample* p_sample)
{
	mp_sample = p_sample;  ///< Not owned by Experiment
}

OutputData<double>* Experiment::getOutputData() const
{
	return m_intensity_map.clone();
}

void Experiment::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(new NamedVector<double>(m_detector.getAxis(dim)));
    }
}


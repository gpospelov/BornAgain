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

//! The ISample object will not be owned by the Experiment object
void Experiment::setSample(ISample* p_sample)
{
	mp_sample = p_sample;
}

OutputData<double>* Experiment::getOutputDataClone() const
{
	return m_intensity_map.clone();
}

const OutputData<double>* Experiment::getOutputData() const
{
    return &m_intensity_map;
}


const OutputData<double>* Experiment::getOutputDataMask() const
{
    return &m_current_output_data_mask;
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
    m_intensity_map.setAllTo(0.0);
    // setting mask on output data
    setOutputDataMask();
}


/* ************************************************************************* */
// setting mask on output data: every 'n_chunk'th out of n_chunks_total
// if n_chunks_total=1, then all elements will be set to '1'
/* ************************************************************************* */
void Experiment::setOutputDataMask(size_t n_chunks_total, size_t n_chunk )
{
    if(n_chunks_total==0) throw RuntimeErrorException("Experiment::setOutputDataMask() -> Error! Number of chunks can not be zero");
    // copying topology from intensity data
    m_current_output_data_mask.copyFrom(m_intensity_map);
    // setting mask
    m_current_output_data_mask.setAllTo(0.0);
    m_current_output_data_mask.resetIndex();
    while(m_current_output_data_mask.hasNext()) {
        if(m_current_output_data_mask.getIndex().getPosition() % n_chunks_total == n_chunk) {
            m_current_output_data_mask.next() = 1;
        } else {
            m_current_output_data_mask.next();
        }
    }

}


/* ************************************************************************* */
// create combined parameter pool of the whole sample and experiment (if any)
/* ************************************************************************* */
ParameterPool *Experiment::createParameterTree() const
{
    if(mp_sample == 0 ) throw NullPointerException("Experiment::createParameterTree() -> Error! Sample is absent");
    return mp_sample->createParameterTree();
}


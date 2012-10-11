#include "Experiment.h"

Experiment::Experiment()
: mp_sample(0)
, mp_sample_builder(0)
, m_is_normalized(false)
{
    setName("Experiment");
    init_parameters();
}

Experiment::Experiment(ISample* p_sample)
: mp_sample(p_sample)
, mp_sample_builder(0)
, m_is_normalized(false)
{
    init_parameters();
}

Experiment::Experiment(ISampleBuilder* p_sample_builder)
: mp_sample(0)
, mp_sample_builder(p_sample_builder)
, m_is_normalized(false)
{
    init_parameters();
}

void Experiment::runSimulation()
{
    m_is_normalized = false;
    updateSample();
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
    if (mp_sample != p_sample) {
        delete mp_sample;
        mp_sample = p_sample;
        delete mp_sample_builder;
        mp_sample_builder = 0;
    }
}

void Experiment::setSampleBuilder(ISampleBuilder* p_sample_builder)
{
    if (mp_sample_builder != p_sample_builder) {
        delete mp_sample_builder;
        mp_sample_builder = p_sample_builder;
        delete mp_sample;
        mp_sample = 0;
    }
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

void Experiment::setBeamParameters(double lambda, double alpha_i, double phi_i)
{
    m_beam.setCentralK(lambda, alpha_i, phi_i);
}

void Experiment::setBeamIntensity(double intensity)
{
    m_beam.setIntensity(intensity);
}

std::string Experiment::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the sample builder
    if (mp_sample_builder) {
        mp_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    }
    // add parameters of the sample
    else if (mp_sample) {
        std::string sample_path = new_path + mp_sample->getName();
        mp_sample->addParametersToExternalPool(sample_path, external_pool, -1);
    }

    // Output parameterpool
//    for(ParameterPool::iterator_t ip=external_pool->begin(); ip!=external_pool->end(); ip++) {
//        std::cout << (*ip).first << " " << (*ip).second << std::endl;
//    }
    return new_path;
}

void Experiment::init_parameters()
{
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

void Experiment::updateSample()
{
    if (mp_sample_builder) {
        ISample *p_new_sample = mp_sample_builder->buildSample();
        if (mp_sample != p_new_sample) {
            delete mp_sample;
            mp_sample = p_new_sample;
        }
    }
}

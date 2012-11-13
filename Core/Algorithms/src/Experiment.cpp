#include "Experiment.h"

#include <typeinfo>

Experiment::Experiment()
: mp_sample(0)
, mp_sample_builder(0)
, m_is_normalized(false)
, mp_options(0)
{
    init_parameters();
}

Experiment::Experiment(ProgramOptions *p_options)
: mp_sample(0)
, mp_sample_builder(0)
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Experiment::Experiment(const ISample &p_sample, ProgramOptions *p_options)
: mp_sample(p_sample.clone())
, mp_sample_builder(0)
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Experiment::Experiment(const ISampleBuilder* p_sample_builder, ProgramOptions *p_options)
: mp_sample(0)
, mp_sample_builder(p_sample_builder)
, m_is_normalized(false)
, mp_options(p_options)
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
        OutputData<double>::iterator it = m_intensity_map.begin();
        while (it != m_intensity_map.end()) {
            *it *= incident_intensity;
            ++it;
        }
        m_is_normalized = true;
    }
}

//! The ISample object will not be owned by the Experiment object
void Experiment::setSample(const ISample &p_sample)
{
//    if (mp_sample != p_sample) {
//        delete mp_sample;
//        mp_sample = p_sample;
//        delete mp_sample_builder;
//        mp_sample_builder = 0;
//    }
    delete mp_sample;
    mp_sample = p_sample.clone();
}

void Experiment::setSampleBuilder(const ISampleBuilder *p_sample_builder)
{
//    if (mp_sample_builder != p_sample_builder) {
//        delete mp_sample_builder;
//        mp_sample_builder = p_sample_builder;
//        delete mp_sample;
//        mp_sample = 0;
//    }
    if( !p_sample_builder ) throw NullPointerException("Experiment::setSampleBuilder() -> Error! Attempt to set null sample builder.");
    mp_sample_builder = p_sample_builder;
    delete mp_sample;
    mp_sample = 0;
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
    OutputData<double>::iterator it_mask = m_current_output_data_mask.begin();
    while(it_mask != m_current_output_data_mask.end()) {
        if(it_mask.getIndex() % n_chunks_total == n_chunk) {
            *it_mask = 1.0;
        } else {
            *it_mask = 0.0;
        }
        ++it_mask;
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

    // add parameters of the beam
    m_beam.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the detector
    m_detector.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the sample builder
    if (mp_sample_builder) {
        mp_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    }
    // add parameters of the sample (only in the case without sample builder)
    else if (mp_sample) {
        std::string sample_path = new_path + mp_sample->getName();
        mp_sample->addParametersToExternalPool(sample_path, external_pool, -1);
    }

    return new_path;
}

void Experiment::init_parameters()
{
    setName("Experiment");
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
        std::string builder_type = typeid(*mp_sample_builder).name();
        if( builder_type.find("ISampleBuilder_wrapper") != std::string::npos ) {
            std::cout << "Experiment::updateSample() -> OMG, some body has called me from python, going to collapse in a second... " << std::endl;
            setSample(*p_new_sample); // p_new_sample belongs to python, don't delete it
        } else {
            delete mp_sample;
            mp_sample = p_new_sample;
        }
    }
}

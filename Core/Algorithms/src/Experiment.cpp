#include "Experiment.h"

Experiment::Experiment()
: IParameterized("Experiment")
, mp_sample(0)
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(0)
{
    init_parameters();
}

Experiment::Experiment(const Experiment &other)
: IParameterized(other), ICloneable()
, mp_sample(0)
, mp_sample_builder(other.mp_sample_builder)
, m_instrument(other.m_instrument)
, m_intensity_map()
, m_is_normalized(other.m_is_normalized)
, mp_options(other.mp_options)
, m_sim_params(other.m_sim_params)
{
    if(other.mp_sample) mp_sample = other.mp_sample->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);
    init_parameters();
}

Experiment::Experiment(const ProgramOptions *p_options)
: IParameterized("Experiment")
, mp_sample(0)
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Experiment::Experiment(const ISample &p_sample, const ProgramOptions *p_options)
: IParameterized("Experiment")
, mp_sample(p_sample.clone())
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Experiment::Experiment(const ISampleBuilder* p_sample_builder, const ProgramOptions *p_options)
: IParameterized("Experiment")
, mp_sample(0)
, mp_sample_builder(p_sample_builder)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}


/* ************************************************************************* */
// clone method
/* ************************************************************************* */
Experiment *Experiment::clone() const
{
    return new Experiment(*this);
}

void Experiment::runExperiment()
{
    m_is_normalized = false;
    updateSample();
}


void Experiment::normalize()
{
    double incident_intensity = m_instrument.getIntensity();
    if (!m_is_normalized && incident_intensity!=1.0) {
        m_intensity_map.scaleAll(incident_intensity);
        m_is_normalized = true;
    }
}


//! The ISample object will not be owned by the Experiment object
void Experiment::setSample(const ISample &p_sample)
{
    delete mp_sample;
    mp_sample = p_sample.clone();
}

void Experiment::setSampleBuilder(const ISampleBuilder *p_sample_builder)
{
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

void Experiment::setBeamParameters(double lambda, double alpha_i, double phi_i)
{
    m_instrument.setBeamParameters(lambda, alpha_i, phi_i);
}

void Experiment::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

std::string Experiment::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the instrument
    m_instrument.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the sample builder
    if (mp_sample_builder) {
        mp_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    }
    // add parameters of the sample (only in the case without sample builder)
    else if (mp_sample) {
//        std::string sample_path = new_path + mp_sample->getName();
//        mp_sample->addParametersToExternalPool(sample_path, external_pool, -1);
        mp_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Experiment::init_parameters()
{
}

void Experiment::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
    }
    m_intensity_map.setAllTo(0.0);
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

void Experiment::setDetectorParameters(const OutputData<double > &output_data)
{
    m_instrument.matchDetectorParameters(output_data);

    //updateIntensityMapAxes();
    m_intensity_map.clear();
    m_intensity_map.copyFrom(output_data); // to copy mask too
    m_intensity_map.setAllTo(0.0);
}



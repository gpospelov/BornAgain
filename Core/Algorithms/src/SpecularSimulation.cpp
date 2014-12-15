// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/OffSpecSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularSimulation.h"
#include "MultiLayer.h"
#include "SpecularMatrix.h"


SpecularSimulation::SpecularSimulation()
    : IParameterized("SpecularSimulation")
    , m_sample(0)
    , m_alpha_i_axis(0)
    , m_lambda(0.0)
    , m_scalar_data(0)
{
    init_parameters();
}


SpecularSimulation::SpecularSimulation(const ISample& sample)
    : IParameterized("SpecularSimulation")
    , m_sample(sample.clone())
    , m_alpha_i_axis(0)
    , m_lambda(0.0)
    , m_scalar_data(0)
{
    init_parameters();
}


SpecularSimulation::SpecularSimulation(SampleBuilder_t sample_builder)
    : IParameterized("SpecularSimulation")
    , m_sample(0)
    , m_sample_builder(sample_builder)
    , m_alpha_i_axis(0)
    , m_lambda(0.0)
    , m_scalar_data(0)
{
    init_parameters();
}


SpecularSimulation::~SpecularSimulation()
{
    delete m_sample;
    delete m_alpha_i_axis;
    delete m_scalar_data;
}


SpecularSimulation* SpecularSimulation::clone() const
{
    return new SpecularSimulation(*this);
}


void SpecularSimulation::setSample(const ISample &sample)
{
    delete m_sample;
    m_sample = sample.clone();
}


ISample *SpecularSimulation::getSample() const
{
    return m_sample;
}


void SpecularSimulation::setSampleBuilder(SampleBuilder_t sample_builder)
{
    if( !sample_builder.get() )
        throw NullPointerException(
            "SpecularSimulation::setSampleBuilder() -> "
            "Error! Attempt to set null sample builder.");

    m_sample_builder = sample_builder;
    delete m_sample;
    m_sample = 0;
}


SampleBuilder_t SpecularSimulation::getSampleBuilder() const
{
    return m_sample_builder;
}


void SpecularSimulation::prepareSimulation()
{
    if (!m_alpha_i_axis || m_alpha_i_axis->getSize()<1) {
        throw ClassInitializationException(
                "SpecularSimulation::prepareSimulation() "
                "-> Error. Incoming alpha range not configured.");
    }
    if (m_lambda<=0.0) {
        throw ClassInitializationException(
                "SpecularSimulation::prepareSimulation() "
                "-> Error. Incoming wavelength < 0.");
    }
    updateSample();

    std::cout << "xxx 1.1" << std::endl;
    collectRTCoefficientsScalar();
}


void SpecularSimulation::updateSample()
{
    if (m_sample_builder.get()) {
        ISample *new_sample = m_sample_builder->buildSample();
        std::string builder_type = typeid(*m_sample_builder).name();
        if( builder_type.find("ISampleBuilder_wrapper") != std::string::npos ) {
            setSample(*new_sample);
        } else {
            delete m_sample;
            m_sample = new_sample;
        }
    }
}


void SpecularSimulation::collectRTCoefficientsScalar()
{
    if(!m_sample)
        throw RuntimeErrorException("SpecularSimulation::collectRTCoefficientsScalar() -> Error. No sample defined");

    std::cout << "xxx 1.2" << std::endl;
    MultiLayer *multilayer = dynamic_cast<MultiLayer *>(m_sample);
    if(!multilayer)
        throw RuntimeErrorException("SpecularSimulation::collectRTCoefficientsScalar() -> Error. Not a multilayer");

    std::cout << "xxx 1.3" << std::endl;
    delete m_scalar_data;
    m_scalar_data = new OutputData<SpecularMatrix::MultiLayerCoeff_t>();

    m_scalar_data->addAxis(*m_alpha_i_axis);

    std::cout << "xxx 1.4" << std::endl;

    OutputData<SpecularMatrix::MultiLayerCoeff_t>::iterator it = m_scalar_data->begin();
//    OutputData<MultiLayerRTCoefficients>::iterator it = m_data.begin();
    while (it != m_scalar_data->end()) {
        double alpha_i = m_scalar_data->getValueOfAxis(0,it.getIndex());
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(m_lambda, -alpha_i, 0.0);

        SpecularMatrix::MultiLayerCoeff_t coeffs;
        SpecularMatrix matrixCalculator;
        matrixCalculator.execute(*multilayer, kvec, coeffs);

        *it = coeffs;
        ++it;

    } // alpha_i


//    m_multilayer_specular_info.clear();

//    MultiLayer *multilayer = dynamic_cast<MultiLayer *>(m_sample);

//    if(!multilayer)
//        throw RuntimeErrorException("SpecularSimulation::collectRTCoefficientsScalar() -> Error. Not a multilayer");

//    for(size_t i_layer=0;
//        i_layer<multilayer->getNumberOfLayers(); ++i_layer) {
//        LayerSpecularInfo *layer_coeff_map = new LayerSpecularInfo();
//        ScalarSpecularInfoMap *p_coeff_map = new ScalarSpecularInfoMap(
//                    multilayer, i_layer, m_lambda);
//        layer_coeff_map->addOutCoefficients(p_coeff_map);

//        m_multilayer_specular_info.push_back(layer_coeff_map);
//    }
}


void SpecularSimulation::runSimulation()
{
    prepareSimulation();

}


void SpecularSimulation::setBeamParameters(double lambda, const IAxis &alpha_axis)
{
    delete m_alpha_i_axis;
    m_alpha_i_axis = alpha_axis.clone();
    if (alpha_axis.getSize()<1) {
        throw ClassInitializationException(
                "SpecularSimulation::prepareSimulation() "
                "-> Error. Incoming alpha range size < 1.");
    }
    m_lambda = lambda;
}

const IAxis *SpecularSimulation::getAlphaAxis() const
{
    return m_alpha_i_axis;
}


std::vector<complex_t > SpecularSimulation::getScalarR(int i_layer) const
{
    if(!m_scalar_data)
        throw RuntimeErrorException("SpecularSimulation::getScalarR() -> Error. No scalar coefficients.");

    std::vector<complex_t > result;
    result.resize(m_alpha_i_axis->getSize());
    for(size_t i=0; i<m_scalar_data->getAllocatedSize(); ++i) {
        result[i] = (*m_scalar_data)[i][i_layer].getScalarR();
    }
    return result;
}


std::vector<complex_t > SpecularSimulation::getScalarT(int i_layer) const
{
    if(!m_scalar_data)
        throw RuntimeErrorException("SpecularSimulation::getScalarR() -> Error. No scalar coefficients.");

    std::vector<complex_t > result;
    result.resize(m_alpha_i_axis->getSize());
    for(size_t i=0; i<m_scalar_data->getAllocatedSize(); ++i) {
        result[i] = (*m_scalar_data)[i][i_layer].getScalarT();
    }
    return result;
}


SpecularSimulation::SpecularSimulation(const SpecularSimulation& other)
    : ICloneable(), IParameterized(other)
    , m_sample(0)
    , m_sample_builder(other.m_sample_builder)
    , m_lambda(other.m_lambda)
{
    if(other.m_sample) m_sample = other.m_sample->clone();
    if(other.m_alpha_i_axis) m_alpha_i_axis = other.m_alpha_i_axis->clone();
    if(other.m_scalar_data) m_scalar_data = other.m_scalar_data->clone();

    init_parameters();
}


void SpecularSimulation::init_parameters()
{

}


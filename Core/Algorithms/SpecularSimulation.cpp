// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/OffSpecSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularSimulation.h"
#include "MultiLayer.h"
#include "SpecularMatrix.h"
#include "Units.h"
#include <iostream>

SpecularSimulation::SpecularSimulation()
    : IParameterized("SpecularSimulation"), m_sample(0), m_alpha_i_axis(0), m_z_axis(0),
      m_lambda(0.0)
{
    init_parameters();
}

SpecularSimulation::SpecularSimulation(const ISample &sample)
    : IParameterized("SpecularSimulation"), m_sample(sample.clone()), m_alpha_i_axis(0),
      m_z_axis(0), m_lambda(0.0)
{
    init_parameters();
}

SpecularSimulation::SpecularSimulation(std::shared_ptr<class ISampleBuilder> sample_builder)
    : IParameterized("SpecularSimulation"), m_sample(0), m_sample_builder(sample_builder),
      m_alpha_i_axis(0), m_z_axis(0), m_lambda(0.0)
{
    init_parameters();
}

SpecularSimulation::SpecularSimulation(const SpecularSimulation &other)
    : ICloneable(), IParameterized(other), m_sample(0), m_sample_builder(other.m_sample_builder),
      m_alpha_i_axis(0), m_z_axis(0), m_lambda(other.m_lambda)
{
    if (other.m_sample)
        m_sample = other.m_sample->clone();
    if (other.m_alpha_i_axis)
        m_alpha_i_axis = other.m_alpha_i_axis->clone();
    if (other.m_z_axis)
        m_z_axis = other.m_z_axis->clone();
    m_data.copyFrom(other.m_data);
    m_ewave_intensity.copyFrom(other.m_ewave_intensity);
    init_parameters();
}

SpecularSimulation::~SpecularSimulation()
{
    delete m_sample;
    delete m_alpha_i_axis;
    delete m_z_axis;
}

SpecularSimulation *SpecularSimulation::clone() const
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

void SpecularSimulation::setSampleBuilder(std::shared_ptr<class ISampleBuilder> sample_builder)
{
    if (!sample_builder.get())
        throw NullPointerException("SpecularSimulation::setSampleBuilder() -> "
                                   "Error! Attempt to set null sample builder.");

    m_sample_builder = sample_builder;
    delete m_sample;
    m_sample = 0;
}

std::shared_ptr<class ISampleBuilder> SpecularSimulation::getSampleBuilder() const
{
    return m_sample_builder;
}

void SpecularSimulation::prepareSimulation()
{
    updateSample();

    if (!m_alpha_i_axis || m_alpha_i_axis->getSize() < 1) {
        throw ClassInitializationException("SpecularSimulation::checkSimulation() "
                                           "-> Error. Incoming alpha range not configured.");
    }
    if (m_lambda <= 0.0) {
        throw ClassInitializationException("SpecularSimulation::checkSimulation() "
                                           "-> Error. Incoming wavelength <= 0.");
    }

    if (!m_sample)
        throw ClassInitializationException(
            "SpecularSimulation::checkSimulation() -> Error. No sample set");

    updateCoefficientDataAxes();
}

// OutputData<double> *SpecularSimulation::getEvanescentWaveIntensity() const
//{
//    if(m_ewave_intensity.getAllocatedSize() == 1)
//        throw ClassInitializationException("SpecularSimulation::getEvanescentWaveIntensity() ->
//        Error. No evanescent wave calculations have been performed. Set corresponding axis with
//        Simulation::setEvanescentWaveAxis.");

//    return m_ewave_intensity.clone();
//}

void SpecularSimulation::runSimulation()
{
    prepareSimulation();

    MultiLayer *multilayer = dynamic_cast<MultiLayer *>(m_sample);
    if (!multilayer)
        throw NullPointerException(
            "SpecularSimulation::runSimulation() -> Error. Not a MultiLayer");

    if (multilayer->requiresMatrixRTCoefficients()) {
        collectRTCoefficientsMatrix(multilayer);
    } else {
        collectRTCoefficientsScalar(multilayer);
        //        calculateEvanescentWaveIntensity();
    }
}

void SpecularSimulation::setBeamParameters(double lambda, const IAxis &alpha_axis)
{
    delete m_alpha_i_axis;
    m_alpha_i_axis = alpha_axis.clone();
    m_lambda = lambda;
}

void SpecularSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min,
                                           double alpha_i_max)
{
    FixedBinAxis axis("alpha_i", nbins, alpha_i_min, alpha_i_max);
    setBeamParameters(lambda, axis);
}

void SpecularSimulation::setEvanescentWaveAxis(const IAxis &z_axis)
{
    delete m_z_axis;
    m_z_axis = z_axis.clone();
}

void SpecularSimulation::setEvanescentWaveAxis(int nbins, double z_min, double z_max)
{
    FixedBinAxis axis("z_axis", nbins, z_min, z_max);
    setEvanescentWaveAxis(axis);
}

const IAxis *SpecularSimulation::getAlphaAxis() const
{
    return m_alpha_i_axis;
}

std::vector<complex_t> SpecularSimulation::getScalarR(size_t i_layer) const
{
    checkCoefficients(i_layer);
    std::vector<complex_t> result;
    result.resize(m_data.getAllocatedSize());
    for (size_t i = 0; i < m_data.getAllocatedSize(); ++i) {
        result[i] = m_data[i][i_layer]->getScalarR();
    }
    return result;
}

std::vector<complex_t> SpecularSimulation::getScalarT(size_t i_layer) const
{
    checkCoefficients(i_layer);
    std::vector<complex_t> result;
    result.resize(m_data.getAllocatedSize());
    for (size_t i = 0; i < m_data.getAllocatedSize(); ++i) {
        result[i] = m_data[i][i_layer]->getScalarT();
    }
    return result;
}

std::vector<complex_t> SpecularSimulation::getScalarKz(size_t i_layer) const
{
    checkCoefficients(i_layer);
    std::vector<complex_t> result;
    result.resize(m_data.getAllocatedSize());
    for (size_t i = 0; i < m_data.getAllocatedSize(); ++i) {
        result[i] = m_data[i][i_layer]->getScalarKz();
    }
    return result;
}

SpecularSimulation::LayerRTCoefficients_t
SpecularSimulation::getLayerRTCoefficients(size_t i_alpha, size_t i_layer) const
{
    if (i_alpha >= m_data.getAllocatedSize())
        throw RuntimeErrorException(
            "SpecularSimulation::getLayerRTCoefficients() -> Error. Wrong i_alpha.");

    if (i_layer >= m_data[i_alpha].size())
        throw RuntimeErrorException(
            "SpecularSimulation::getLayerRTCoefficients() -> Error. Wrong layer index.");

    return m_data[i_alpha][i_layer];
}

void SpecularSimulation::init_parameters()
{
}

void SpecularSimulation::updateSample()
{
    if (m_sample_builder.get()) {
        ISample *new_sample = m_sample_builder->buildSample();
        std::string builder_type = typeid(*m_sample_builder).name();
        if (builder_type.find("ISampleBuilder_wrapper") != std::string::npos) {
            setSample(*new_sample);
        } else {
            delete m_sample;
            m_sample = new_sample;
        }
    }
}

void SpecularSimulation::collectRTCoefficientsScalar(const MultiLayer *multilayer)
{
    OutputData<MultiLayerRTCoefficients_t>::iterator it = m_data.begin();
    while (it != m_data.end()) {
        double alpha_i = m_data.getAxisValue(it.getIndex(), 0);
        kvector_t kvec = Geometry::vecOfLambdaAlphaPhi(m_lambda, -alpha_i, 0.0);

        SpecularMatrix::MultiLayerCoeff_t coeffs;
        SpecularMatrix::execute(*multilayer, kvec, coeffs);

        MultiLayerRTCoefficients_t ml_coeffs;
        ml_coeffs.resize(coeffs.size());
        for (size_t i_layer = 0; i_layer < coeffs.size(); ++i_layer) {
            ml_coeffs[i_layer] = LayerRTCoefficients_t(new ScalarRTCoefficients(coeffs[i_layer]));
        }

        *it = ml_coeffs;
        ++it;

    } // alpha_i
}

void SpecularSimulation::collectRTCoefficientsMatrix(const MultiLayer * /*multilayer*/)
{
    throw NotImplementedException(
        "SpecularSimulation::collectRTCoefficientsMatrix() -> Error. Not implemented.");
}

// void SpecularSimulation::calculateEvanescentWaveIntensity()
//{
//    if(!m_z_axis) return;

//    MultiLayer *multilayer = dynamic_cast<MultiLayer *>(m_sample);
//    const IAxis *alpha_axis = m_ewave_intensity.getAxis(0);
//    const IAxis *z_axis = m_ewave_intensity.getAxis(1);

//    OutputData<double>::iterator it = m_ewave_intensity.begin();
//    while (it != m_ewave_intensity.end()) {
//        std::vector<int> indices =
//                m_ewave_intensity.toCoordinates(it.getIndex());

//        size_t alpha_index = indices[0];
//        size_t z_index =  indices[1];

////        double alpha_axis_value = (*alpha_axis)[alpha_index];
//        double z_axis_value = (*z_axis)[z_index];

//        int i_layer = multilayer->zToLayerIndex(z_axis_value);

//        double depth = multilayer->getLayerThickness(i_layer) -
//        (z_axis_value-multilayer->getLayerBottomZ(i_layer));

////        std::cout << "alpha_axis_value:" << alpha_axis_value << " z_axis_value:" << z_axis_value
///<< " i_layer:" << i_layer  << " depth:" << depth<< std::endl;

//        LayerRTCoefficients_t rtcoeff = getLayerRTCoefficients(alpha_index, i_layer);

////        complex_t cvalue = rtcoeff->getScalarT()*std::exp(rtcoeff->getScalarKz()*depth) +
///rtcoeff->getScalarR()*std::exp(rtcoeff->getScalarKz()*depth);
////        complex_t cvalue =
///rtcoeff->getScalarT()*std::exp(std::imag(rtcoeff->getScalarKz())*depth) +
///rtcoeff->getScalarR()*std::exp(std::imag(rtcoeff->getScalarKz())*depth);
////        *it = std::abs(cvalue);
//        double value = 1.0 +
//            std::abs(rtcoeff->getScalarT())*
//            std::exp(std::imag(rtcoeff->getScalarKz())*depth*Units::angstrom);
//        *it = value;
//        ++it;
//    }

//}

void SpecularSimulation::checkCoefficients(size_t i_layer) const
{
    if (m_data.getAllocatedSize() == 1 || m_data[0].size() == 0)
        throw ClassInitializationException(
            "SpecularSimulation::checkCoefficients() -> Error. "
            "No coefficients found, check that (1) you have set beam parameters "
            "(2) you have run your simulation.");

    if (i_layer >= m_data[0].size()) {
        std::ostringstream message;
        message << "SpecularSimulation::checkCoefficients() -> Error. Requested layer index "
                << i_layer << " is large than or equal to the total number of layers "
                << m_data[0].size() << std::endl;
        throw OutOfBoundsException(message.str());
    }
}

void SpecularSimulation::updateCoefficientDataAxes()
{
    m_data.clear();
    m_data.addAxis(*m_alpha_i_axis);

    if (m_z_axis) {
        m_ewave_intensity.clear();
        m_ewave_intensity.addAxis(*m_alpha_i_axis);
        m_ewave_intensity.addAxis(*m_z_axis);
    }
}

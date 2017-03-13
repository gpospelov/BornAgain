// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.cpp
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
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "SpecularMatrix.h"
#include <memory>

SpecularSimulation::SpecularSimulation()
    : IParameterized("SpecularSimulation")
{
    init_parameters();
}

SpecularSimulation::SpecularSimulation(const ISample &sample)
    : IParameterized("SpecularSimulation")
    , mP_sample(sample.clone())
{
    init_parameters();
}

SpecularSimulation::SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
    : IParameterized("SpecularSimulation")
    , mP_sample_builder(sample_builder)
{
    init_parameters();
}

SpecularSimulation::SpecularSimulation(const SpecularSimulation &other)
    : IParameterized(other)
    , mP_sample_builder(other.mP_sample_builder)
    , m_lambda(other.m_lambda)
{
    if (other.mP_sample.get())
        mP_sample.reset( other.mP_sample->clone() );
    if (other.mP_alpha_i_axis)
        mP_alpha_i_axis.reset(other.mP_alpha_i_axis->clone());
    m_data.copyFrom(other.m_data);
    init_parameters();
}

SpecularSimulation::~SpecularSimulation()
{}

SpecularSimulation *SpecularSimulation::clone() const
{
    return new SpecularSimulation(*this);
}

void SpecularSimulation::setSample(const ISample &sample)
{
    mP_sample.reset( sample.clone() );
}

void SpecularSimulation::setSampleBuilder(std::shared_ptr<IMultiLayerBuilder> sample_builder)
{
    if (!sample_builder)
        throw Exceptions::NullPointerException("SpecularSimulation::setSampleBuilder() -> "
                                               "Error! Attempt to set null sample builder.");

    mP_sample_builder = sample_builder;
    mP_sample.reset(nullptr);
}

void SpecularSimulation::prepareSimulation()
{
    updateSample();

    if (!mP_alpha_i_axis || mP_alpha_i_axis->size() < 1)
        throw Exceptions::ClassInitializationException("SpecularSimulation::checkSimulation() "
                                           "-> Error. Incoming alpha range not configured.");
    if (m_lambda <= 0.0)
        throw Exceptions::ClassInitializationException("SpecularSimulation::checkSimulation() "
                                           "-> Error. Incoming wavelength <= 0.");
    if (!mP_sample)
        throw Exceptions::ClassInitializationException(
            "SpecularSimulation::checkSimulation() -> Error. No sample set");

    updateCoefficientDataAxes();
}

void SpecularSimulation::runSimulation()
{
    prepareSimulation();

    MultiLayer *multilayer = dynamic_cast<MultiLayer*>(mP_sample.get());
    if (!multilayer)
        throw Exceptions::NullPointerException(
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
    mP_alpha_i_axis.reset(alpha_axis.clone());
    m_lambda = lambda;
}

void SpecularSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min,
                                           double alpha_i_max)
{
    FixedBinAxis axis("alpha_i", nbins, alpha_i_min, alpha_i_max);
    setBeamParameters(lambda, axis);
}

const IAxis *SpecularSimulation::getAlphaAxis() const
{
    return mP_alpha_i_axis.get();
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
        throw Exceptions::RuntimeErrorException(
            "SpecularSimulation::getLayerRTCoefficients() -> Error. Wrong i_alpha.");

    if (i_layer >= m_data[i_alpha].size())
        throw Exceptions::RuntimeErrorException(
            "SpecularSimulation::getLayerRTCoefficients() -> Error. Wrong layer index.");

    return m_data[i_alpha][i_layer];
}

void SpecularSimulation::updateSample()
{
    if (!mP_sample_builder)
        return;
    if (mP_sample_builder->isPythonBuilder()) {
        mP_sample.reset( mP_sample_builder->buildSample()->clone() );
    } else {
        mP_sample.reset( mP_sample_builder->buildSample() );
    }
}

void SpecularSimulation::collectRTCoefficientsScalar(const MultiLayer *multilayer)
{
    OutputData<MultiLayerRTCoefficients_t>::iterator it = m_data.begin();
    while (it != m_data.end()) {
        double alpha_i = m_data.getAxisValue(it.getIndex(), 0);
        kvector_t kvec = vecOfLambdaAlphaPhi(m_lambda, -alpha_i, 0.0);

        std::vector<ScalarRTCoefficients> coeffs;
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
    throw Exceptions::NotImplementedException(
        "SpecularSimulation::collectRTCoefficientsMatrix() -> Error. Not implemented.");
}

void SpecularSimulation::checkCoefficients(size_t i_layer) const
{
    if (m_data.getAllocatedSize() == 1 || m_data[0].size() == 0)
        throw Exceptions::ClassInitializationException(
            "SpecularSimulation::checkCoefficients() -> Error. "
            "No coefficients found, check that (1) you have set beam parameters "
            "(2) you have run your simulation.");

    if (i_layer >= m_data[0].size()) {
        std::ostringstream message;
        message << "SpecularSimulation::checkCoefficients() -> Error. Requested layer index "
                << i_layer << " is large than or equal to the total number of layers "
                << m_data[0].size() << std::endl;
        throw Exceptions::OutOfBoundsException(message.str());
    }
}

void SpecularSimulation::updateCoefficientDataAxes()
{
    m_data.clear();
    m_data.addAxis(*mP_alpha_i_axis);
}

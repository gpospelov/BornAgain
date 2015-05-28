// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "SpecularMatrix.h"
#include "Numeric.h"

static complex_t I = complex_t(0.0, 1.0);

// Returns reflection/transmission coefficients for given multilayer and wavevector k

void SpecularMatrix::execute(const MultiLayer& sample, const kvector_t& k,
        MultiLayerCoeff_t& coeff)
{
    coeff.clear();
    coeff.resize(sample.getNumberOfLayers());
    m_roughness_pmatrices.clear();
    m_roughness_pmatrices.resize(sample.getNumberOfInterfaces());

    calculateEigenvalues(sample, k, coeff);

    // check if there is a roughness and if so, calculate the effective
    // matrix to insert at this interface (else unit matrix)
    for (size_t i=0; i<sample.getNumberOfInterfaces(); ++i) {
        double sigma = 0.0;
        if (sample.getLayerInterface(i)->getRoughness()) {
            sigma = sample.getLayerBottomInterface(i)->getRoughness()->getSigma();
        }
        if(sigma > 0.0) {
            double sigeff = std::pow(Units::PID2, 1.5)*sigma*k.mag();
            m_roughness_pmatrices[i] = calculatePMatrix(
                        sigeff*coeff[i+1].lambda, sigeff*coeff[i].lambda);
        }
        else {
            m_roughness_pmatrices[i] = getUnitMatrix();
        }
    }

    calculateTransferAndBoundary(sample, k, coeff);
}

void SpecularMatrix::calculateEigenvalues(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    double sign_kz = k.z() > 0.0 ? -1.0 : 1.0;
    complex_t r2ref = sample.getLayer(0)->getRefractiveIndex2() * k.sin2Theta();
    for(size_t i=0; i<coeff.size(); ++i) {
        coeff[i].lambda = std::sqrt(sample.getLayer(i)->getRefractiveIndex2() - r2ref);
        coeff[i].kz = k.mag()*coeff[i].lambda * sign_kz;
    }
}

void SpecularMatrix::calculateTransferAndBoundary(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    size_t N = coeff.size();
    if (coeff[0].lambda == 0.0 && N>1) {
        setForNoTransmission(coeff);
        return;
    }

    // Last layer boundary ensures no reflection
    coeff[N-1].t_r(0) = 1.0;
    coeff[N-1].t_r(1) = 0.0;
    coeff[N-1].l.setIdentity();

    for(int i=(int)N-2; i>0; --i) {
        complex_t lambda = coeff[i].lambda;
        complex_t lambda_rough = lambda*m_roughness_pmatrices[i](1,1);
        if (lambda == complex_t(0.0, 0.0)) {
            complex_t prev_lambda = coeff[i+1].lambda
                    *m_roughness_pmatrices[i](0,0);
            coeff[i].l.setIdentity();
            complex_t t_coeff = coeff[i+1].t_r(0) + coeff[i+1].t_r(1)
                    * m_roughness_pmatrices[i](1,1);
            complex_t phi_0 = (coeff[i+1].t_r(1) - coeff[i+1].t_r(0))
                    * prev_lambda;
            coeff[i].t_r(0) = t_coeff + I * k.mag()
                    * sample.getLayer(i)->getThickness() * phi_0;
            coeff[i].t_r(1) = 0.0;
        }
        else {
            complex_t prev_lambda = coeff[i+1].lambda
                    *m_roughness_pmatrices[i](0,0);
            complex_t t_coeff = ((lambda_rough-prev_lambda)*coeff[i+1].t_r(1)
               + (lambda_rough+prev_lambda)*coeff[i+1].t_r(0))/2.0/lambda;
            complex_t r_coeff = ((lambda_rough+prev_lambda)*coeff[i+1].t_r(1)
               + (lambda_rough-prev_lambda)*coeff[i+1].t_r(0))/2.0/lambda;
            complex_t ikdlambda = I * k.mag() * sample.getLayer(i)->getThickness() * lambda;
            coeff[i].t_r(0) = t_coeff*std::exp(-ikdlambda);
            coeff[i].t_r(1) = r_coeff*std::exp( ikdlambda);
        }
    }
    // If more than 1 layer, impose normalization:
    if (N>1) {
        // First layer boundary is also top layer boundary:
        coeff[0].l.setIdentity();
        complex_t lambda = coeff[0].lambda;
        complex_t lambda_rough = lambda*m_roughness_pmatrices[0](1,1);
        complex_t prev_lambda = coeff[1].lambda
                *m_roughness_pmatrices[0](0,0);
        coeff[0].t_r(0) = ((lambda_rough-prev_lambda)*coeff[1].t_r(1)
                + (lambda_rough+prev_lambda)*coeff[1].t_r(0))/2.0/lambda;
        coeff[0].t_r(1) = ((lambda_rough+prev_lambda)*coeff[1].t_r(1)
                + (lambda_rough-prev_lambda)*coeff[1].t_r(0))/2.0/lambda;
        complex_t T0 = coeff[0].getScalarT();
        for (size_t i=0; i<N; ++i) {
            coeff[i].t_r = coeff[i].t_r/T0;
        }
    }
}

Eigen::Matrix2cd SpecularMatrix::calculatePMatrix(
        complex_t lambda_lower, complex_t lambda_upper) const
{
    // first check for equal lambdas
    if (lambda_lower == lambda_upper) {
        return getUnitMatrix();
    }
    complex_t p00; // initialize for unit matrix
    p00 = getPMatrixElement(lambda_lower)/ getPMatrixElement(lambda_upper);
    Eigen::Matrix2cd p;
    p(0,0) = p00;
    p(0,1) = 0.0;
    p(1,0) = 0.0;
    p(1,1) = 1.0/p00;

    return p;
}

Eigen::Matrix2cd SpecularMatrix::getUnitMatrix() const
{
    return Eigen::Matrix2cd::Identity();
}

complex_t SpecularMatrix::getPMatrixElement(complex_t sigma_lambda) const
{
    if (std::abs(sigma_lambda)<Numeric::double_epsilon) {
        return 1.0;
    }
    return std::sqrt(std::tanh(sigma_lambda)/sigma_lambda);
}

void SpecularMatrix::setForNoTransmission(MultiLayerCoeff_t& coeff) const
{
    size_t N = coeff.size();
    coeff[0].t_r(0) = 1.0;
    coeff[0].t_r(1) = -1.0;
    for (size_t i=1; i<N; ++i) {
        coeff[i].t_r.setZero();
        coeff[i].l.setIdentity();
    }
}

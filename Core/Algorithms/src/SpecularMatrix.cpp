// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SpecularMatrix.cpp
//! @brief     Implements class SpecularMatrix.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "SpecularMatrix.h"

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
        const LayerInterface *interface = sample.getLayerInterface(i);
        if(interface->getRoughness() ) {
            complex_t a = calculateRoughnessParameter(
                    *interface, k, false);
            complex_t b = calculateRoughnessParameter(
                    *interface, k, true);
            complex_t lambda_lower = coeff[i+1].lambda;
            complex_t lambda_upper = coeff[i].lambda;
            m_roughness_pmatrices[i] = calculatePMatrix(a, b,
                    lambda_lower, lambda_upper);
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
    double sinalpha = std::abs( k.cosTheta() );
    double cosalpha2 = 1.0 - sinalpha*sinalpha;
    complex_t rindex0 = sample.getLayer(0)->getRefractiveIndex();
    complex_t r2cosalpha2 = rindex0*rindex0*cosalpha2;
    for(size_t i=0; i<coeff.size(); ++i) {
        complex_t rindex = sample.getLayer(i)->getRefractiveIndex();
        coeff[i].lambda = std::sqrt(rindex*rindex - r2cosalpha2);
    }
}

void SpecularMatrix::calculateTransferAndBoundary(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    size_t N = coeff.size();
    // Last layer boundary ensures no reflection
    coeff[N-1].phi_psi(0) = -coeff[N-1].lambda;
    coeff[N-1].phi_psi(1) = 1.0;
    coeff[N-1].l.setIdentity();
    for(size_t i=N-2; i>0; --i) {
        complex_t lambda = coeff[i].lambda;
        complex_t kdlambda = k.mag()*sample.getLayer(i)->getThickness()*lambda;
        complex_t cosine_term = std::cos(kdlambda);
        complex_t sine_term =
                ( std::abs(kdlambda) < Numeric::double_epsilon ) ?
                k.mag()*sample.getLayer(i)->getThickness() :
                std::sin(kdlambda)/lambda;
        coeff[i].l(0,0) = cosine_term;
        coeff[i].l(0,1) = complex_t(0.0, 1.0)*lambda*lambda*sine_term;
        coeff[i].l(1,0) = complex_t(0.0, 1.0)*sine_term;
        coeff[i].l(1,1) = cosine_term;
        coeff[i].phi_psi = coeff[i].l * m_roughness_pmatrices[i]
                                      * coeff[i+1].phi_psi;
    }
    // First layer boundary is also top layer boundary:
    coeff[0].l.setIdentity();
    coeff[0].phi_psi = m_roughness_pmatrices[0] * coeff[1].phi_psi;
    // Normalize all boundary values with top layer transmitted wave:
    complex_t T0 = coeff[0].T();
    for (size_t i=0; i<N; ++i) {
        coeff[i].phi_psi = coeff[i].phi_psi/T0;
    }
}

complex_t SpecularMatrix::calculateRoughnessParameter(const LayerInterface &interface,
        const kvector_t& k, bool invert_term) const
{
    double k0 = k.mag();
    complex_t n_lower = interface.getLayerBottom()->getRefractiveIndex();
    complex_t n_upper = interface.getLayerTop()->getRefractiveIndex();
    double sig = interface.getRoughness()->getSigma()*std::sqrt(M_PI/2.0);
    double sign = invert_term ? -1.0 : 1.0;
    // when n is interpolated tanh-wise
//    return k0*(n_upper-n_lower)*sig*(
//            n_lower-n_upper + sign*(n_lower+n_upper)*std::log(4.0) );
    // when n^2 is interpolated tanh-wise
    return sign*k0*(n_upper*n_upper-n_lower*n_lower)*sig*std::log(2.0)/2.0;
}

Eigen::Matrix2cd SpecularMatrix::calculatePMatrix(complex_t a, complex_t b,
        complex_t lambda_lower, complex_t lambda_upper) const
{
    std::cout << "a: " << a << " b: " << b << " ll: "
            << lambda_lower << " lu: " << lambda_upper << std::endl;
    complex_t i(0.0, 1.0);
    Eigen::Matrix2cd p_lower;
    p_lower(0,0) = std::cos(a/lambda_lower/2.0);
    p_lower(0,1) = i*lambda_lower*std::sin(a/lambda_lower/2.0);
    p_lower(1,0) = i*std::sin(a/lambda_lower/2.0)/lambda_lower;
    p_lower(1,1) = std::cos(a/lambda_lower/2.0);

    Eigen::Matrix2cd p_upper;
    p_upper(0,0) = std::cos(b/lambda_upper/2.0);
    p_upper(0,1) = i*lambda_upper*std::sin(b/lambda_upper/2.0);
    p_upper(1,0) = i*std::sin(b/lambda_upper/2.0)/lambda_upper;
    p_upper(1,1) = std::cos(b/lambda_upper/2.0);

    return p_upper*p_lower;
}

Eigen::Matrix2cd SpecularMatrix::getUnitMatrix() const
{
    Eigen::Matrix2cd unit;
    unit(0,0) = 1.0;
    unit(0,1) = 0.0;
    unit(1,0) = 0.0;
    unit(1,1) = 1.0;
    return unit;
}

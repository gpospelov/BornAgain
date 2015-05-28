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
#include "MathFunctions.h"

using std::sqrt;

static complex_t I = complex_t(0.0, 1.0);

// Returns reflection/transmission coefficients for given multilayer and wavevector k

void SpecularMatrix::execute(const MultiLayer& sample, const kvector_t& k,
        MultiLayerCoeff_t& coeff)
{
    size_t N = sample.getNumberOfLayers();
    assert(N-1 == sample.getNumberOfInterfaces());
    coeff.clear();
    coeff.resize(N);

    // Calculate lambda and kz for each layer.
    double sign_kz = k.z() > 0.0 ? -1.0 : 1.0;
    complex_t r2ref = sample.getLayer(0)->getRefractiveIndex2() * k.sin2Theta();
    for(size_t i=0; i<N; ++i) {
        coeff[i].lambda = sqrt(sample.getLayer(i)->getRefractiveIndex2() - r2ref);
        coeff[i].kz = k.mag()*coeff[i].lambda * sign_kz;
    }

    // Calculate t_r and l for each layer.

    if (coeff[0].lambda == 0.0 && N>1) {
        // set for no transmission
        coeff[0].t_r(0) = 1.0;
        coeff[0].t_r(1) = -1.0;
        for (size_t i=1; i<N; ++i) {
            coeff[i].t_r.setZero();
            coeff[i].l.setIdentity();
        }
        return;
    }

    // Last layer boundary ensures no reflection
    coeff[N-1].t_r(0) = 1.0;
    coeff[N-1].t_r(1) = 0.0;
    coeff[N-1].l.setIdentity();

    // check if there is a roughness and if so, calculate the effective
    // matrix to insert at this interface (else unit matrix)
    std::vector<Eigen::Matrix2cd> roughness_pmatrices;
    roughness_pmatrices.clear();
    roughness_pmatrices.resize(N-1);
    for (size_t i=0; i<N-1; ++i) {
        double sigma = 0.0;
        if (sample.getLayerInterface(i)->getRoughness()) {
            sigma = sample.getLayerBottomInterface(i)->getRoughness()->getSigma();
        }
        if(sigma > 0.0) {
            double sigeff = std::pow(Units::PID2, 1.5)*sigma*k.mag();
            roughness_pmatrices[i] = calculatePMatrix(
                        sigeff*coeff[i+1].lambda, sigeff*coeff[i].lambda);
        }
        else {
            roughness_pmatrices[i] = Eigen::Matrix2cd::Identity();
        }
    }

    for(int i=(int)N-2; i>0; --i) {
        complex_t lambda = coeff[i].lambda;
        complex_t lambda_rough = lambda*roughness_pmatrices[i](1,1);
        if (lambda == complex_t(0.0, 0.0)) {
            complex_t prev_lambda = coeff[i+1].lambda * roughness_pmatrices[i](0,0);
            coeff[i].l.setIdentity();
            complex_t t_coeff = coeff[i+1].t_r(0) +
                    coeff[i+1].t_r(1) * roughness_pmatrices[i](1,1);
            complex_t phi_0 = (coeff[i+1].t_r(1) - coeff[i+1].t_r(0)) * prev_lambda;
            coeff[i].t_r(0) = t_coeff +
                    I * k.mag() * sample.getLayer(i)->getThickness() * phi_0;
            coeff[i].t_r(1) = 0.0;
        }
        else {
            complex_t prev_lambda = coeff[i+1].lambda * roughness_pmatrices[i](0,0);
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
        complex_t lambda_rough = lambda*roughness_pmatrices[0](1,1);
        complex_t prev_lambda = coeff[1].lambda
                *roughness_pmatrices[0](0,0);
        coeff[0].t_r(0) = (
                    (lambda_rough-prev_lambda)*coeff[1].t_r(1) +
                    (lambda_rough+prev_lambda)*coeff[1].t_r(0) )/2.0/lambda;
        coeff[0].t_r(1) = (
                    (lambda_rough+prev_lambda)*coeff[1].t_r(1) +
                    (lambda_rough-prev_lambda)*coeff[1].t_r(0) )/2.0/lambda;
        complex_t T0 = coeff[0].getScalarT();
        for (size_t i=0; i<N; ++i) {
            coeff[i].t_r = coeff[i].t_r/T0;
        }
    }
}

Eigen::Matrix2cd SpecularMatrix::calculatePMatrix( complex_t lower, complex_t upper)
{
    if (lower == upper) {
        return Eigen::Matrix2cd::Identity();
    }
    complex_t p00 = sqrt( MathFunctions::tanhc(lower) / MathFunctions::tanhc(upper) );
    Eigen::Matrix2cd p;
    p << p00, 0, 0, 1.0/p00;
    return p;
}

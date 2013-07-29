// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      SpecularMagnetic.cpp
//! @brief     Implements class SpecularMagnetic.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SpecularMagnetic.h"

#include <Eigen/LU>

void SpecularMagnetic::execute(const MultiLayer& sample, const kvector_t& k,
        MultiLayerCoeff_t& coeff)
{
    coeff.clear();
    coeff.resize(sample.getNumberOfLayers());

    calculateEigenvalues(sample, k, coeff);

    calculateTransferAndBoundary(sample, k, coeff);
}

void SpecularMagnetic::calculateEigenvalues(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    double mag_k = k.mag();
    for(size_t i=0; i<coeff.size(); ++i) {
        coeff[i].m_scatt_matrix = sample.getLayer(i)->getMaterial()->
                getScatteringMatrix(k);
        coeff[i].m_a = coeff[i].m_scatt_matrix.trace()/2.0;
        coeff[i].m_b_mag = std::sqrt(coeff[i].m_a*coeff[i].m_a -
                coeff[i].m_scatt_matrix.determinant());
        coeff[i].m_bz = ( coeff[i].m_scatt_matrix(0,0) -
                coeff[i].m_scatt_matrix(1,1) )/2.0;
        coeff[i].lambda(0) = std::sqrt(coeff[i].m_a - coeff[i].m_b_mag);
        coeff[i].lambda(1) = std::sqrt(coeff[i].m_a + coeff[i].m_b_mag);
        coeff[i].kz = mag_k*coeff[i].lambda;
    }
}

void SpecularMagnetic::calculateTransferAndBoundary(const MultiLayer& sample,
        const kvector_t& k, MultiLayerCoeff_t& coeff) const
{
    size_t N = coeff.size();
    if (coeff[0].lambda == Eigen::Vector2cd::Zero() && N>1) {
        setForNoTransmission(coeff);
        return;
    }

    for (int i=1; i<(int)N; ++i) {
        coeff[i].calculateTRMatrices();
        double t = sample.getLayer(i)->getThickness();
        coeff[i].l =
               coeff[i].R1m * getImExponential((complex_t)(coeff[i].kz(0)*t)) +
               coeff[i].T1m * getImExponential((complex_t)(-coeff[i].kz(0)*t)) +
               coeff[i].R2m * getImExponential((complex_t)(coeff[i].kz(1)*t)) +
               coeff[i].T2m * getImExponential((complex_t)(-coeff[i].kz(1)*t));
    }
}

Eigen::Matrix2cd SpecularMagnetic::getUnitMatrix() const
{
    return Eigen::Matrix2cd::Identity();
}

void SpecularMagnetic::setForNoTransmission(MultiLayerCoeff_t& coeff) const
{
    size_t N = coeff.size();
    for (size_t i=0; i<N; ++i) {
        coeff[i].phi_psi.setZero();
        coeff[i].l.setIdentity();
        coeff[i].T1m = coeff[i].l/4.0;
        coeff[i].R1m = coeff[i].T1m;
        coeff[i].T2m = coeff[i].T1m;
        coeff[i].R2m = coeff[i].T1m;
    }
}

void SpecularMagnetic::LayerMatrixCoeff::calculateTRMatrices()
{
    if (m_b_mag == 0.0) {
        calculateTRWithoutMagnetization();
        return;
    }

    // T1m:
    // row 0:
    T1m(0,0) = (1.0 - m_bz/m_b_mag)/4.0;
    T1m(0,1) = - m_scatt_matrix(0,1)/4.0/m_b_mag;
    T1m(0,2) = lambda(0)*(m_bz/m_b_mag - 1.0)/4.0;
    T1m(0,3) = m_scatt_matrix(0,1)*lambda(0)/4.0/m_b_mag;
    // row 1:
    T1m(1,0) = - m_scatt_matrix(1,0)/4.0/m_b_mag;
    T1m(1,1) = (1.0 + m_bz/m_b_mag)/4.0;
    T1m(1,2) = m_scatt_matrix(1,0)*lambda(0)/4.0/m_b_mag;
    T1m(1,3) = - lambda(0)*(m_bz/m_b_mag + 1.0)/4.0;
    // row 2:
    T1m(2,0) = -(1.0 - m_bz/m_b_mag)/4.0/lambda(0);
    T1m(2,1) = m_scatt_matrix(0,1)/4.0/m_b_mag/lambda(0);
    T1m(2,2) = -(m_bz/m_b_mag - 1.0)/4.0;
    T1m(2,3) = - m_scatt_matrix(0,1)/4.0/m_b_mag;
    // row 3:
    T1m(3,0) = m_scatt_matrix(1,0)/4.0/m_b_mag/lambda(0);
    T1m(3,1) = -(1.0 + m_bz/m_b_mag)/4.0/lambda(0);
    T1m(3,2) = - m_scatt_matrix(1,0)/4.0/m_b_mag;
    T1m(3,3) = (m_bz/m_b_mag + 1.0)/4.0;

    // R1m:
    // row 0:
    R1m(0,0) = T1m(0,0);
    R1m(0,1) = T1m(0,1);
    R1m(0,2) = -T1m(0,2);
    R1m(0,3) = -T1m(0,3);
    // row 1:
    R1m(1,0) = T1m(1,0);
    R1m(1,1) = T1m(1,1);
    R1m(1,2) = -T1m(1,2);
    R1m(1,3) = -T1m(1,3);
    // row 2:
    R1m(2,0) = -T1m(2,0);
    R1m(2,1) = -T1m(2,1);
    R1m(2,2) = T1m(2,2);
    R1m(2,3) = T1m(2,3);
    // row 3:
    R1m(3,0) = -T1m(3,0);
    R1m(3,1) = -T1m(3,1);
    R1m(3,2) = T1m(3,2);
    R1m(3,3) = T1m(3,3);

    // T2m:
    // row 0:
    T2m(0,0) = (1.0 + m_bz/m_b_mag)/4.0;
    T2m(0,1) = m_scatt_matrix(0,1)/4.0/m_b_mag;
    T2m(0,2) = - lambda(1)*(m_bz/m_b_mag + 1.0)/4.0;
    T2m(0,3) = - m_scatt_matrix(0,1)*lambda(1)/4.0/m_b_mag;
    // row 1:
    T2m(1,0) = m_scatt_matrix(1,0)/4.0/m_b_mag;
    T2m(1,1) = (1.0 - m_bz/m_b_mag)/4.0;
    T2m(1,2) = - m_scatt_matrix(1,0)*lambda(1)/4.0/m_b_mag;
    T2m(1,3) = lambda(1)*(m_bz/m_b_mag - 1.0)/4.0;
    // row 2:
    T2m(2,0) = -(1.0 + m_bz/m_b_mag)/4.0/lambda(1);
    T2m(2,1) = - m_scatt_matrix(0,1)/4.0/m_b_mag/lambda(1);
    T2m(2,2) = (m_bz/m_b_mag + 1.0)/4.0;
    T2m(2,3) = m_scatt_matrix(0,1)/4.0/m_b_mag;
    // row 3:
    T2m(3,0) = - m_scatt_matrix(1,0)/4.0/m_b_mag/lambda(1);
    T2m(3,1) = -(1.0 - m_bz/m_b_mag)/4.0/lambda(1);
    T2m(3,2) = m_scatt_matrix(1,0)/4.0/m_b_mag;
    T2m(3,3) = (1.0 - m_bz/m_b_mag)/4.0;

    // R2m:
    // row 0:
    R2m(0,0) = T2m(0,0);
    R2m(0,1) = T2m(0,1);
    R2m(0,2) = -T2m(0,2);
    R2m(0,3) = -T2m(0,3);
    // row 1:
    R2m(1,0) = T2m(1,0);
    R2m(1,1) = T2m(1,1);
    R2m(1,2) = -T2m(1,2);
    R2m(1,3) = -T2m(1,3);
    // row 2:
    R2m(2,0) = -T2m(2,0);
    R2m(2,1) = -T2m(2,1);
    R2m(2,2) = T2m(2,2);
    R2m(2,3) = T2m(2,3);
    // row 3:
    R2m(3,0) = -T2m(3,0);
    R2m(3,1) = -T2m(3,1);
    R2m(3,2) = T2m(3,2);
    R2m(3,3) = T2m(3,3);
}

void SpecularMagnetic::LayerMatrixCoeff::calculateTRWithoutMagnetization()
{
    // T1m:
    T1m.setZero();
    T1m(1,1) = 0.5;
    T1m(1,3) = -std::sqrt(m_a)/2.0;
    T1m(3,1) = -1.0/(2.0*std::sqrt(m_a));
    T1m(3,3) = 0.5;

    // R1m:
    R1m.setZero();
    R1m(0,0) = 0.5;
    R1m(0,2) = -std::sqrt(m_a)/2.0;
    R1m(2,0) = -1.0/(2.0*std::sqrt(m_a));
    R1m(2,2) = 0.5;

    // T2m:
    T2m.setZero();
    T2m(1,1) = 0.5;
    T2m(1,3) = std::sqrt(m_a)/2.0;
    T2m(3,1) = 1.0/(2.0*std::sqrt(m_a));
    T2m(3,3) = 0.5;

    // R2m:
    R2m.setZero();
    R2m(0,0) = 0.5;
    R2m(0,2) = std::sqrt(m_a)/2.0;
    R2m(2,0) = 1.0/(2.0*std::sqrt(m_a));
    R2m(2,2) = 0.5;
}

complex_t SpecularMagnetic::getImExponential(complex_t exponent) const
{
    // TODO: add over- and underflow checks!
    return std::exp(complex_t(0.0, 1.0)*exponent);
}

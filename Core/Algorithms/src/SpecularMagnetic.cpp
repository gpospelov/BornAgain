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
    (void)k;
    size_t N = coeff.size();
    if (coeff[0].lambda == Eigen::Vector2cd::Zero() && N>1) {
        setForNoTransmission(coeff);
        return;
    }

    // First, initialize bottom layer values to have no reflection
    coeff[N-1].initializeBottomLayerPhiPsi();

    coeff[0].calculateTRMatrices();
    coeff[0].l = Eigen::Matrix4cd::Identity();
    for (int i=(int)N-2; i>0; --i) {
        coeff[i].calculateTRMatrices();
        double t = sample.getLayer(i)->getThickness();
        coeff[i].l =
               coeff[i].R1m * getImExponential((complex_t)(coeff[i].kz(0)*t)) +
               coeff[i].T1m * getImExponential((complex_t)(-coeff[i].kz(0)*t)) +
               coeff[i].R2m * getImExponential((complex_t)(coeff[i].kz(1)*t)) +
               coeff[i].T2m * getImExponential((complex_t)(-coeff[i].kz(1)*t));
        coeff[i].phi_psi_plus = coeff[i].l * coeff[i+1].phi_psi_plus;
        coeff[i].phi_psi_min = coeff[i].l * coeff[i+1].phi_psi_min;
    }
    // If more than one layer, impose normalization and correct correspondence
    // for spin-z polarization in top layer
    if (N>1) {
        // First layer boundary is also top layer boundary:
        coeff[0].l.setIdentity();
        coeff[0].phi_psi_plus = coeff[1].phi_psi_plus;
        coeff[0].phi_psi_min = coeff[1].phi_psi_min;
        // Normalize all boundary values such that top layer has unit wave
        // amplitude for both spin up and down (and does not contain a
        // transmitted wave amplitude for the opposite polarization)
        Eigen::Vector2cd T0plusV = coeff[0].T1plus() + coeff[0].T2plus();
        Eigen::Vector2cd T0minV = coeff[0].T1plus() + coeff[0].T2plus();
        complex_t cpp, cpm, cmp, cmm;
        cpp = T0minV(1);
        cpm = -T0plusV(1);
        cmp = T0minV(0);
        cmm = -T0minV(0);
        Eigen::Vector4cd phipsitemp = cpp * coeff[0].phi_psi_plus +
                cpm * coeff[0].phi_psi_min;
        coeff[0].phi_psi_min = cmp * coeff[0].phi_psi_plus +
                cmm * coeff[0].phi_psi_min;
        coeff[0].phi_psi_plus = phipsitemp;
        complex_t T0plus = coeff[0].phi_psi_plus(2);
        complex_t T0min = coeff[0].phi_psi_min(3);
        std::cout << T0plus << std::endl;
        std::cout << T0min << std::endl;
        coeff[0].phi_psi_min = coeff[0].phi_psi_min / T0min;
        coeff[0].phi_psi_plus = coeff[0].phi_psi_plus / T0plus;
        for (size_t i=1; i<N; ++i) {
            phipsitemp = ( cpp * coeff[i].phi_psi_plus +
                    cpm * coeff[i].phi_psi_min ) / T0plus;
            coeff[i].phi_psi_min = ( cmp * coeff[i].phi_psi_plus +
                    cmm * coeff[i].phi_psi_min ) / T0min;
            coeff[i].phi_psi_plus = phipsitemp;
        }
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
        coeff[i].phi_psi_plus.setZero();
        coeff[i].phi_psi_min.setZero();
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

void SpecularMagnetic::LayerMatrixCoeff::initializeBottomLayerPhiPsi()
{
    if (m_b_mag == 0.0) {
        phi_psi_plus << 0.0, -std::sqrt(m_a), 0.0, 1.0;
        phi_psi_min << -std::sqrt(m_a), 0.0, 1.0, 0.0;
        return;
    }
    // First basis vector that has no upward going wave amplitude
    phi_psi_plus(0) = m_scatt_matrix(0,1) * ( lambda(0)-lambda(1) ) /
            2.0/m_b_mag;
    phi_psi_plus(1) = ( m_bz  * (lambda(1)-lambda(0)) / m_b_mag -
            lambda(1) - lambda(0) )/2.0;
    phi_psi_plus(2) = 0.0;
    phi_psi_plus(3) = 1.0;

    // Second basis vector that has no upward going wave amplitude
    phi_psi_min(0) = - (m_scatt_matrix(0,0) + lambda(0) * lambda(1) ) /
            ( lambda(0) + lambda(1) );
    phi_psi_min(1) = m_scatt_matrix(1,0) * ( lambda(0) - lambda(1) ) /
            2.0/m_b_mag;
    phi_psi_min(2) = 1.0;
    phi_psi_min(3) = 0.0;
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

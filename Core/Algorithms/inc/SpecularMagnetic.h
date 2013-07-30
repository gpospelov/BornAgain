// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SpecularMagnetic.h
//! @brief     Defines class SpecularMagnetic.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARMAGNETIC_H_
#define SPECULARMAGNETIC_H_

#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"

#include <Eigen/Core>

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization

class SpecularMagnetic : public ISimulation
{
public:
    SpecularMagnetic() {}

   //! layer coefficients for matrix formalism
   class LayerMatrixCoeff {
   public:
       LayerMatrixCoeff() {}
       ~LayerMatrixCoeff() {}
       Eigen::Vector2cd T1plus() const;
       Eigen::Vector2cd R1plus() const;
       Eigen::Vector2cd T2plus() const;
       Eigen::Vector2cd R2plus() const;
       Eigen::Vector2cd T1min() const;
       Eigen::Vector2cd R1min() const;
       Eigen::Vector2cd T2min() const;
       Eigen::Vector2cd R2min() const;
       // R, T - amplitudes of reflected and transmitted waves
       Eigen::Vector2cd lambda; // positive eigenvalues of transfer matrix
       Eigen::Vector2cd kz;
       Eigen::Vector4cd phi_psi_plus; // boundary values for up-polarization
       Eigen::Vector4cd phi_psi_min; // boundary values for up-polarization
       Eigen::Matrix4cd l;
       Eigen::Matrix4cd T1m;
       Eigen::Matrix4cd R1m;
       Eigen::Matrix4cd T2m;
       Eigen::Matrix4cd R2m;
       Eigen::Matrix2cd m_scatt_matrix; // scattering matrix
       complex_t m_a; // polarization independent part
       complex_t m_b_mag; // magnitude of polarization part
       complex_t m_bz; // z-part of polarization scattering
       void calculateTRMatrices();
       void initializeBottomLayerPhiPsi();
   private:
       void calculateTRWithoutMagnetization();
   };

   //! multi layer coefficients for matrix formalism
   class MultiLayerMatrixCoeff
   {
   public:
       LayerMatrixCoeff& operator[](size_t i) { return m_data[i]; }
       const LayerMatrixCoeff& operator[](size_t i) const { return m_data[i]; }
       size_t size() const { return m_data.size(); }
       void clear() { m_data.clear(); }
       void resize(size_t size) { m_data.resize(size); }
   private:
       std::vector<LayerMatrixCoeff > m_data;
   };

   typedef MultiLayerMatrixCoeff MultiLayerCoeff_t; // set of layer coefficients for matrix formalism

   //! Calculates Fresnel coefficients for given multi layer and kvector
   void execute(const MultiLayer& sample, const kvector_t& k, MultiLayerCoeff_t& coeff);

private:
//   std::vector<Eigen::Matrix2cd> m_roughness_pmatrices;

   void calculateEigenvalues(const MultiLayer& sample, const kvector_t& k,
           MultiLayerCoeff_t& coeff) const;
   void calculateTransferAndBoundary(const MultiLayer& sample,
           const kvector_t& k, MultiLayerCoeff_t& coeff) const;
//   Eigen::Matrix2cd calculatePMatrix(double sigma_eff,
//           complex_t lambda_lower, complex_t lambda_upper) const;
   Eigen::Matrix2cd getUnitMatrix() const;
//   complex_t getPMatrixElement(complex_t sigma_lambda) const;
   void setForNoTransmission(MultiLayerCoeff_t& coeff) const;
   complex_t getImExponential(complex_t exponent) const;
};

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::T1plus() const {
    Eigen::Vector2cd result;
    result(0) = T1m.row(2).dot(phi_psi_plus);
    result(1) = T1m.row(3).dot(phi_psi_plus);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::R1plus() const {
    Eigen::Vector2cd result;
    result(0) = R1m.row(2).dot(phi_psi_plus);
    result(1) = R1m.row(3).dot(phi_psi_plus);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::T2plus() const {
    Eigen::Vector2cd result;
    result(0) = T2m.row(2).dot(phi_psi_plus);
    result(1) = T2m.row(3).dot(phi_psi_plus);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::R2plus() const {
    Eigen::Vector2cd result;
    result(0) = R2m.row(2).dot(phi_psi_plus);
    result(1) = R2m.row(3).dot(phi_psi_plus);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::T1min() const {
    Eigen::Vector2cd result;
    result(0) = T1m.row(2).dot(phi_psi_min);
    result(1) = T1m.row(3).dot(phi_psi_min);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::R1min() const {
    Eigen::Vector2cd result;
    result(0) = R1m.row(2).dot(phi_psi_min);
    result(1) = R1m.row(3).dot(phi_psi_min);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::T2min() const {
    Eigen::Vector2cd result;
    result(0) = T2m.row(2).dot(phi_psi_min);
    result(1) = T2m.row(3).dot(phi_psi_min);
    return result;
}

inline Eigen::Vector2cd SpecularMagnetic::LayerMatrixCoeff::R2min() const {
    Eigen::Vector2cd result;
    result(0) = R2m.row(2).dot(phi_psi_min);
    result(1) = R2m.row(3).dot(phi_psi_min);
    return result;
}

#endif /* SPECULARMAGNETIC_H_ */

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SpecularMatrix.h
//! @brief     Defines class SpecularMatrix.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPECULARMATRIX_H_
#define SPECULARMATRIX_H_

#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"
#include "ScalarRTCoefficients.h"
#include "EigenCore.h"


//! @class SpecularMatrix
//! @ingroup algorithms_internal
//! @brief Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer

class BA_CORE_API_ SpecularMatrix : public ISimulation
{
public:
    SpecularMatrix() {}

   //! multi layer coefficients for matrix formalism
   class MultiLayerMatrixCoeff
   {
   public:
       ScalarRTCoefficients& operator[](size_t i) { return m_data[i]; }
       const ScalarRTCoefficients& operator[](size_t i) const { return m_data[i]; }
       size_t size() const { return m_data.size(); }
       void clear() { m_data.clear(); }
       void resize(size_t size) { m_data.resize(size); }
   private:
       std::vector<ScalarRTCoefficients > m_data;
   };

   typedef MultiLayerMatrixCoeff MultiLayerCoeff_t; // set of layer coefficients for matrix formalism

   //! Returns reflection/transmission coefficients for given multi layer
   //! and wavevector k
   void execute(const MultiLayer& sample, const kvector_t& k, MultiLayerCoeff_t& coeff);

private:
   std::vector<Eigen::Matrix2cd> m_roughness_pmatrices;

   void calculateEigenvalues(const MultiLayer& sample, const kvector_t& k,
           MultiLayerCoeff_t& coeff) const;
   void calculateTransferAndBoundary(const MultiLayer& sample,
           const kvector_t& k, MultiLayerCoeff_t& coeff) const;
   Eigen::Matrix2cd calculatePMatrix(double sigma_eff,
           complex_t lambda_lower, complex_t lambda_upper) const;
   Eigen::Matrix2cd getUnitMatrix() const;
   complex_t getPMatrixElement(complex_t sigma_lambda) const;
   void setForNoTransmission(MultiLayerCoeff_t& coeff) const;
};

#endif /* SPECULARMATRIX_H_ */

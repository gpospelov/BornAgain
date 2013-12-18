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
#include "MatrixRTCoefficients.h"
#include "EigenCore.h"


//! @class SpecularMagnetic
//! @ingroup algorithms_internal
//! @brief Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer with magnetization

class BA_CORE_API_ SpecularMagnetic : public ISimulation
{
public:
    SpecularMagnetic() {}

   //! multilayer coefficients for matrix formalism
   class MultiLayerMatrixCoeff
   {
   public:
       MatrixRTCoefficients& operator[](size_t i) { return m_data[i]; }
       const MatrixRTCoefficients& operator[](size_t i) const {
           return m_data[i];
       }
       size_t size() const { return m_data.size(); }
       void clear() { m_data.clear(); }
       void resize(size_t size) { m_data.resize(size); }
   private:
       std::vector<MatrixRTCoefficients > m_data;
   };

   //! set of layer coefficients for matrix formalism
   typedef MultiLayerMatrixCoeff MultiLayerCoeff_t;

   //! Calculates reflection/transmission coefficients for given multi layer
   //! and wavevector k
   void execute(const MultiLayer& sample, const kvector_t& k,
           MultiLayerCoeff_t& coeff);

private:
   void calculateEigenvalues(const MultiLayer& sample, const kvector_t& k,
           MultiLayerCoeff_t& coeff) const;
   void calculateTransferAndBoundary(const MultiLayer& sample,
           const kvector_t& k, MultiLayerCoeff_t& coeff) const;
   Eigen::Matrix2cd getUnitMatrix() const;
   void setForNoTransmission(MultiLayerCoeff_t& coeff) const;
   complex_t getImExponential(complex_t exponent) const;
};

#endif /* SPECULARMAGNETIC_H_ */

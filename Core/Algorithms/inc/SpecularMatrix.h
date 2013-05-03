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

//! Implements the matrix formalism for the calculation of wave amplitudes of
//! the coherent wave solution in a multilayer

class SpecularMatrix : public ISimulation
{
public:
    SpecularMatrix() : m_use_roughness(false) {}

   //! layer coefficients for matrix formalism
   class LayerMatrixCoeff {
   public:
       LayerMatrixCoeff() : lambda(0), phi(0), psi(0), l11(0), l12(0), l21(0), l22(0) {}
       ~LayerMatrixCoeff() {}
       // A - amplitude of initial wave, R, T - amplitudes of reflected and transmitted waves
       complex_t lambda; // positive eigenvalue of transfer matrix
       complex_t phi;  // amplitude of the normalized derivative of wavefunction at top
       complex_t psi;  // amplitude of the wavefunction at top
       complex_t l11;  // matrix element of transfer matrix
       complex_t l12;  // matrix element of transfer matrix
       complex_t l21;  // matrix element of transfer matrix
       complex_t l22;  // matrix element of transfer matrix
   };

   //! multi layer coefficients for matrix formalism
   class MultiLayerMatrixCoeff
   {
   public:
       inline LayerMatrixCoeff& operator[](size_t i) { return m_data[i]; }
       inline const LayerMatrixCoeff& operator[](size_t i) const { return m_data[i]; }
       inline size_t size() const { return m_data.size(); }
       inline void clear() { m_data.clear(); }
       inline void resize(size_t size) { m_data.resize(size); }
   private:
       std::vector<LayerMatrixCoeff > m_data;
       complex_t R; // total reflection coefficient
       complex_t L11;
       complex_t L12;
       complex_t L21;
       complex_t L22;
   };

   typedef MultiLayerMatrixCoeff MultiLayerCoeff_t; // set of layer coefficients for matrix formalism

   //! Returns Fresnel coefficients for given multi layer and kvector
   void execute(const MultiLayer& sample, const kvector_t& k, MultiLayerCoeff_t& coeff);

private:
   bool m_use_roughness;

   void calculateEigenvalues(const MultiLayer& sample, const kvector_t& k, MultiLayerCoeff_t& coeff) const;
   void calculateTransferMatrices(const MultiLayer& sample, const kvector_t& k, MultiLayerCoeff_t& coeff) const;
   void calculateBoundaryValues(MultiLayerCoeff_t& coeff) const;
};

#endif /* SPECULARMATRIX_H_ */

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Material.h
//! @brief     materials-related global functions and utilities
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALUTILS_H_
#define MATERIALUTILS_H_

#include "Complex.h"
#include "Vectors3D.h"
#include "EigenCore.h"

//! Function for calculating the reduced potential, used for obtaining the Fresnel coefficients
//! (non-polarized material case)
complex_t ScalarReducedPotential(complex_t n, kvector_t k, double n_ref);

#ifndef SWIG
//! Function for calculating the reduced potential, used for obtaining the Fresnel coefficients
//! (polarized material case)
Eigen::Matrix2cd PolarizedReducedPotential(complex_t n, kvector_t b_field,
                                           kvector_t k, double n_ref);

//! Utility to compute magnetization correction for reduced potential and scattering length density
template <typename T>
BA_CORE_API_ Eigen::Matrix2cd MagnetizationCorrection(complex_t unit_factor, double magnetic_factor,
                                                      BasicVector3D<T> polarization);

#endif /* SWIG */

#endif /* MATERIALUTILS_H_ */

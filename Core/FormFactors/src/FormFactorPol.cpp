// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPol.cpp
//! @brief     Implements class FormFactorPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPol.h"

FormFactorPol* FormFactorPol::clone() const
{
    FormFactorPol *p_result = new FormFactorPol(mp_form_factor->clone());
    p_result->setRTInfo(*mp_magnetic_coeffs);
    p_result->setName(getName());
    return p_result;
}

Eigen::Matrix2cd FormFactorPol::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, double alpha_f, double phi_f) const
{
}

void FormFactorPol::setRTInfo(const MagneticCoefficientsMap& magnetic_coeff_map)
{
    delete mp_magnetic_coeffs;
    mp_magnetic_coeffs = magnetic_coeff_map.clone();
}

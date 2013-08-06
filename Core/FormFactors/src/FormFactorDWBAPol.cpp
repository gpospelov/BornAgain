// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDWBAPol.cpp
//! @brief     Defines class FormFactorDWBAPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBAPol.h"
#include "MagneticCoefficientsMap.h"
#include "Exceptions.h"

FormFactorDWBAPol::FormFactorDWBAPol(IFormFactor* p_formfactor)
: IFormFactorDecorator(p_formfactor)
, mp_magnetic_coeffs(0)
, mp_material(0)
, mp_ambient_material(0)
{
    setName("FormFactorDWBAPol");
}

FormFactorDWBAPol::~FormFactorDWBAPol()
{
    delete mp_magnetic_coeffs;
}

FormFactorDWBAPol* FormFactorDWBAPol::clone() const
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(mp_form_factor->clone());
    p_result->setRTInfo(*mp_magnetic_coeffs);
    p_result->setName(getName());
    return p_result;
}

void FormFactorDWBAPol::setRTInfo(
        const MagneticCoefficientsMap& magnetic_coeff_map)
{
    delete mp_magnetic_coeffs;
    mp_magnetic_coeffs = magnetic_coeff_map.clone();
}

Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    calculateTerms(k_i, k_f_bin, alpha_i, alpha_f);
    //TODO: replace with real result!
    return Eigen::Matrix2cd::Zero();
}

void FormFactorDWBAPol::calculateTerms(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const
{
    (void)k_i;
    (void)k_f_bin;
    (void)alpha_i;
    (void)alpha_f;
    //TODO: here comes the bulk of the DWBA calculation
}

Eigen::Matrix2cd FormFactorDWBAPol::getScatteringPotential(
        const kvector_t& k) const
{
    if (!mp_material || !mp_ambient_material) {
        throw ClassInitializationException("FormFactorDWBAPol::"
                "getScatteringPotential: materials not yet initialized");
    }
    return mp_material->getScatteringMatrix(k) -
            mp_ambient_material->getScatteringMatrix(k);
}

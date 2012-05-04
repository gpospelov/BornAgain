/*
 * DWBAFormFactor.cpp
 *
 *  Created on: Apr 26, 2012
 *      Author: herck
 */

#include "DWBAFormFactor.h"

DWBAFormFactor::DWBAFormFactor(IFormFactor *p_form_factor)
    : mp_form_factor(p_form_factor)
    , mp_T(0), mp_R(0)
{
}

DWBAFormFactor::~DWBAFormFactor()
{
    delete mp_form_factor;
}

complex_t DWBAFormFactor::evaluate(kvector_t k_i, kvector_t k_f) const
{
    kvector_t k_i_mirror_xy(k_i.x(), k_i.y(), -k_i.z());
    kvector_t k_f_mirror_xy(k_f.x(), k_f.y(), -k_f.z());
    double alpha_i = -std::asin(k_i.z()/k_i.mag());
    double alpha_f = std::asin(k_f.z()/k_f.mag());
    // The four different scattering contributions; S stands for scattering off the particle, R for reflection off the layer interface
    complex_t term_S = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_f);
    complex_t term_RS = getR(alpha_i)*mp_form_factor->evaluate(k_i_mirror_xy, k_f);
    complex_t term_SR = getT(alpha_i)*mp_form_factor->evaluate(k_i, k_f_mirror_xy)*getX(alpha_f);
    complex_t term_RSR = getR(alpha_i)*mp_form_factor->evaluate(k_i_mirror_xy, k_f_mirror_xy)*getX(alpha_f);
    return term_S + term_RS + term_SR + term_RSR;
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTetrahedron.cpp
//! @brief     Implements class FormFactorTetrahedron.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTetrahedron.h"
#include "StochasticDiracDelta.h"
#include "MathFunctions.h"

FormFactorTetrahedron::FormFactorTetrahedron(
    double height, double half_side, double alpha)
{
    setName("FormFactorTetrahedron");
    m_height = height;
    m_half_side = half_side;
    m_alpha = alpha;
    m_root3 = std::sqrt(3.0);
    init_parameters();
}

void FormFactorTetrahedron::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("half_side", &m_half_side);
    registerParameter("alpha", &m_alpha);
}

FormFactorTetrahedron* FormFactorTetrahedron::clone() const
{
    FormFactorTetrahedron *result =
        new FormFactorTetrahedron(m_height, m_half_side, m_alpha);
    result->setName(getName());
    return result;
}

complex_t FormFactorTetrahedron::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double R = m_half_side;
    double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    complex_t F;
    const complex_t im(0,1);

    if (std::abs(qx)==0.0 && std::abs(qy)==0.0) {
        complex_t qzH_half = qz*H/2.0;
        //WRONG
        F = m_root3*R*R*H*std::exp(im*qzH_half)*MathFunctions::Sinc(qzH_half);
    }
    else {
        if (std::abs(qx*qx-3.0*qy*qy)==0.0) {
            complex_t qa = 2.*qy/tga + qz/2.;
            complex_t qb = - qy/tga + qz/2.;
            F = H/2.*m_root3*std::exp(im*2.*qy*R/m_root3)*(
                        - std::exp(im*qa*H-im*2.*m_root3*qy*R)*MathFunctions::Sinc(qa*H)
                        + std::exp(im*qb*H)*MathFunctions::Sinc(qb*H)*
                        ( 1.- 3.*qy/(tga*qb) - im*2.*m_root3*qy*R )
                        + 3.*qy/(qb*tga)*std::exp(im*2.*qb*H)
                        )/( qx*qx ) ;
        } else {

            complex_t q1, q2, q3;
            double L;
            L = 2.*tga*R/m_root3-H;
            q3 = (qy/tga - qz/2.);

            if (std::abs(qx)==0.0) {

               F = - 2.*H*MathFunctions::Sinc(q3*H)*
                       std::exp(im*(q3*L+qz*R*tga/m_root3))/((m_root3*qy*qy));

            } else {

            q1=(1./2.)*((m_root3*qx-qy)/tga - qz);
            q2=(1./2.)*((m_root3*qx+qy)/tga + qz);

            F = -(1. + m_root3*qy/qx)*MathFunctions::Sinc(q1*H)*std::exp(im*q1*L)
                -(1. - m_root3*qy/qx)*MathFunctions::Sinc(q2*H)*std::exp(-im*q2*L)
                + 2.*MathFunctions::Sinc(q3*H)*std::exp(im*q3*L);

            F = F*H*std::exp(im*qz*R*tga/m_root3)*m_root3/((qx*qx-3.*qy*qy));}
        }
    }

    return F;
}




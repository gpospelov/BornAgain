// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorztruncatedCube.cpp
//! @brief     Implements class FormFactorTruncatedCube.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTruncatedCube.h"
#include "FormFactorBox.h"
#include "MathFunctions.h"

FormFactorTruncatedCube::FormFactorTruncatedCube(
   double length, double removed_length)
{
    setName("FormFactorTruncatedCube");
    m_length = length;
    m_removed_length = removed_length;

    assert(m_removed_length <= 0.5*m_length);
    init_parameters();

}

void FormFactorTruncatedCube::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length);
    registerParameter("removed_length", &m_removed_length);
}

FormFactorTruncatedCube* FormFactorTruncatedCube::clone() const
{
    FormFactorTruncatedCube *result =
        new FormFactorTruncatedCube(m_length, m_removed_length);
    result->setName(getName());
    return result;
}

complex_t FormFactorTruncatedCube::FormFactorVertex(const cvector_t& q) const
{
    double L = m_length;
    double t = m_removed_length;
    const complex_t im(0.,1.);
    complex_t ecke = 0.0;
    complex_t qz = q.z();
    complex_t qy = q.y();
    complex_t qx = q.x();
    complex_t expiqyt = std::exp(im*qy*t);
    complex_t expiqzt = std::exp(im*qz*t);
    complex_t qxhL = 0.5*qx*L;
    complex_t qyhL = 0.5*qy*L;
    complex_t expiqxhL = std::exp(im*qxhL);
    complex_t expiqyhL = std::exp(im*qyhL);


    if (std::abs(qz) <= Numeric::double_epsilon)
    {
        if (std::abs(qx) <= Numeric::double_epsilon)
        {
            if (std::abs(qy) <= Numeric::double_epsilon)
            {
                // Volume
                ecke = 1./6.*t*t*t;
            }
            else
            {
                ecke = -im* expiqyhL*(0.5*qy*qy*t*t + im*qy*t - 1. + std::exp(-im*qy*t))/(qy*qy*qy);
            }
        }
        else
        {
            if (std::abs(qy) <= Numeric::double_epsilon)
            {
                ecke = -im*expiqxhL*(0.5*qx*qx*t*t + im*qx*t - 1. + std::exp(-im*qx*t))/(qx*qx*qx);
            }
            else
            {
                ecke = im*expiqxhL*expiqyhL*std::exp(-0.5*im*t*(qx + qy))*(
                            std::exp(0.5*im*t*(qx + qy))*(im*qx*qy*t - qx - qy)
                            + (qx + qy)*std::cos(0.5*t*(qx - qy))
                            + 0.5*im*t*(qx*qx + qy*qy)*MathFunctions::Sinc(0.5*(qx - qy)*t)
                            )/(qy*qy*qx*qx);
            }
        }
    }
    //qz!=0
    else
    {
        if (std::abs(qy) <= Numeric::double_epsilon)
        {
            if (std::abs(qx) <= Numeric::double_epsilon)
            {
                ecke = im*(0.5*qz*t*qz*t - im*qz*t + expiqzt - 1.)/(qz*qz*qz);
            }
            else
            {
                ecke = -im*expiqxhL*(
                            (qz - qx)*std::exp(-im*qx*t)
                            + im*qx*qz*t + qx - qz
                            - im*qx*qx*t*std::exp(0.5*t*im*(qz - qx))*MathFunctions::Sinc(0.5*(qx + qz)*t)
                            )/(qz*qz*qx*qx);
            }
        }
        // qy !=0
        else
        {
            if (std::abs(qz+qy) <= Numeric::double_epsilon)
            {
                if (std::abs(qx-qy) <= Numeric::double_epsilon)
                {
                    ecke = im*expiqyhL*expiqyhL*(
                                1. + (0.5*qy*t*qy*t - im*qy*t - 1.)*std::exp(-im*qy*t)
                                )/(qy*qy*qy);
                 }
                else
                {
                    if (std::abs(qx) <= Numeric::double_epsilon)
                   {
                         ecke = - expiqyhL*(
                                     qy*t + 2.*im + std::exp(-im*qy*t)*(qy*t - 2.*im)
                                     )/(qy*qy*qy);
                    }
                    else
                    {
                        ecke = -im*expiqxhL*expiqyhL*(qx*std::exp(-im*qy*t)*(im*t*qy*(qx - qy) + qx - 2.*qy)
                                    - (qx - qy)*(qx - qy) + std::exp(-im*qx*t)*qy*qy
                                    )/((qx - qy)*(qx - qy)*qy*qy*qx);
                    }
                }
            }
            // qz!=qy
            else {
                   if (std::abs(qx) <= Numeric::double_epsilon)
                   {
                     ecke = im*expiqyhL*(
                                 std::exp(im*.5*(qz - qy)*t)*(
                                     (qy - qz)*std::cos(.5*t*(qy + qz))
                                     + .5*im*t*(qy*qy + qz*qz)*MathFunctions::Sinc(.5*t*(qy + qz))
                                     )
                                 -im*qy*qz*t - qy + qz
                                 )/(qy*qy*qz*qz);
                   }
                   else
                   {
                      // General case
                     ecke = t/qz*expiqxhL*expiqyhL*std::exp(-im*qx*0.5*t)*(
                                 MathFunctions::Sinc(0.5*qx*t)/qy
                                 - qz/(qy*(qy + qz))*std::exp(-.5*im*qy*t)*MathFunctions::Sinc(.5*(qx - qy)*t)
                                 - std::exp(.5*im*qz*t)*MathFunctions::Sinc(.5*(qx + qz)*t)/(qy + qz)
                                 );
                   }
                 }
        }
    }
    return ecke;
}

complex_t FormFactorTruncatedCube::evaluate_for_q(const cvector_t& q) const
{
    FormFactorBox fffull(m_length, m_length, m_length);
    complex_t ffcube = fffull.evaluate_for_q(q);
    const complex_t im(0.0,1.0);

    complex_t qz = q.z();
    complex_t qy = q.y();
    complex_t qx = q.x();
    cvector_t rotatq1 = q;
    cvector_t rotatq2(qy, -qx, qz);
    cvector_t rotatq3(-qx, -qy, qz);
    cvector_t rotatq4(-qy, qx, qz);
    cvector_t rotatq5(qx, qy, -qz);
    cvector_t rotatq6(qy, -qx, -qz);
    cvector_t rotatq7(-qx, -qy, -qz);
    cvector_t rotatq8(-qy, qx, -qz);

    complex_t ffE1 = FormFactorVertex(rotatq1);
    complex_t ffE2 = FormFactorVertex(rotatq2);
    complex_t ffE3 = FormFactorVertex(rotatq3);
    complex_t ffE4 = FormFactorVertex(rotatq4);
    complex_t ffE5 = FormFactorVertex(rotatq5);
    complex_t ffE6 = FormFactorVertex(rotatq6);
    complex_t ffE7 = FormFactorVertex(rotatq7);
    complex_t ffE8 = FormFactorVertex(rotatq8);

    complex_t result = ffcube - ffE1 - ffE2 - ffE3 - ffE4 + std::exp(im*qz*m_length)*(-ffE5 - ffE6 - ffE7 - ffE8);

    return result;
}

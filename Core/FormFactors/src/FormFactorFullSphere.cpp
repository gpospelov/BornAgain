// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorFullSphere.h"
#include "StochasticDiracDelta.h"
//#include "Numeric.h"
#include "MathFunctions.h"

//#include <cmath>

FormFactorFullSphere::FormFactorFullSphere(double radius)
{
    setName("FormFactorFullSphere");
    m_radius = radius;
    init_parameters();
}

FormFactorFullSphere::~FormFactorFullSphere()
{
}

//! initialize pool parameters, i.e. register some of class members for later access via parameter pool

void FormFactorFullSphere::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("radius", &m_radius);
}


FormFactorFullSphere* FormFactorFullSphere::clone() const
{
    FormFactorFullSphere *p_clone = new FormFactorFullSphere(m_radius);
    return p_clone;
}

complex_t FormFactorFullSphere::evaluate_for_q(const cvector_t &q) const
{
    complex_t qz = q.z();
    double R = m_radius;

    complex_t iqzR = complex_t(0.0, 1.0)*qz*R;
    complex_t z_part = std::exp(iqzR);

    complex_t qR = std::sqrt( std::norm(q.x()) + std::norm(q.y()) + std::norm(qz) )*R;
    double volume = 4*M_PI*R*R*R/3;
    complex_t radial;
    if (std::abs(qR) < Numeric::double_epsilon) {
        radial = volume;
    }
    else {
        // way1 (standard)
        //radial = 3*volume*(std::sin(qR) - qR*std::cos(qR))/(qR*qR*qR);

        // way2 (fast)
        radial = 3*volume*(MathFunctions::FastSin(qR) - qR*MathFunctions::FastCos(qR))/(qR*qR*qR);

        // way3 (experimental)
        // complex_t xsin, xcos;
        // MathFunctions::FastSinCos(qR, xsin, xcos);
        // radial = 3*volume*(xsin - qR*xcos)/(qR*qR*qR);
    }

    return radial*z_part;
}

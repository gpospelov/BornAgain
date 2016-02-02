// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism6.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorPrism6::FormFactorPrism6(double radius, double height)
{
    setName(FFPrism6Type);
    m_height = height;
    m_radius = radius;
    check_initialization();
    init_parameters();
}

bool FormFactorPrism6::check_initialization() const
{
    return true;
}

void FormFactorPrism6::init_parameters()
{
    clearParameterPool();
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
}

FormFactorPrism6* FormFactorPrism6::clone() const
{
    return new FormFactorPrism6(m_radius, m_height);
}

void FormFactorPrism6::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

//! Returns a contribution C_j to the form factor F(q)=sum_j^n 4 C_j/q^2 of a 2n-gon with
//! twofold symmetry axis at 0.

complex_t FormFactorPrism6::ff_term(
    complex_t qRx, complex_t qRy, double xi, double yi, double xf, double yf ) const
{
    complex_t qRj = ( qRx*(xf+xi) + qRy*(yf+yi) ) / 2.;
    complex_t qEj = ( qRx*(xf-xi) + qRy*(yf-yi) ) / 2.;
    complex_t qWj = ( qRx*(yf-yi) - qRy*(xf-xi) ) / 2.;
    return qWj * qRj * MathFunctions::sinc(qEj) * MathFunctions::sinc(qRj);
}

complex_t FormFactorPrism6::evaluate_for_q(const cvector_t& q) const
{
    static double root3d2 = std::sqrt(3.0) / 2;
    complex_t qz = q.z();
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = qz * H / 2.0;
    complex_t z_part = H * MathFunctions::sinc(qzH_half) * std::exp(complex_t(0.0, 1.0) * qzH_half);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (q.x() == 0.0 && q.y() == 0.0) {
        xy_part = 3. * root3d2 * R * R;
    } else {
        complex_t qRx = q.x() * R;
        complex_t qRy = q.y() * R;
        xy_part += ff_term( qRx, qRy, root3d2, -.5, root3d2, +.5 );
        xy_part += ff_term( qRx, qRy, root3d2, +.5, 0., 1. );
        xy_part += ff_term( qRx, qRy, 0., 1., -root3d2, +.5 );
        xy_part *= 4. / ( q.x()*conj(q.x()) + q.y()*conj(q.y()) );
        /*
        if (std::abs(3.0 * q.y() * q.y() - q.x() * q.x()) == 0.0) {
            complex_t qyRr3_half = q.y() * R * root3d2;
            xy_part = R * R * root3d2 * MathFunctions::sinc(qyRr3_half)
                      * (MathFunctions::sinc(qyRr3_half) + 2.0 * std::cos(qyRr3_half));
        } else {
            complex_t qxR_half = (q.x() * R) / 2.0;
            complex_t qyRr3_half = q.y() * R * root3d2.;

            xy_part = (8.0 * root3d2
                       * (3.0 / 4.0 * q.y() * R * q.y() * R * MathFunctions::sinc(qxR_half)
                          * MathFunctions::sinc(qyRr3_half) + std::cos(2.0 * qxR_half)
                          - std::cos(qyRr3_half) * std::cos(qxR_half)))
                      / (3.0 * q.y() * q.y() - q.x() * q.x());
        }
        */
    }
    return xy_part*z_part;
}

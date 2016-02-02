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

complex_t FormFactorPrism6::evaluate_for_q(const cvector_t& q) const
{
    static double root3 = std::sqrt(3.0);
    complex_t qz = q.z();
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = qz * H / 2.0;
    complex_t z_part = H * MathFunctions::sinc(qzH_half) * std::exp(complex_t(0.0, 1.0) * qzH_half);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (q.x() == 0.0 && q.y() == 0.0) {
        xy_part = 3. * root3 / 2. * R * R;
    } else {
        if (std::abs(3.0 * q.y() * q.y() - q.x() * q.x()) == 0.0) {
            complex_t qyRr3_half = q.y() * R * root3 / 2.;
            xy_part = R * R * root3 / 2.0 * MathFunctions::sinc(qyRr3_half)
                      * (MathFunctions::sinc(qyRr3_half) + 2.0 * std::cos(qyRr3_half));
        } else {
            complex_t qxR_half = (q.x() * R) / 2.0;
            complex_t qyRr3_half = q.y() * R * root3 / 2.;

            xy_part = (4.0 * root3
                       * (3.0 / 4.0 * q.y() * R * q.y() * R * MathFunctions::sinc(qxR_half)
                          * MathFunctions::sinc(qyRr3_half) + std::cos(2.0 * qxR_half)
                          - std::cos(qyRr3_half) * std::cos(qxR_half)))
                      / (3.0 * q.y() * q.y() - q.x() * q.x());
        }
    }
    return xy_part*z_part;
}

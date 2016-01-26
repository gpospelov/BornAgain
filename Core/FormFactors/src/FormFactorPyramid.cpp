// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPyramid.cpp
//! @brief     Implements class FormFactorPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPyramid.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorPyramid::FormFactorPyramid(
    double length, double height, double alpha)
{
    setName(FFPyramidType);
    m_length = length;
    m_height = height;
    m_alpha = alpha;
    check_initialization();
    init_parameters();
}

bool FormFactorPyramid::check_initialization() const
{
    bool result(true);
    if(m_alpha<0.0 || m_alpha>Units::PID2) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters ";
        ostr << " length:" << m_length;
        ostr << " height:" << m_height;
        ostr << " alpha:" << m_alpha << "\n\n";
        ostr << "Check for '0 <= alpha <= pi/2' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    if(m_length<0.0 || m_height<0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters ";
        ostr << " length:" << m_length;
        ostr << " height:" << m_height;
        ostr << " alpha:" << m_alpha << "\n\n";
        ostr << "Check for '0 <= length and 0 <= height' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    if(2.*m_height > m_length*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorPyramid() -> Error in class initialization with parameters ";
        ostr << " length:" << m_length;
        ostr << " height:" << m_height;
        ostr << " alpha:" << m_alpha << "\n\n";
        ostr << "Check for '2.*height <= length*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorPyramid::init_parameters()
{
    clearParameterPool();
    registerParameter(Length, &m_length, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
    registerParameter(Alpha, &m_alpha, AttLimits::n_positive());
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
    return new FormFactorPyramid(m_length, m_height, m_alpha);
}

void FormFactorPyramid::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorPyramid::getRadius() const
{
    return m_length/2.0;
}

complex_t FormFactorPyramid::evaluate_for_q(const cvector_t& q) const
{

    double H = m_height;
    double R = m_length/2.;
    double tga = std::tan(m_alpha);
    if (m_height == 0.0) return 0.0;
    if (m_alpha == 0.0) return 0.0;
    if (m_length == 0.0) return 0.0;

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    const complex_t im(0, 1);
    complex_t full = fullPyramidPrimitive(qx/tga, qy/tga, qz, -R*tga);
    complex_t top = fullPyramidPrimitive(qx/tga, qy/tga, qz, H-R*tga);
    return std::exp(im*qz*R*tga) * (full-top) / (tga*tga);
}

complex_t FormFactorPyramid::fullPyramidPrimitive(complex_t a, complex_t b, complex_t c,
                                                  double z) const
{
    const complex_t im(0, 1);
    if (std::norm(a * z) > Numeric::double_epsilon && std::norm(b * z) > Numeric::double_epsilon) {
        if (std::abs((a - b) * (a - b) - c * c) * z * z > Numeric::double_epsilon
            && std::abs((a + b) * (a + b) - c * c) * z * z > Numeric::double_epsilon) {
            complex_t phase = std::exp(im * c * z);
            complex_t numerator
                = std::sin(a * z) * (b * (a * a - b * b + c * c) * std::cos(b * z)
                                     + im * c * (a * a + b * b - c * c) * std::sin(b * z))
                  + a * std::cos(a * z) * ((-a * a + b * b + c * c) * std::sin(b * z)
                                           + 2.0 * im * b * c * std::cos(b * z));
            complex_t denominator = a * b * (a - b - c) * (a + b - c) * (a - b + c) * (a + b + c);
            return -4.0 * phase * numerator / denominator;
        } else {
            return 2.0 * (g(a - b, c, z) - g(a + b, c, z)) / (a * b);
        }
    } else if (std::norm(a * z) <= Numeric::double_epsilon
               && std::norm(b * z) <= Numeric::double_epsilon) {
        if (std::norm(c * z) <= Numeric::double_epsilon) {
            return -4.0 * std::pow(z, 3) / 3.0;
        } else
            return 4.0 * im
                   * (2.0 + std::exp(im * c * z) * (c * c * z * z + 2.0 * im * c * z - 2.0))
                   / std::pow(c, 3);
    } else {
        complex_t abmax;
        if (std::norm(b * z) <= Numeric::double_epsilon) {
            abmax = a;
        } else {
            abmax = b;
        }
        return 2.0 * (h(c - abmax, z) - h(c + abmax, z)) / abmax;
    }
}

complex_t FormFactorPyramid::g(complex_t x, complex_t c, double z) const
{
    const complex_t im(0, 1);
    if (std::abs((x*x-c*c)*z*z) > Numeric::double_epsilon) {
        return (im*c - std::exp(im*c*z)*(x*std::sin(x*z) + im*c*std::cos(x*z))) / (x*x-c*c);
    } else {
        if (std::norm(c*z) > Numeric::double_epsilon) {
            return im * (std::exp(2.0*im*c*z) + 2.0*im*c*z - 1.0) / (4.0*c);
        } else {
            return -z;
        }
    }
}

complex_t FormFactorPyramid::h(complex_t x, double z) const
{
    const complex_t im(0, 1);
    if (std::norm(x*z) > Numeric::double_epsilon) {
        return (im - (im+x*z)*std::exp(im*x*z))/(x*x);
    }
    return -im*z*z/2.0;
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorAnisoPyramid.cpp
//! @brief     Implements class FormFactorAnisoPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorAnisoPyramid.h"
#include "MathFunctions.h"

FormFactorAnisoPyramid::FormFactorAnisoPyramid(
    double length, double width, double height, double alpha)
{
    setName("FormFactorAnisoPyramid");
    m_length = length;
    m_width = width;
    m_height = height;
    m_alpha = alpha;
    check_initialization();
    init_parameters();
}

bool FormFactorAnisoPyramid::check_initialization() const
{
    bool result(true);
    if(m_alpha<0.0 || m_alpha>Units::PID2) {
        std::ostringstream ostr;
        ostr << "FormFactorAnisoPyramid() -> Error in class initialization with parameters ";
        ostr << " length:" << m_length;
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " alpha:" << m_alpha << "\n\n";
        ostr << "Check for '0 <= alpha <= pi/2' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    if(m_length<0.0 || m_width<0.0 || m_height<0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorAnisoPyramid() -> Error in class initialization with parameters ";
        ostr << " length:" << m_length;
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " alpha:" << m_alpha << "\n\n";
        ostr << "Check for '0 <= length, 0<= width and 0 <= height' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    if(2.*m_height > std::min(m_length, m_width)*std::tan(m_alpha)) {
        std::ostringstream ostr;
        ostr << "FormFactorAnisoPyramid() -> Error in class initialization ";
        ostr << "with parameters length:" << m_length;
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*height > min(length, width)*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorAnisoPyramid::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length, AttLimits::n_positive());
    registerParameter("width", &m_width, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
    registerParameter("alpha", &m_alpha, AttLimits::n_positive());
}

FormFactorAnisoPyramid* FormFactorAnisoPyramid::clone() const
{
    FormFactorAnisoPyramid *result =
        new FormFactorAnisoPyramid(m_length, m_width, m_height, m_alpha);
    result->setName(getName());
    return result;
}

complex_t FormFactorAnisoPyramid::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double L = m_length;
    double W = m_width;
    double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    const complex_t im(0,1);
    if (L < W) {
        complex_t full = fullAnisoPyramidPrimitive(qx/tga, qy/tga, qz, (W-L)*tga/2.0, -L*tga/2.0);
        complex_t top = fullAnisoPyramidPrimitive(qx/tga, qy/tga, qz, (W-L)*tga/2.0, H-L*tga/2.0);
        return std::exp(im*qz*L*tga/2.0) * (full-top) / (tga*tga);
    } else {
        complex_t full = fullAnisoPyramidPrimitive(qy/tga, qx/tga, qz, (L-W)*tga/2.0, -W*tga/2.0);
        complex_t top = fullAnisoPyramidPrimitive(qy/tga, qx/tga, qz, (L-W)*tga/2.0, H-W*tga/2.0);
        return std::exp(im*qz*W*tga/2.0) * (full-top) / (tga*tga);
    }
}

complex_t FormFactorAnisoPyramid::fullAnisoPyramidPrimitive(complex_t a, complex_t b, complex_t c,
                                                            double d, double z) const
{
    const complex_t im(0, 1);
    if (std::norm(a*z) > Numeric::double_epsilon && std::norm(b*z) > Numeric::double_epsilon) {
        if (std::abs((a-b)*(a-b)-c*c)*z*z > Numeric::double_epsilon &&
            std::abs((a+b)*(a+b)-c*c)*z*z > Numeric::double_epsilon) {
            complex_t phase = std::exp(im * c * z);
            complex_t numerator = std::sin(a*z) * (b*(a*a - b*b + c*c)*std::cos(b*(d-z))
                                                   -im*c*(a*a + b*b - c*c)*std::sin(b*(d-z)))
                              + a*std::cos(a*z)*((a*a - b*b - c*c)*std::sin(b*(d-z))
                                                 + 2.0*im*b*c*std::cos(b*(d-z)));
            complex_t denominator = a*b*(a - b - c)*(a + b - c)*(a - b + c)*(a + b + c);
            return -4.0 * phase * numerator / denominator;
        } /* else {
            return 2.0 * (g(a-b, c, z) - g(a+b, c, z)) / (a*b);
        }
    } else if (std::norm(a*z) <= Numeric::double_epsilon
               && std::norm(b*z) <= Numeric::double_epsilon) {
        if (std::norm(c*z) <= Numeric::double_epsilon) {
            return -4.0*std::pow(z, 3)/3.0;
        } else
            return 4.0*im * (2.0 + std::exp(im*c*z)*(c*c*z*z + 2.0*im*c*z - 2.0)) / std::pow(c, 3);
    } else {
        complex_t abmax;
        if (std::norm(b*z) <= Numeric::double_epsilon && std::norm(a*z) > Numeric::double_epsilon) {
            abmax = a;
        } else {
            abmax = b;
        }
        return 2.0 * (h(c - abmax, z) - h(c + abmax, z)) / abmax; */
    }
    return 0.0;
}




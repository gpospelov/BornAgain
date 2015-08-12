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
#include "MathFunctions.h"

FormFactorPyramid::FormFactorPyramid(
    double length, double height, double alpha)
{
    setName("FormFactorPyramid");
    m_length = length;
    m_height = height;
    m_alpha = alpha;
    check_initialization();
    init_parameters();
}

bool FormFactorPyramid::check_initialization() const
{
    bool result(true);
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
    registerParameter("length", &m_length, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
    registerParameter("alpha", &m_alpha, AttLimits::n_positive());
}

FormFactorPyramid* FormFactorPyramid::clone() const
{
    FormFactorPyramid *result =
        new FormFactorPyramid(m_length, m_height, m_alpha);
    result->setName(getName());
    return result;
}

complex_t FormFactorPyramid::evaluate_for_q(const cvector_t& q) const
{

    double H = m_height;
    double R = m_length/2.;
    double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

//    // comparison with isgisaxs trick
//        double gisaxs_epsilon = 2.2204460492503131e-12;
//        qx < 0 ? qx -= gisaxs_epsilon : qx += gisaxs_epsilon;
//        qy < 0 ? qy -= gisaxs_epsilon : qy += gisaxs_epsilon;
//        //double Z = 45.*Units::deg;
//        //double qx =  std::cos(Z)*q.x() + std::sin(Z)*q.y();
//        //double qy = -std::sin(Z)*q.x() + std::cos(Z)*q.y();

    complex_t F;
    const complex_t im(0, 1);
    if (std::norm(qx) > Numeric::double_epsilon && std::norm(qy) > Numeric::double_epsilon) {
        complex_t full = fullPyramidPrimitive(qx/tga, qy/tga, qz, -R*tga);
        complex_t top = fullPyramidPrimitive(qx/tga, qy/tga, qz, H-R*tga);
        F = std::exp(im*qz*R*tga)*(full-top)/(tga*tga);
    } else if (std::norm(qx) <= Numeric::double_epsilon
               && std::norm(qy) <= Numeric::double_epsilon) {
        if (std::norm(qz) <= Numeric::double_epsilon)
            F = 4. / 3. * tga * R * R * R
                * (1. - (1. - H / R / tga) * (1. - H / R / tga) * (1. - H / R / tga));
        else
            F = 4. * im * (-2. / tga / tga - 2. * im * qz * R / tga + qz * qz * R * R
                           - std::exp(im * H * qz) * ((-1. + im + H * qz) / tga - qz * R)
                             * ((1. + im + H * qz) / tga - qz * R)) / std::pow(qz, 3);
    } else {
        complex_t qxy;
        if (std::norm(qy) <= Numeric::double_epsilon && std::norm(qx) > Numeric::double_epsilon) {
            qxy = qx;
        } else {
            qxy = qy;
        }
        F = (4. * (qxy * tga * (-(qxy * qxy * R) + qz * tga * (complex_t(0.0, -2.0) + qz * R * tga))
                   * std::cos(qxy * R)
                   - std::exp(im * H * qz) * qxy
                     * (H * std::pow(qxy, 2) - qxy * qxy * R * tga
                        - qz * (complex_t(0.0, 2.0) + H * qz) * std::pow(tga, 2)
                        + std::pow(qz, 2) * R * std::pow(tga, 3)) * std::cos(qxy * (R - H / tga))
                   + tga * (std::pow(qxy, 2) * (1. - complex_t(0.0, 1.0) * qz * R * tga)
                            + std::pow(qz, 2) * std::pow(tga, 2)
                              * (1. + complex_t(0.0, 1.0) * qz * R * tga)) * std::sin(qxy * R)
                   + complex_t(0.0, 1.0) * std::exp(im * H * qz) * tga
                     * (std::pow(qz, 2) * std::pow(tga, 2)
                        * (complex_t(0.0, 1.0) + H * qz - qz * R * tga)
                        + std::pow(qxy, 2) * (complex_t(0.0, 1.0) - H * qz + qz * R * tga))
                     * std::sin(qxy * (R - H / tga))))
            / (qxy * std::pow(qxy - qz * tga, 2) * std::pow(qxy + qz * tga, 2));
    }
    return F;
}

complex_t FormFactorPyramid::fullPyramidPrimitive(complex_t a, complex_t b, complex_t c,
                                                  double z) const
{
    const complex_t im(0, 1);
    complex_t phase = std::exp(im * c * z);
    complex_t nominator = std::sin(a * z) * (b * (a * a - b * b + c * c) * std::cos(b * z)
                                             + im * c * (a * a + b * b - c * c) * std::sin(b * z))
                          + a * std::cos(a * z) * ((-a * a + b * b + c * c) * std::sin(b * z)
                                                   + 2.0 * im * b * c * std::cos(b * z));
    complex_t denominator = a * b * (a - b - c) * (a + b - c) * (a - b + c) * (a + b + c);
    return -4.0 * phase * nominator / denominator;
}

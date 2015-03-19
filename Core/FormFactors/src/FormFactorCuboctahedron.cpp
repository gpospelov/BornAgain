// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCuboctahedron.cpp
//! @brief     Implements class FormFactorCuboctahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCuboctahedron.h"
#include "FormFactorPyramid.h"
#include "MathFunctions.h"

FormFactorCuboctahedron::FormFactorCuboctahedron(
    double length, double height, double height_ratio, double alpha)
{
    setName("FormFactorCuboctahedron");
    m_height = height;
    m_length = length;
    m_height_ratio = height_ratio;
    m_alpha = alpha;
    assert(2.*m_height <= m_length*std::tan(m_alpha)*std::min(1.,1.0/m_height_ratio));
    check_initialization();
    init_parameters();
}

bool FormFactorCuboctahedron::check_initialization() const
{
    bool result(true);
    if(2.*m_height > m_length*std::tan(m_alpha)*std::min(1.,1.0/m_height_ratio)) {
        std::ostringstream ostr;
        ostr << "FormFactorCuboctahedron() -> Error in class initialization ";
        ostr << "with parameters m_height:" << m_height;
        ostr << " m_length:" << m_length;
        ostr << " m_height_ratio:" << m_height_ratio;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for '2.*height <= length*std::tan(alpha)*min(1.,1.0/height_ratio)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

void FormFactorCuboctahedron::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("height_ratio", &m_height_ratio);
    registerParameter("length", &m_length);
    registerParameter("alpha", &m_alpha);
}

FormFactorCuboctahedron* FormFactorCuboctahedron::clone() const
{
    FormFactorCuboctahedron *result =
        new FormFactorCuboctahedron(m_length, m_height,
                                    m_height_ratio, m_alpha);
    result->setName(getName());
    return result;
}

complex_t FormFactorCuboctahedron::evaluate_for_q(const cvector_t& q) const
{
    double H = m_height;
    double L = m_length;
    double rh = m_height_ratio;
    //double tga = std::tan(m_alpha);

    complex_t qx = q.x();
    complex_t qy = q.y();
    complex_t qz = q.z();

    FormFactorPyramid fftop(L,rh*H, m_alpha);
    complex_t ffhigh = fftop.evaluate_for_q(q);
    FormFactorPyramid ffbottom(L,H, m_alpha);
    cvector_t downq(qx,qy,-qz);
    complex_t fflow = ffbottom.evaluate_for_q(downq);
    const complex_t im(0,1);

    return std::exp(im*qz*H)*(ffhigh + fflow);
}

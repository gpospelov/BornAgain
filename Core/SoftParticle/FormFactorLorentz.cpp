// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorLorentz.cpp
//! @brief     Implements class FormFactorLorentzSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Shapes/Box.h"
#include "Core/SoftParticle/FormFactorLorentz.h"
#include "Fit/Tools/RealLimits.h"

FormFactorLorentzSphere::FormFactorLorentzSphere(double width, double height)
{
    m_width = width;
    m_height = height;
    initialize();
}

FormFactorLorentzSphere::FormFactorLorentzSphere(double length) : m_width{length}, m_height{length}
{
    initialize();
}

double FormFactorLorentzSphere::radialExtension() const
{
    return m_width / 2.0;
}

complex_t FormFactorLorentzSphere::evaluate_for_q(cvector_t q) const
{
    static const double sigma2 = 4.0 * std::pow(M_PI, 2.0 / 3.0);
    double R = m_width;
    double H = m_height;

    complex_t xnorm = R * R * q.x() * q.x() / sigma2;
    complex_t ynorm = R * R * q.y() * q.y() / sigma2;
    complex_t znorm = H * H * q.z() * q.z() / sigma2;

    complex_t result = H * R * R / (1.0 + xnorm + ynorm + znorm);

    return result;
}

void FormFactorLorentzSphere::onChange()
{
    mP_shape.reset(new Box(m_width, m_width, m_height));
}

void FormFactorLorentzSphere::initialize()
{
    setName("FormFactorLorentzSphere");
    registerParameter("Width", &m_width).setUnit("nm").setNonnegative();
    registerParameter("Height", &m_height).setUnit("nm").setNonnegative();
    onChange();
}

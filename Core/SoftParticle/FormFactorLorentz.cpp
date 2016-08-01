// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorLorentz.cpp
//! @brief     Implements class FormFactorLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLorentz.h"
#include "AttLimits.h"
#include "BornAgainNamespace.h"
#include "Units.h"

using namespace BornAgain;

FormFactorLorentz::FormFactorLorentz(double volume)
{
    double R = std::pow(volume, 1.0/3.0);
    m_height = R;
    m_width = R;
    initialize();
}

FormFactorLorentz::FormFactorLorentz(double width, double height)
{
    m_width = width;
    m_height = height;
    initialize();
}

bool FormFactorLorentz::check_initialization() const
{
    return true;
}

void FormFactorLorentz::init_parameters()
{
    registerParameter(Width, &m_width, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}

FormFactorLorentz* FormFactorLorentz::clone() const
{
    return new FormFactorLorentz(m_width, m_height);
}

void FormFactorLorentz::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

double FormFactorLorentz::getRadialExtension() const
{
    return m_width / 2.0;
}

complex_t FormFactorLorentz::evaluate_for_q(const cvector_t q) const
{
    static const double sigma2 = 4.0*std::pow(Units::PI, 2.0/3.0);
    double R = m_width;
    double H = m_height;

    complex_t xnorm = R*R*q.x()*q.x()/sigma2;
    complex_t ynorm = R*R*q.y()*q.y()/sigma2;
    complex_t znorm = H*H*q.z()*q.z()/sigma2;

    complex_t result = H*R*R/(1.0 + xnorm + ynorm + znorm);

    return result;
}

void FormFactorLorentz::initialize()
{
    setName(FFLorentzType);
    check_initialization();
    init_parameters();
}

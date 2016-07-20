// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticles/FormFactorSphereUniformRadius.cpp
//! @brief     Implements class FormFactorSphereUniformRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorSphereUniformRadius.h"
#include "BornAgainNamespace.h"
#include "Numeric.h"

using namespace  BornAgain;

FormFactorSphereUniformRadius::FormFactorSphereUniformRadius(double mean,
        double full_width)
: m_mean(mean)
, m_full_width(full_width)
{
    if(!checkParameters()) {
        throw Exceptions::ClassInitializationException(
                "FormFactorSphereUniformRadius::FormFactorSphereUniformRadius:"
                " mean radius must be bigger than the half width");
    }
    setName(FormFactorSphereUniformRadiusType);
    check_initialization();
    init_parameters();
}

FormFactorSphereUniformRadius* FormFactorSphereUniformRadius::clone() const
{
    return new FormFactorSphereUniformRadius(m_mean, m_full_width);
}

FormFactorSphereUniformRadius::~FormFactorSphereUniformRadius()
{
}

void FormFactorSphereUniformRadius::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorSphereUniformRadius::evaluate_for_q(const cvector_t q) const
{
    double R = m_mean;
    double W = m_full_width;
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double q_r = std::sqrt(q2);
    if (q_r*R < Numeric::double_epsilon)
        return (4.0*Units::PI*R*R*R + Units::PI*R*W*W)/3.0;
    double qR = q_r*R;
    double qW = q_r*W;
    double nominator = 4*Units::PI*( 4*std::sin(qR)*std::sin(qW/2.0)
                                     - qW*std::cos(qW/2.0)*std::sin(qR)
                                     - 2.0*qR*std::cos(qR)*std::sin(qW/2.0) );
    return nominator/(q2*q2*W);
}

bool FormFactorSphereUniformRadius::check_initialization() const
{
    return true;
}

void FormFactorSphereUniformRadius::init_parameters()
{
    clearParameterPool();
    registerParameter(MeanRadius, &m_mean, AttLimits::n_positive());
    registerParameter(FullWidth, &m_full_width, AttLimits::n_positive());
}

bool FormFactorSphereUniformRadius::checkParameters() const
{
    if (m_full_width<=0.0) return false;
    if (2.0*m_mean<m_full_width) return false;
    return true;
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorSphereUniformRadius.cpp
//! @brief     Implements class FormFactorSphereUniformRadius.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorSphereUniformRadius.h"

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
    setName("FormFactorSphereUniformRadius");
    init_parameters();
}

FormFactorSphereUniformRadius* FormFactorSphereUniformRadius::clone() const
{
    FormFactorSphereUniformRadius *p_result = new FormFactorSphereUniformRadius(
            m_mean, m_full_width);
    p_result->setName(getName());
    return p_result;
}

FormFactorSphereUniformRadius::~FormFactorSphereUniformRadius()
{
}

int FormFactorSphereUniformRadius::getNumberOfStochasticParameters() const
{
    return 2;
}

void FormFactorSphereUniformRadius::createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const
{
    assert(nbr_samples>1);
    double step = m_full_width/(nbr_samples+1.0);
    double radius_start = m_mean - m_full_width/2.0;
    double probability = 1.0/nbr_samples;
    for (size_t i=0; i<nbr_samples; ++i) {
        double radius = radius_start + (double)i*step;
        form_factors.push_back(new FormFactorFullSphere(radius));
        probabilities.push_back(probability);
    }
}

complex_t FormFactorSphereUniformRadius::evaluate_for_q(
        const cvector_t& q) const
{
    double R = m_mean;
    double W = m_full_width;
    double q2 = std::norm(q.x()) + std::norm(q.y()) + std::norm(q.z());
    double q_r = std::sqrt(q2);
    if (q_r*R < Numeric::double_epsilon) {
        return (4.0*M_PI*R*R*R + M_PI*R*W*W)/3.0;
    }
    double qR = q_r*R;
    double qW = q_r*W;
    double nominator = 4*M_PI*( 4*std::sin(qR)*std::sin(qW/2.0)
                             - qW*std::cos(qW/2.0)*std::sin(qR)
                             - 2.0*qR*std::cos(qR)*std::sin(qW/2.0));
    return nominator/(q2*q2*W);
}

void FormFactorSphereUniformRadius::init_parameters()
{
    clearParameterPool();
    registerParameter("mean_radius", &m_mean);
    registerParameter("width_radius", &m_full_width);
}

bool FormFactorSphereUniformRadius::checkParameters() const
{
    if (m_full_width<=0.0) return false;
    if (2.0*m_mean<m_full_width) return false;
    return true;
}

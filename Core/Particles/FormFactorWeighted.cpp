// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particles/FormFactorWeighted.cpp
//! @brief     Implements class FormFactorWeighted.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BornAgainNamespace.h"
#include "FormFactorWeighted.h"


FormFactorWeighted::FormFactorWeighted()
{
    setName(BornAgain::FormFactorWeightedType);
}

FormFactorWeighted::~FormFactorWeighted()
{
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        delete m_form_factors[index];
    }
}

FormFactorWeighted* FormFactorWeighted::clone() const
{
    FormFactorWeighted *result = new FormFactorWeighted();
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        result->addFormFactor(*m_form_factors[index], m_weights[index]);
    }
    return result;
}

void FormFactorWeighted::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorWeighted::getRadius() const
{
    double result { 0.0 };
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        double radius = m_form_factors[index]->getRadius();
        result += m_weights[index]*radius;
    }
    return result;
}

void FormFactorWeighted::addFormFactor(const IFormFactor& form_factor,
                                       double weight)
{
    m_form_factors.push_back(form_factor.clone());
    m_weights.push_back(weight);
}

void FormFactorWeighted::setAmbientMaterial(const IMaterial& material)
{
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        m_form_factors[index]->setAmbientMaterial(material);
    }
}

complex_t FormFactorWeighted::evaluate(const WavevectorInfo& wavevectors) const
{
    complex_t result(0.0, 0.0);
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        complex_t ff_evaluate = m_form_factors[index]->evaluate(wavevectors);
        result += m_weights[index]*ff_evaluate;
    }
    return result;
}

Eigen::Matrix2cd FormFactorWeighted::evaluatePol(const WavevectorInfo& wavevectors) const
{
    Eigen::Matrix2cd result = Eigen::Matrix2cd::Zero();
    for (size_t index=0; index<m_form_factors.size(); ++index) {
        Eigen::Matrix2cd ff_evaluate = m_form_factors[index]->evaluatePol(wavevectors);
        result += m_weights[index]*ff_evaluate;
    }
    return result;
}


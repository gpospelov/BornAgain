// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorDecoratorPositionFactor.h
//! @brief     Declares class FormFactorDecoratorPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORPOSITIONFACTOR_H
#define FORMFACTORDECORATORPOSITIONFACTOR_H

#include "IFormFactorDecorator.h"
#include "BornAgainNamespace.h"

//! @class FormFactorDecoratorPositionFactor
//! @ingroup formfactors_internal
//! @brief Decorates a formfactor with a position dependent phase factor.

class BA_CORE_API_ FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, kvector_t position);
    virtual ~FormFactorDecoratorPositionFactor() {}

    virtual FormFactorDecoratorPositionFactor *clone() const;
    virtual void accept(ISampleVisitor *visitor) const;

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

#ifndef SWIG
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

protected:
    kvector_t m_position;

private:
    complex_t getPositionFactor(const cvector_t q) const;
};

inline FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(
    const IFormFactor &form_factor, kvector_t position)
    : IFormFactorDecorator(form_factor), m_position(position)
{
    setName(BornAgain::FormFactorDecoratorPositionFactorType);
}

inline FormFactorDecoratorPositionFactor *FormFactorDecoratorPositionFactor::clone() const
{
    return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position);
}

inline void FormFactorDecoratorPositionFactor::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

inline complex_t FormFactorDecoratorPositionFactor::evaluate(
        const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    complex_t pos_factor = getPositionFactor(q);
    return pos_factor * mp_form_factor->evaluate(wavevectors);
}

inline Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(
        const WavevectorInfo& wavevectors) const
{
    cvector_t q = wavevectors.getQ();
    complex_t pos_factor = getPositionFactor(q);
    return pos_factor * mp_form_factor->evaluatePol(wavevectors);
}

inline complex_t FormFactorDecoratorPositionFactor::getPositionFactor(const cvector_t q) const
{
    complex_t qr = q.x() * m_position.x() + q.y() * m_position.y() + q.z() * m_position.z();
    return exp_I(qr);
}

#endif // FORMFACTORDECORATORPOSITIONFACTOR_H

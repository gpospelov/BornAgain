// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FFDecorators/FormFactorDecoratorPositionFactor.h
//! @brief     Defines class FormFactorDecoratorPositionFactor.
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
#include "Vectors3D.h"

//! Decorates a formfactor with a position dependent phase factor.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor& form_factor, kvector_t position);
    virtual ~FormFactorDecoratorPositionFactor() {}

    virtual FormFactorDecoratorPositionFactor* clone() const {
        return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position); }
    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

#ifndef SWIG
    virtual Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const;
#endif

protected:
    kvector_t m_position;

private:
    complex_t getPositionFactor(const cvector_t q) const;
};

#endif // FORMFACTORDECORATORPOSITIONFACTOR_H

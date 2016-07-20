// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorPositionFactor.h
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

#include "IFormFactorDecorator.h" // inheriting from
#include "Vectors3D.h"

//! @class FormFactorDecoratorPositionFactor
//! @ingroup formfactors_internal
//! @brief Decorates a formfactor with a position dependent phase factor.

class BA_CORE_API_ FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor& form_factor, kvector_t position);
    virtual ~FormFactorDecoratorPositionFactor() {}

    virtual FormFactorDecoratorPositionFactor* clone() const;
    virtual void accept(ISampleVisitor* visitor) const;

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

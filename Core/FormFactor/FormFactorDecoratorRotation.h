// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorRotation.h
//! @brief     Defines class FormFactorDecoratorRotation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORROTATION_H
#define FORMFACTORDECORATORROTATION_H

#include "IFormFactorDecorator.h"
#include "Rotations.h"

//! @class FormFactorDecoratorRotation
//! @ingroup formfactors_internal
//! @brief Equips a formfactor with a rotation.

class BA_CORE_API_ FormFactorDecoratorRotation : public IFormFactorDecorator
{
public:
    //! Constructor, setting form factor and rotation.
    FormFactorDecoratorRotation(const IFormFactor &form_factor, const IRotation &transform);

    virtual FormFactorDecoratorRotation *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

protected:
    Geometry::Transform3D m_transform;
};

#endif // FORMFACTORDECORATORROTATION_H

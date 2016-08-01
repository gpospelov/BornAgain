// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTrivial.h
//! @brief     Declares class FormFactorTrivial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTRIVIAL_H
#define FORMFACTORTRIVIAL_H

#include "IFormFactorBorn.h" // inheriting from

//! @class FormFactorTrivial
//! @ingroup formfactors
//! @brief A uniform formfactor F(q)=1, for development purposes.

class BA_CORE_API_ FormFactorTrivial : public IFormFactorBorn
{
public:
    FormFactorTrivial();

    FormFactorTrivial* clone() const;

    virtual void accept(ISampleVisitor* visitor) const final;

    virtual double getRadialExtension() const final;

    virtual complex_t evaluate_for_q(const cvector_t q) const final;
};

#endif // FORMFACTORTRIVIAL_H

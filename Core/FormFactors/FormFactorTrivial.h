// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorTrivial.h
//! @brief     Defines class FormFactorTrivial.
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

#include "IFormFactorBorn.h"

//! @class FormFactorCylinder
//! @ingroup formfactors
//! @brief The formfactor of a cylinder.

class BA_CORE_API_ FormFactorTrivial : public IFormFactorBorn
{
public:
    //! @brief Cylinder constructor
    //! @param radius of Cylinder's base
    //! @param height of Cylinder
    FormFactorTrivial();

    virtual FormFactorTrivial *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double getRadius() const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual bool check_initialization() const;
    virtual void init_parameters();
};

#endif // FORMFACTORTRIVIAL_H



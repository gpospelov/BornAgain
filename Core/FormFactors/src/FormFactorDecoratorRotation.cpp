// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDecoratorRotation.cpp
//! @brief     Implements class FormFactorDecoratorRotation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorRotation.h"

#include <boost/scoped_ptr.hpp>

FormFactorDecoratorRotation *FormFactorDecoratorRotation::clone() const
{
    boost::scoped_ptr<IRotation> P_rotation(IRotation::createRotation(m_transform));
    FormFactorDecoratorRotation *result =  new FormFactorDecoratorRotation(
                mp_form_factor->clone(), *P_rotation);

    result->setName(getName());
    return result;
}


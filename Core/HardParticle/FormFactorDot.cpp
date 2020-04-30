// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDot.cpp
//! @brief     Implements class FormFactorDot.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorDot.h"
#include "BornAgainNamespace.h"
#include "Dot.h"
#include "RealParameter.h"

FormFactorDot::FormFactorDot()
{
    setName(BornAgain::FFDotType);
    onChange();
}

IFormFactor* FormFactorDot::sliceFormFactor(ZLimits, const IRotation&, kvector_t) const
{
    throw std::runtime_error(getName()
                             + "::sliceFormFactor error: "
                               "this shape should never be sliced!");
}

void FormFactorDot::onChange()
{
    mP_shape.reset(new Dot());
}

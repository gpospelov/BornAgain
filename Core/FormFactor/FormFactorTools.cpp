// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorTools.cpp
//! @brief     Implements global functions that facilitate IFormFactor handling.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "FormFactorTools.h"

IFormFactor *FormFactorTools::createDWBAScalarFormFactor(const IFormFactor &form_factor)
{
    FormFactorDWBA *p_result = new FormFactorDWBA(form_factor);
    return p_result;
}

IFormFactor *FormFactorTools::createDWBAMatrixFormFactor(const IFormFactor &form_factor)
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(form_factor);
    return p_result;
}

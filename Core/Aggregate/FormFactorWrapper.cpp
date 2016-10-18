// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorWrapper.cpp
//! @brief     Implements class FormFactorWrapper.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorWrapper.h"
#include "IFormFactor.h"

FormFactorWrapper::~FormFactorWrapper() { delete mp_ff; }

FormFactorWrapper* FormFactorWrapper::clone() const
{
    return new FormFactorWrapper(mp_ff->clone(), m_abundance);
}

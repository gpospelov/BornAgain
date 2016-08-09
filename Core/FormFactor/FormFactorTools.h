// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorTools.h
//! @brief     Defines global functions that facilitate IFormFactor handling.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTOOLS_H
#define FORMFACTORTOOLS_H

#include "IFormFactor.h"


namespace FormFactorTools {

//! Decorates the given formfactor with a scalar dwba formfactor and returns
//! this form factor
IFormFactor* createDWBAScalarFormFactor(const IFormFactor &form_factor);

//! Decorates the given formfactor with a matrix dwba formfactor and returns
//! this form factor
IFormFactor* createDWBAMatrixFormFactor(const IFormFactor &form_factor);
}


#endif // FORMFACTORTOOLS_H

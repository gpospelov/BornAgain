// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorTools.h
//! @brief     Defines global functions that facilitate IFormFactor handling.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTOOLS_H_
#define FORMFACTORTOOLS_H_

#include "IFormFactor.h"

class LayerSpecularInfo;

namespace FormFactorTools {

//! Decorates the given formfactor with a scalar dwba formfactor and returns
//! this form factor
IFormFactor* createDWBAScalarFormFactor(IFormFactor* p_form_factor,
        const LayerSpecularInfo &specular_info, double depth=0.0);

//! Decorates the given formfactor with a matrix dwba formfactor and returns
//! this form factor
IFormFactor* createDWBAMatrixFormFactor(IFormFactor* p_form_factor,
        const LayerSpecularInfo &specular_info, double depth=0.0);
}


#endif /* FORMFACTORTOOLS_H_ */

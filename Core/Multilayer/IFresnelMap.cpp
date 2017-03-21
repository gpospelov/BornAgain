// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IFresnelMap.cpp
//! @brief     Implements class IFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFresnelMap.h"
#include "MultiLayer.h"

IFresnelMap::IFresnelMap() {}
IFresnelMap::~IFresnelMap() {}

void IFresnelMap::setMultilayer(const MultiLayer& multilayer)
{
    mP_multilayer.reset(multilayer.clone());
}

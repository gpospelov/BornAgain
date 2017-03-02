// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h
//! @brief     Defines RealSpaceBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACEBUILDER_H
#define REALSPACEBUILDER_H

#include "WinDllMacros.h"

class SessionItem;
class RealSpaceModel;

namespace RealSpaceBuilder
{

BA_CORE_API_ void populate(RealSpaceModel* model, const SessionItem& item);

}

#endif // REALSPACEBUILDER_H

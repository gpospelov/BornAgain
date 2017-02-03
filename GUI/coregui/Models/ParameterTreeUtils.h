// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeUtils.h
//! @brief     Defines ParameterTreeUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERTREEUTILS_H
#define PARAMETERTREEUTILS_H

#include "WinDllMacros.h"
#include <functional>
#include <QString>

class JobItem;
class SessionItem;
class ParameterItem;

//! The ParameterTreeBuilder namespace contains helper functions to create container
//! with ParameterItems. The ParameterItem appears in RealTimeView and provides real
//! time tuning of MultiLayerItem and InstrumentItem.

namespace ParameterTreeUtils
{

BA_CORE_API_ void createParameterTree(JobItem* jobItem);

BA_CORE_API_ void populateParameterContainer(SessionItem* container, const SessionItem* source);

BA_CORE_API_ void visitParameterContainer(SessionItem* container,
                                          std::function<void(ParameterItem*)> fun);

BA_CORE_API_ QStringList parameterTreeNames(const SessionItem* source);

BA_CORE_API_ QStringList translatedParameterTreeNames(const SessionItem* source);

BA_CORE_API_ void populateDomainLinks(SessionItem* container);

}

#endif // PARAMETERTREEUTILS_H

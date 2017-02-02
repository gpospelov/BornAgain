// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeBuilder.h
//! @brief     Defines ParameterTreeBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERTREEBUILDER_H
#define PARAMETERTREEBUILDER_H

#include "WinDllMacros.h"
#include <QString>

class JobItem;
class SessionItem;

//! The ParameterTreeBuilder namespace contains helper functions to create container
//! with ParameterItems. The ParameterItem appears in RealTimeView and provides real
//! time tuning of MultiLayerItem and InstrumentItem.

namespace ParameterTreeBuilder
{

BA_CORE_API_ void createParameterTree(JobItem* item, const QString& tag = QString());
BA_CORE_API_ void populateDomainLinks(JobItem* jobItem, const QString& tag);

}

#endif // PARAMETERTREEBUILDER_H

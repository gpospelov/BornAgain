// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeBuilder.h
//! @brief     Defines class ParameterTreeBuilder
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

#include <QString>
#include "WinDllMacros.h"

class JobItem;
class SessionItem;

//! The ParameterTreeBuilder class helps JobModel to create a container with ParameterItem's.
//! The ParameterItem appears in RealTimeView and provides real time tuning of MultiLayerItem
//! and InstrumentItem.

class BA_CORE_API_ ParameterTreeBuilder
{
public:
    static void createParameterTree(JobItem *item, const QString &tag = QString());
    static void populateDomainLinks(JobItem *jobItem,  const QString &tag);
private:
    static void handleItem(SessionItem *tree, SessionItem *source);
};

#endif // PARAMETERTREEBUILDER_H

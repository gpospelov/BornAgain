// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemUtils.cpp
//! @brief     Implements namespace SessionItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke, Dmitry Yurov
//
// ************************************************************************** //

#include "SessionItemUtils.h"
#include "SessionItem.h"
#include "VectorItem.h"

kvector_t SessionItemUtils::GetVectorItem(const SessionItem& item, const QString& name)
{
    SessionItem* vectorItem = item.getItem(name);
    Q_ASSERT(vectorItem);
    double x = vectorItem->getItemValue(VectorItem::P_X).toDouble();
    double y = vectorItem->getItemValue(VectorItem::P_Y).toDouble();
    double z = vectorItem->getItemValue(VectorItem::P_Z).toDouble();
    return { x, y, z };
}

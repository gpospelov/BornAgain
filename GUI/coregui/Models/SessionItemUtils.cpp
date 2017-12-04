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
#include "MaterialItem.h"
#include "ObsoleteColorProperty.h"
#include "ExternalProperty.h"
#include <QColor>
#include <QIcon>
#include <QPixmap>

int SessionItemUtils::ParentRow(const SessionItem& item)
{
    if (item.parent())
        return item.parent()->rowOfChild(const_cast<SessionItem*>(&item));
    return -1;
}

kvector_t SessionItemUtils::GetVectorItem(const SessionItem& item, const QString& name)
{
    SessionItem* vectorItem = item.getItem(name);
    Q_ASSERT(vectorItem);
    double x = vectorItem->getItemValue(VectorItem::P_X).toDouble();
    double y = vectorItem->getItemValue(VectorItem::P_Y).toDouble();
    double z = vectorItem->getItemValue(VectorItem::P_Z).toDouble();
    return { x, y, z };
}

void SessionItemUtils::SetVectorItem(const SessionItem& item, const QString& name, kvector_t value)
{
    auto p_vector_item = item.getItem(name);
    p_vector_item->setItemValue(VectorItem::P_X, value.x());
    p_vector_item->setItemValue(VectorItem::P_Y, value.y());
    p_vector_item->setItemValue(VectorItem::P_Z, value.z());
}

int SessionItemUtils::ParentVisibleRow(const SessionItem& item)
{
    int result(-1);

    if (!item.parent() || !item.isVisible())
        return result;

    for(auto child : item.parent()->children()) {
        if (child->isVisible())
            ++result;

        if (&item == child)
            return result;
    }

    return result;
}

QVariant SessionItemUtils::TextColorRole(const SessionItem& item)
{
    return item.isEnabled() ? QVariant() : QColor(Qt::gray);
}

QVariant SessionItemUtils::ToolTipRole(const SessionItem& item, int ncol)
{
    QString result = item.toolTip();
    if (result.isEmpty()) {
        result = item.displayName();
        if (ncol == 1 && item.value().canConvert<QString>())
            result = item.value().toString();
    }

    return QVariant(result);
}


QVariant SessionItemUtils::DecorationRole(const SessionItem& item)
{
    if (item.value().canConvert<ExternalProperty>())
        return QIcon(item.value().value<ExternalProperty>().pixmap());

    if (item.value().canConvert<ObsoleteColorProperty>())
        return QIcon(item.value().value<ObsoleteColorProperty>().getPixmap());

    return QVariant();
}

QVariant SessionItemUtils::CheckStateRole(const SessionItem& item)
{
    if (item.value().type() == QVariant::Bool)
        return item.value().toBool() ? Qt::Checked : Qt::Unchecked;
    return QVariant();
}

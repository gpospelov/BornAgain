// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentBoxEditor.cpp
//! @brief     Implements class ComponentBoxEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#include "ComponentBoxEditor.h"
#include "ComponentEditorPrivate.h"
#include "SessionModel.h"
#include "CustomEventFilters.h"
#include <QModelIndex>
#include <QDebug>


ComponentBoxEditor::ComponentBoxEditor(QWidget *parent)
    : ComponentEditor(ComponentEditorFlags::BROWSER_GROUPBOX, parent)
{

}

////! adds all property items to thr PropertyGroup with given name
void ComponentBoxEditor::addPropertyItems(SessionItem *item, const QString &group_name)
{
    Q_ASSERT(item);
    QtVariantProperty *groupProperty = m_d->processPropertyGroupForName(group_name);
    updatePropertyItems(item, groupProperty);
}

void ComponentBoxEditor::updatePropertyItems(SessionItem *item, QtVariantProperty *parentProperty)
{
    if(item->modelType() == Constants::PropertyType ||
            item->modelType() == Constants::GroupItemType) {
        updateItem(item, parentProperty);
    }

    if(m_d->m_item_to_insert_mode.contains(item)) {
        if(m_d->m_item_to_insert_mode[item] == ComponentEditorFlags::SINGLE) return;
    }
    foreach (SessionItem *childItem, componentItems(item)) {
        updateItem(childItem, parentProperty);
    }

}

//! add single item to property group with given name
void ComponentBoxEditor::addItem(SessionItem *item, const QString &group_name)
{
    Q_ASSERT(item);
    QtVariantProperty *groupProperty = m_d->processPropertyGroupForName(group_name);
    updateItem(item, groupProperty);
    m_d->m_item_to_insert_mode[item] = ComponentEditorFlags::SINGLE;
}

void ComponentBoxEditor::updateItem(SessionItem *item, QtVariantProperty *parentProperty)
{
    connectModel(item->model());
    m_d->processPropertyForItem(item, parentProperty);

}

void ComponentBoxEditor::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(bottomRight);
//    if (topLeft != bottomRight)
//        return;

    SessionModel *model = qobject_cast<SessionModel *>(sender());
    Q_ASSERT(model);
    SessionItem *item = model->itemForIndex(topLeft);
    Q_ASSERT(item);

    qDebug() << " ComponentEditor::onDataChanged" << m_d->m_presentationType
             << roles << item->modelType() << item->displayName();

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        // updating editor's property appearance (tooltips, limits)
        if (roles.contains(Qt::UserRole)) {
            m_d->updatePropertyAppearance(property, PropertyAttribute::fromItem(item));
        }

        // updating editor's property values
        if (roles.contains(Qt::DisplayRole) || roles.contains(Qt::EditRole)) {
            disconnectManager();
            property->setValue(item->value());
            connectManager();

            if(item->modelType() == Constants::GroupItemType) {
                m_d->cleanChildren(item);
                updatePropertyItems(item, m_d->m_item_to_qtparent[item]);
//                updateEditor(item, m_d->getPropertyForItem(item->parent()));
            }

        }
    }

}

void ComponentBoxEditor::onRowsInserted(const QModelIndex &, int , int )
{
    // intentionally empty
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentBoxEditor.cpp
//! @brief     Implements class ComponentBoxEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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

void ComponentBoxEditor::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    qDebug() << "ComponentBoxEditor::onRowsInserted";

}




//ComponentBoxEditor::ComponentBoxEditor(ComponentEditorFlags::PresentationType flags, QWidget *parent)
//    : QWidget(parent), m_d(new ComponentEditorPrivate(flags, this))
//{
//    setWindowTitle(QLatin1String("Property Editor"));
//    setObjectName(QLatin1String("ComponentEditor"));

//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->setMargin(0);
//    layout->addWidget(m_d->m_browser);

//    connectManager();
//}

//ComponentBoxEditor::~ComponentBoxEditor()
//{
//}

////! Sets editor to display all recursive properties of given item
//void ComponentBoxEditor::setItem(SessionItem *item, const QString &group_name)
//{
//    clearEditor();
//    if(!item) return;

////    updateEditor(item);

//    QtVariantProperty *groupVariantProperty(0);
//    if(!group_name.isEmpty()) {
//        groupVariantProperty = m_d->m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), group_name);
//        m_d->m_browser->addProperty(groupVariantProperty);
//    }

////    if(m_d->isFlat()) {
//        foreach (SessionItem *childItem, componentItems(item)) {
//            updateEditor(childItem, groupVariantProperty);
//        }
////    } else {
////        updateEditor(item);
////    }

//}


////! adds all property items to thr PropertyGroup with given name
//void ComponentBoxEditor::addPropertyItems(SessionItem *item, const QString &group_name)
//{
//    if(item->modelType() == Constants::PropertyType) {
//        addItem(item, group_name);
//    }

//    else if(item->modelType() == Constants::GroupItemType) {
//        addItem(item, group_name);
//        foreach (SessionItem *childItem, componentItems(item)) {
//            addItem(childItem, group_name);
//        }
//    }

//    else {
//        foreach (SessionItem *childItem, componentItems(item)) {
//            addItem(childItem, group_name);
//        }
//    }
//}

////! add single item to property group with given name
//void ComponentBoxEditor::addItem(SessionItem *item, const QString &group_name)
//{
//    QtVariantProperty *groupProperty = m_d->processPropertyGroupForName(group_name);
//    m_d->processPropertyForItem(item, groupProperty);
//}

////void ComponentEditor::addItemProperty(SessionItem *item, const QString &name)
////{

////}

////! Main function to run through SessionItem tree and fill editor with
////! properties
//void ComponentBoxEditor::updateEditor(SessionItem *item,
//                                   QtVariantProperty *parentProperty)
//{
//    connectModel(item->model());

////    if(parentProperty)

//    if (QtVariantProperty *childProperty
//        = m_d->processPropertyForItem(item, parentProperty)) {
//        parentProperty = childProperty;
//    }

//    foreach (SessionItem *childItem, componentItems(item)) {
//        updateEditor(childItem, parentProperty);
//    }
//}

////! Clear editor from all properties, ready to accept new items
//void ComponentBoxEditor::clearEditor()
//{
//    disconnect();
//    disconnectManager();
//    m_d->clear();
//    connectManager();
//}

////! Propagates data from SessionItem to editor
//void ComponentBoxEditor::onDataChanged(const QModelIndex &topLeft,
//                                    const QModelIndex &bottomRight,
//                                    const QVector<int> &roles)
//{
//    if (topLeft != bottomRight)
//        return;

//    SessionModel *model = qobject_cast<SessionModel *>(sender());
//    Q_ASSERT(model);
//    SessionItem *item = model->itemForIndex(topLeft);
//    Q_ASSERT(item);

//    qDebug() << " ComponentEditor::onDataChanged" << m_d->m_presentationType
//             << roles << item->modelType() << item->displayName();

//    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
//        // updating editor's property appearance (tooltips, limits)
//        if (roles.contains(Qt::UserRole)) {
//            m_d->updatePropertyAppearance(property, item->getAttribute());
//        }

//        // updating editor's property values
//        if (roles.contains(Qt::DisplayRole) || roles.contains(Qt::EditRole)) {
//            disconnectManager();
//            property->setValue(item->value());
//            connectManager();

//            if(item->modelType() == Constants::GroupItemType) {
//                cleanChildren(item);
//                //updateEditor(item, m_d->getPropertyForItem(item->parent()));
//            }

//        }
//    }
//}

////! Updates the editor starting from given SessionItem's parent.
////! Editor should know already about given item (i.e. corresponding
////! QtVariantProperty should exist.
//void ComponentBoxEditor::onRowsInserted(const QModelIndex &parent, int first,
//                                     int last)
//{
//    qDebug() << "ComponentEditor::onRowsInserted" << parent << first << last;
//    SessionModel *model = qobject_cast<SessionModel *>(sender());

//    SessionItem *item = model->itemForIndex(parent);
//    Q_ASSERT(item);

//    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
//        updateEditor(item, property);
//    }
//}

////! Propagates value from the editor to SessionItem
//void ComponentBoxEditor::onQtPropertyChanged(QtProperty *property,
//                                          const QVariant &value)
//{
//    qDebug() << "ComponentEditor::onQtPropertyChanged" << property << value;
//    if (SessionItem *item = m_d->getItemForProperty(property)) {
//        disconnectModel(item->model());
//        item->setValue(value);
//        connectModel(item->model());
//    }
//}

////! Returns list of children suitable for displaying in ComponentEditor.
////! In condensed mode, editor will analyse only nearest visible properties.
//QList<SessionItem *>
//ComponentBoxEditor::componentItems(SessionItem *item) const
//{
//    QList<SessionItem *> result;


//        foreach (SessionItem *child, item->childItems()) {
//            if (child->getAttribute().isHidden())
//                continue;
//            if (child->modelType() == Constants::PropertyType) {
//                result.append(child);
//            }
//            if (child->modelType() == Constants::GroupItemType) {
//                result.append(child);
//            }
//            if (item->modelType() == Constants::GroupItemType) {
//                foreach(SessionItem *childOfChild, child->childItems()) {
//                    result.append(childOfChild);
//                }
//            }
//        }

//    return result;
//}

//void ComponentBoxEditor::cleanChildren(SessionItem *item)
//{
//    foreach(SessionItem *child, item->childItems()) {
//        if (QtVariantProperty *property = m_d->getPropertyForItem(child)) {
//            m_d->removeQtVariantProperty(property);
//        }
//        cleanChildren(child);
//    }
//}

//void ComponentBoxEditor::disconnectModel(SessionModel *model)
//{
//    disconnect(
//        model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &,
//                                  const QVector<int> &)),
//        this, SLOT(onDataChanged(const QModelIndex &, const QModelIndex &,
//                                 const QVector<int> &)));

//    disconnect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this,
//               SLOT(onRowsInserted(const QModelIndex &, int, int)));
//}

//void ComponentBoxEditor::connectModel(SessionModel *model)
//{
//    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &,
//                                      const QVector<int> &)),
//            this, SLOT(onDataChanged(const QModelIndex &, const QModelIndex &,
//                                     const QVector<int> &)),
//            Qt::UniqueConnection);

//    connect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this,
//            SLOT(onRowsInserted(const QModelIndex &, int, int)),
//            Qt::UniqueConnection);
//}

//void ComponentBoxEditor::disconnectManager()
//{
//    disconnect(m_d->m_manager,
//               SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
//               SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)));
//}

//void ComponentBoxEditor::connectManager()
//{
//    connect(m_d->m_manager,
//            SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
//            SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)),
//            Qt::UniqueConnection);
//}


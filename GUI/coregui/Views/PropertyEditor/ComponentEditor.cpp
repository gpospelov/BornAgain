// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "ComponentEditor.h"
#include "ComponentEditorPrivate.h"
#include "qtpropertybrowser.h"
#include "PropertyVariantManager.h"
#include "GUIHelpers.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "GroupItem.h"
#include "GroupProperty.h"

#include <QVBoxLayout>
#include <QVariant>
#include <QDebug>

ComponentEditor::ComponentEditor(QWidget *parent)
    : QWidget(parent), m_d(new ComponentEditorPrivate(this))
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("ComponentEditor"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_d->m_browser);

    connectManager();
}

ComponentEditor::~ComponentEditor()
{
}

//! Sets editor to display all recursive properties of given item
void ComponentEditor::setItem(ParameterizedItem *item)
{
    clearEditor();
    if (item)
        updateEditor(item);
}

//void ComponentEditor::addItemProperty(ParameterizedItem *item, const QString &name)
//{

//}

//! Main function to run through ParameterizedItem tree and fill editor with
//! properties
void ComponentEditor::updateEditor(ParameterizedItem *item,
                                   QtVariantProperty *parentProperty)
{
    connectModel(item->model());

    if (QtVariantProperty *childProperty
        = m_d->processPropertyForItem(item, parentProperty)) {
        parentProperty = childProperty;
    }
    foreach (ParameterizedItem *childItem, componentItems(item)) {
        updateEditor(childItem, parentProperty);
    }
}

//! Clear editor from all properties, ready to accept new items
void ComponentEditor::clearEditor()
{
    disconnect();
    disconnectManager();
    m_d->clear();
    connectManager();
}

//! Sets presentation type (full/condensed editor, table/groupbox like)
void ComponentEditor::setPresentationType(
    ComponentEditorFlags::PresentationType presentationType)
{
    m_d->setPresentationType(presentationType);
    layout()->addWidget(m_d->m_browser);
}

//! Propagates data from ParameterizedItem to editor
void ComponentEditor::onDataChanged(const QModelIndex &topLeft,
                                    const QModelIndex &bottomRight,
                                    const QVector<int> &roles)
{
    qDebug() << " ComponentEditor::onDataChanged" << m_d->m_presentationType
             << topLeft << roles;

    if (topLeft != bottomRight)
        return;

    SessionModel *model = qobject_cast<SessionModel *>(sender());
    Q_ASSERT(model);
    ParameterizedItem *item = model->itemForIndex(topLeft);
    Q_ASSERT(item);

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        // updating editor's property appearance (tooltips, limits)
        if (roles.contains(Qt::UserRole)) {
            m_d->updatePropertyAppearance(property, item->getAttribute());
        }

        // updating editor's property values
        if (roles.contains(Qt::DisplayRole) || roles.contains(Qt::EditRole)) {
            disconnectManager();
            property->setValue(item->value());
            connectManager();

//            if(item->modelType() == Constants::GroupItemType) {
//                foreach(QtVariantProperty *qtProperty, m_d->m_qtvariant_to_dependend[property]) {
//                    qDebug() << "AAAA" << qtProperty << m_d->getItemForProperty(qtProperty);
//                    m_d->removeQtVariantProperty(qtProperty);
//                }
////                m_d->m_qtvariant_to_dependend[property].clear();

////                updateEditor(topLeft, m_d->getPropertyForItem(item->parent()));
////                return;
//            }

            if(item->modelType() == Constants::GroupItemType) {
                cleanChildren(item);
                updateEditor(item, m_d->getPropertyForItem(item->parent()));
            }


        }
    }

    // Special case for condensed editor and GroupItem.
    // If child of GroupItem is marked as hidden we should remove it from the
    // editor,
    // if item is marked as visible but doesn't exist yet, we have to recreate
    // corresponding property
//    if (m_d->isShowCondensed() && roles.contains(Qt::UserRole)) {

//        if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
//            if (item->getAttribute().isHidden()) {
//                m_d->removeQtVariantProperty(property);
//            }
//        } else {
//            ParameterizedItem *parentItem = item->parent();
//            if (QtVariantProperty *parentProperty
//                = m_d->getPropertyForItem(parentItem)) {
//                updateEditor(item, parentProperty);
//            }
//        }
//    }
}

//! Updates the editor starting from given ParameterizedItem's parent.
//! Editor should know already about given item (i.e. corresponding
//! QtVariantProperty should exist.
void ComponentEditor::onRowsInserted(const QModelIndex &parent, int first,
                                     int last)
{
    qDebug() << "ComponentEditor::onRowsInserted" << parent << first << last;
    SessionModel *model = qobject_cast<SessionModel *>(sender());

    ParameterizedItem *item = model->itemForIndex(parent);
    Q_ASSERT(item);

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        updateEditor(item, property);
    }
}

//! Propagates value from the editor to ParameterizedItem
void ComponentEditor::onQtPropertyChanged(QtProperty *property,
                                          const QVariant &value)
{
    qDebug() << "ComponentEditor::onQtPropertyChanged" << property << value;
    if (ParameterizedItem *item = m_d->getItemForProperty(property)) {
        disconnectModel(item->model());
        item->setValue(value);
        connectModel(item->model());
    }
}

//! Returns list of children suitable for displaying in ComponentEditor.
//! In condensed mode, editor will analyse only nearest visible properties.
QList<ParameterizedItem *>
ComponentEditor::componentItems(ParameterizedItem *item) const
{
    QList<ParameterizedItem *> result;

    if (m_d->isShowDetailed()) {
        result = item->childItems();
    }

    else if (m_d->isShowCondensed()) {

        foreach (ParameterizedItem *child, item->childItems()) {
            if (child->getAttribute().isHidden())
                continue;
            if (child->modelType() == Constants::PropertyType) {
                result.append(child);
            }
            if (child->modelType() == Constants::GroupItemType) {
                result.append(child);
            }
            if (item->modelType() == Constants::GroupItemType) {
//                result.append(child);
                foreach(ParameterizedItem *childOfChild, child->childItems()) {
                    result.append(childOfChild);
                }
            }
        }
    }

    return result;
}

void ComponentEditor::cleanChildren(ParameterizedItem *item)
{
    foreach(ParameterizedItem *child, item->childItems()) {
        if (QtVariantProperty *property = m_d->getPropertyForItem(child)) {
            m_d->removeQtVariantProperty(property);
        }
        cleanChildren(child);
    }
}

void ComponentEditor::disconnectModel(SessionModel *model)
{
    disconnect(
        model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &,
                                  const QVector<int> &)),
        this, SLOT(onDataChanged(const QModelIndex &, const QModelIndex &,
                                 const QVector<int> &)));

    disconnect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this,
               SLOT(onRowsInserted(const QModelIndex &, int, int)));
}

void ComponentEditor::connectModel(SessionModel *model)
{
    connect(model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &,
                                      const QVector<int> &)),
            this, SLOT(onDataChanged(const QModelIndex &, const QModelIndex &,
                                     const QVector<int> &)),
            Qt::UniqueConnection);

    connect(model, SIGNAL(rowsInserted(const QModelIndex &, int, int)), this,
            SLOT(onRowsInserted(const QModelIndex &, int, int)),
            Qt::UniqueConnection);
}

void ComponentEditor::disconnectManager()
{
    disconnect(m_d->m_manager,
               SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
               SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)));
}

void ComponentEditor::connectManager()
{
    connect(m_d->m_manager,
            SIGNAL(valueChanged(QtProperty *, const QVariant &)), this,
            SLOT(onQtPropertyChanged(QtProperty *, const QVariant &)),
            Qt::UniqueConnection);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //
#include "ComponentEditor.h"
#include "ComponentEditorPrivate.h"
#include "GUIHelpers.h"
#include "GroupItem.h"
#include "GroupProperty.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "qtpropertybrowser.h"
#include <QVBoxLayout>
#include <QVariant>
#include <QTreeView>

ComponentEditor::ComponentEditor(ComponentEditorFlags::PresentationType flags, QWidget *parent)
    : QWidget(parent)
    , m_d(new ComponentEditorPrivate(flags, this))
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("ComponentEditor"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_d->m_browser);
//    layout->addStretch();

    connectManager();
}

ComponentEditor::~ComponentEditor()
{
}

//! Sets editor to display all recursive properties of given item
void ComponentEditor::setItem(SessionItem *item, const QString &group_name)
{
    if(item == m_d->m_topItem)
        return;

    clearEditor();

    m_d->m_topItem = item;
    if(!item)
        return;

    connectModel(item->model());

    QtVariantProperty *groupVariantProperty = m_d->processPropertyGroupForName(group_name);

    foreach (SessionItem *childItem, componentItems(item)) {
        updateEditor(childItem, groupVariantProperty);
    }
}


//! Main function to run through SessionItem tree and fill editor with
//! properties
void ComponentEditor::updateEditor(SessionItem *item,
                                   QtVariantProperty *parentProperty)
{
    if (QtVariantProperty *childProperty
        = m_d->processPropertyForItem(item, parentProperty)) {
        parentProperty = childProperty;
    }

    foreach (SessionItem *childItem, componentItems(item)) {
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

void ComponentEditor::setHeaderHidden(bool hide)
{
    const QObjectList list = m_d->m_browser->children();
    foreach(QObject *obj, list) {
        QTreeView *view = dynamic_cast<QTreeView *>(obj);
        if(view)
            view->setHeaderHidden(hide);
    }

}

//! Propagates data from SessionItem to editor
void ComponentEditor::onDataChanged(const QModelIndex &topLeft,
                                    const QModelIndex &bottomRight,
                                    const QVector<int> &roles)
{
//    if (topLeft != bottomRight)
//        return;
    Q_UNUSED(bottomRight);

    SessionModel *model = qobject_cast<SessionModel *>(sender());
    Q_ASSERT(model);
    SessionItem *item = model->itemForIndex(topLeft);
    Q_ASSERT(item);

    if(m_d->m_changedItems.contains(item)) return;

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        // updating editor's property appearance (tooltips, limits)
        if (roles.contains(SessionModel::FlagRole)) {
            m_d->updatePropertyAppearance(property, PropertyAttribute::fromItem(item));
        }

        // updating editor's property values
        if (roles.contains(Qt::DisplayRole) || roles.contains(Qt::EditRole)) {
            disconnectManager();
            property->setValue(item->value());
            connectManager();

            if(item->modelType() == Constants::GroupItemType) {
                m_d->cleanChildren(item);
                updateEditor(item, m_d->getPropertyForItem(item->parent()));
            }

        }
    }
}

//! Updates the editor starting from given SessionItem's parent.
//! Editor should know already about given item (i.e. corresponding
//! QtVariantProperty should exist.
void ComponentEditor::onRowsInserted(const QModelIndex &parent, int,
                                     int )
{
    SessionModel *model = qobject_cast<SessionModel *>(sender());

    SessionItem *item = model->itemForIndex(parent);
    Q_ASSERT(item);
    if(m_d->m_changedItems.contains(item)) return;

    if (QtVariantProperty *property = m_d->getPropertyForItem(item)) {
        updateEditor(item, property);
    }
}

//! Propagates value from the editor to SessionItem
void ComponentEditor::onQtPropertyChanged(QtProperty *property,
                                          const QVariant &value)
{
    if (SessionItem *item = m_d->getItemForProperty(property)) {
        Q_ASSERT(item);
//        disconnectModel(item->model());
        m_d->m_changedItems.append(item);
        item->setValue(value);
//        connectModel(item->model());
        m_d->m_changedItems.removeAll(item);
    }
}

//! Returns list of children suitable for displaying in ComponentEditor.
QList<SessionItem *>
ComponentEditor::componentItems(SessionItem *item) const
{
    QList<SessionItem *> result;
    foreach (SessionItem *child, item->childItems()) {
        if (!child->isVisible())
            continue;

        if (child->modelType() == Constants::PropertyType) {
            result.append(child);
        }

        else if (child->modelType() == Constants::GroupItemType) {
            result.append(child);
        }

        else if (child->modelType() == Constants::VectorType) {
            result.append(child);
        }

        else if (child->modelType() == Constants::RefractiveIndexType) {
            result.append(child);
        }

        else if (child->modelType() == Constants::BasicAxisType ||
                 child->modelType() == Constants::AmplitudeAxisType) {
            result.append(child);
        }

        if (item->modelType() == Constants::GroupItemType) {
            foreach (SessionItem *childOfChild, child->childItems()) {
                if (childOfChild->isVisible())
                    result.append(childOfChild);
            }
        }

    }

    return result;
}


void ComponentEditor::disconnectModel(SessionModel *model)
{
    if(!model) return;

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
    if(!model) return;

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

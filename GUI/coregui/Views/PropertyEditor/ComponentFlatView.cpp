// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentFlatView.cpp
//! @brief     Implements class ComponentFlatView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentFlatView.h"
#include "ComponentUtils.h"
#include "PropertyEditorFactory.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "LayoutUtils.h"
#include "PropertyWidgetItem.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDataWidgetMapper>

ComponentFlatView::ComponentFlatView(QWidget* parent)
    : ComponentView(parent)
    , m_mainLayout(new QVBoxLayout)
    , m_gridLayout(nullptr)
    , m_currentItem(nullptr)
    , m_model(nullptr)
    , m_show_children(true)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_mainLayout->setMargin(10);
    m_mainLayout->setSpacing(0);

    initGridLayout();

    setLayout(m_mainLayout);
}

void ComponentFlatView::setItem(SessionItem* item)
{
    addItemProperties(item);
}

void ComponentFlatView::addItemProperties(SessionItem* item)
{
    Q_ASSERT(item);

    m_currentItem = item;
    setModel(m_currentItem->model());

    updateItemProperties(m_currentItem);
}

void ComponentFlatView::setModel(SessionModel* model)
{
    if (m_model) {
        disconnect(m_model, &SessionModel::dataChanged, this, &ComponentFlatView::onDataChanged);

    }

    m_model = model;

    if (m_model) {
        connect(m_model, &SessionModel::dataChanged, this, &ComponentFlatView::onDataChanged);
    }

}

void ComponentFlatView::clearEditor()
{
    Q_ASSERT(m_gridLayout);
    LayoutUtils::clearLayout(m_gridLayout, false);

    for(auto widget: m_widgetItems)
        delete widget;

    m_widgetItems.clear();

}

void ComponentFlatView::setShowChildren(bool show)
{
    m_show_children = show;

}

void ComponentFlatView::onDataChanged(const QModelIndex& topLeft, const QModelIndex&bottomRight,
                                      const QVector<int>& roles)
{
    Q_UNUSED(bottomRight);
    SessionItem *item = m_model->itemForIndex(topLeft);
    Q_ASSERT(item);
    if (item->modelType() == Constants::GroupItemType)
        updateItemProperties(m_currentItem);

    if (roles.contains(SessionModel::FlagRole))
        updateItemRoles(item);
}

void ComponentFlatView::updateItemProperties(SessionItem* item)
{
    Q_ASSERT(item);

    clearEditor();

    int nrow(0);
    for (auto child : ComponentUtils::componentItems(*item)) {

        auto widget = createWidget(child);
        if (!widget)
            continue;

        widget->addToGrid(m_gridLayout, ++nrow);
        m_widgetItems.push_back(widget);

        if (!m_show_children)
            break;
    }

}

void ComponentFlatView::updateItemRoles(SessionItem* item)
{
    for(auto widget: m_widgetItems)
        if (widget->item() == item)
            widget->updateItemRoles();
}

void ComponentFlatView::initGridLayout()
{
    delete m_gridLayout;
    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(6);
    m_mainLayout->addLayout(m_gridLayout);
    m_mainLayout->addStretch(1);
}

PropertyWidgetItem* ComponentFlatView::createWidget(const SessionItem* item)
{
    auto editor = PropertyEditorFactory::CreateEditor(*item);
    if (!editor)
        return nullptr;

    auto result = new PropertyWidgetItem(this);
    result->setItemEditor(item, editor);

    return result;
}

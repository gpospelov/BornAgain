// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboWidget.cpp
//! @brief     Implements class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ItemComboWidget.h"
#include "ItemComboToolBar.h"
#include "SessionItemWidget.h"
#include "GUIHelpers.h"
#include <QComboBox>
#include <QEvent>
#include <QStackedWidget>
#include <QVBoxLayout>

ItemComboWidget::ItemComboWidget(QWidget* parent)
    : QWidget(parent), m_toolBar(new ItemComboToolBar), m_stackedWidget(new QStackedWidget),
      m_currentItem(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);

    connect(m_toolBar, SIGNAL(comboChanged(QString)), this, SLOT(onComboChanged(QString)));
}

void ItemComboWidget::setItem(SessionItem* item)
{
    if (!item)
        return;

    QStringList validPresentations = activePresentationList(item);
    m_toolBar->setPresentationList(validPresentations);

    m_currentItem = item;

    setPresentation(currentPresentation());
}

void ItemComboWidget::registerWidget(const QString& presentationType, factory_function_t f)
{
    m_widgetFactory.registerItem(presentationType, f);
}

//! Sets stack to show widget corresponding to given presentation

void ItemComboWidget::setPresentation(const QString& presentationType)
{
    if (!activePresentationList(m_currentItem).contains(presentationType))
        return;

    m_toolBar->setPresentation(presentationType);

    Q_ASSERT(m_currentItem);

    SessionItemWidget* widget = m_presentationTypeToWidget[presentationType];

    if (!widget) {
        widget = m_widgetFactory.createItem(presentationType);
        m_stackedWidget->addWidget(widget);
        m_presentationTypeToWidget[presentationType] = widget;
        widget->setItem(m_currentItem);
    }
    Q_ASSERT(widget);
    m_toolBar->setActionList(widget->actionList());
    m_stackedWidget->setCurrentWidget(widget);
    if (widget->isHidden())
        widget->show();
}

//! Returns list of active presentations for given item. Active presentation is the one
//! which is present in QComboBox selector and can be selected. For example, if JobItem
//! is fittable, the list will contain "FitComparisonWidgetName".

QStringList ItemComboWidget::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList();
}

//! Returns full list of presentations valid for a given item.

QStringList ItemComboWidget::validPresentationList(SessionItem* item)
{
    return activePresentationList(item);
}

void ItemComboWidget::onComboChanged(const QString&)
{
    setPresentation(currentPresentation());
}

QString ItemComboWidget::currentPresentation() const
{
    return m_toolBar->currentPresentation();
}

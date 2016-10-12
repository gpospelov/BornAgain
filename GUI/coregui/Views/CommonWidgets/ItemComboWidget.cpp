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
#include <QDebug>
#include <QEvent>
#include <QStackedWidget>
#include <QVBoxLayout>

ItemComboWidget::ItemComboWidget(QWidget *parent)
    : QWidget(parent)
    , m_toolBar(new ItemComboToolBar)
    , m_stackedWidget(new QStackedWidget)
    , m_currentItem(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_stackedWidget);
    setLayout(layout);

    connect(m_toolBar, SIGNAL(comboChanged(QString)),
            this, SLOT(onComboChanged(QString)));
}


void ItemComboWidget::setItem(SessionItem *item)
{
    if(!item)
        return;

    QStringList validPresentations = getValidPresentationList(item);
    m_toolBar->setPresentationList(validPresentations);

    m_currentItem = item;

    setPresentation(currentPresentation());

}

void ItemComboWidget::registerWidget(const QString &presentationType, factory_function_t f)
{
    m_widgetFactory.registerItem(presentationType, f);
}

//! Sets stack to show widget corresponding to given presentation

void ItemComboWidget::setPresentation(const QString &presentationType)
{
    if(!getValidPresentationList(m_currentItem).contains(presentationType))
        return;

    m_toolBar->setPresentation(presentationType);

    Q_ASSERT(m_currentItem);

    SessionItemWidget *widget = m_presentationTypeToWidget[presentationType];

    if(!widget) {
        widget = m_widgetFactory.createItem(presentationType);
        m_stackedWidget->addWidget(widget);
        m_presentationTypeToWidget[presentationType] = widget;
        widget->setItem(m_currentItem);
    }
    Q_ASSERT(widget);
    m_toolBar->setActionList(widget->actionList());
    m_stackedWidget->setCurrentWidget(widget);
    if(widget->isHidden())
        widget->show();

}

//! Returns list of presentations valid for given item.

QStringList ItemComboWidget::getValidPresentationList(SessionItem *item)
{
    Q_UNUSED(item);
    return QStringList();
}


//void ItemComboWidget::showEvent(QShowEvent *)
//{
//    if(!m_externalToolBar)
//        return;


//}

//void ItemComboWidget::hideEvent(QHideEvent *)
//{
//    if(!m_externalToolBar)
//        return;

//}

void ItemComboWidget::onComboChanged(const QString &name)
{
    qDebug() << "ItemComboWidget::onWidgetChangeRequest" << name;
    setPresentation(currentPresentation());
}

QString ItemComboWidget::currentPresentation() const
{
    return m_toolBar->currentPresentation();
}


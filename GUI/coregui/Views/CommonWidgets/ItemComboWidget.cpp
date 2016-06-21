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
#include <QStackedWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QEvent>
#include <QDebug>

ItemComboWidget::ItemComboWidget(QWidget *parent)
    : QWidget(parent)
    , m_toolBar(new ItemComboToolBar)
    , m_stackedWidget(new QStackedWidget)
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
    m_currentItem = item;

    if(!m_currentItem)
        return;

    QWidget *widget = m_presentationTypeToWidget[currentPresentation()];

    if(!widget) {
        widget = m_widgetFactory.createItem(currentPresentation());
        m_stackedWidget->addWidget(widget);
        m_presentationTypeToWidget[currentPresentation()] = widget;
    }
    Q_ASSERT(widget);
    m_stackedWidget->setCurrentWidget(widget);
    if(widget->isHidden())
        widget->show();

}

void ItemComboWidget::add(const QString &presentationType, std::function<QWidget *()> f)
{
    m_widgetFactory.registerItem(presentationType, f);
    m_toolBar->addPresentationType(presentationType);
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
}

QString ItemComboWidget::currentPresentation() const
{
    return m_toolBar->currentPresentation();
}


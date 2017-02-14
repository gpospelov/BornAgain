// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemWidget.cpp
//! @brief     Declares class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionItemWidget.h"
#include "SessionItem.h"


SessionItemWidget::SessionItemWidget(QWidget *parent)
    : QWidget(parent)
{

}

QList<QAction *> SessionItemWidget::actionList()
{
    return QList<QAction *>();
}

// --------------------------------------------------------------------------------------------- //

#include <QDebug>

NewSessionItemWidget::NewSessionItemWidget(QWidget* parent)
    : QWidget(parent)
    , m_currentItem(nullptr)
    , is_subscribed(false)
{

}

NewSessionItemWidget::~NewSessionItemWidget()
{
    unsubscribe();
}

void NewSessionItemWidget::setItem(SessionItem* item)
{
    qDebug() << "NewSessionItemWidget::setItem(SessionItem* item)" << item;

    if(m_currentItem == item)
        return;

    unsubscribe(); // from previous item

    m_currentItem = item;
   if (!m_currentItem)
       return;

   subscribe();
}

QList<QAction*> NewSessionItemWidget::actionList()
{
    return QList<QAction *>();
}

void NewSessionItemWidget::showEvent(QShowEvent*)
{
    qDebug() << "NewSessionItemWidget::showEvent 1.1 was shown?";
    subscribe();
}

void NewSessionItemWidget::hideEvent(QHideEvent*)
{
    qDebug() << "NewSessionItemWidget::hideEvent 1.1 was hidden?";
    unsubscribe();
}

void NewSessionItemWidget::subscribe()
{
    qDebug() << "NewSessionItemWidget::subscribe()" << m_currentItem;

    if (!m_currentItem || is_subscribed)
        return;

    m_currentItem->mapper()->setOnItemDestroy([this](SessionItem*) { m_currentItem = 0; }, this);

    subscribeToItem();

    is_subscribed = true;
}

void NewSessionItemWidget::unsubscribe()
{
    qDebug() << "NewSessionItemWidget::unsubscribe()" << m_currentItem;
    if (m_currentItem)
        m_currentItem->mapper()->unsubscribe(this);

    unsubscribeFromItem();

    is_subscribed = false;
}

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

SessionItemWidget::SessionItemWidget(QWidget* parent)
    : QWidget(parent)
    , m_currentItem(nullptr)
    , is_subscribed(false)
{

}

SessionItemWidget::~SessionItemWidget()
{
    unsubscribe();
}

void SessionItemWidget::setItem(SessionItem* item)
{
    if(m_currentItem == item)
        return;

    unsubscribe(); // from previous item

    m_currentItem = item;
    if (!m_currentItem)
        return;

    if(!isHidden())
        subscribe();
}

QList<QAction*> SessionItemWidget::actionList()
{
    return QList<QAction *>();
}

void SessionItemWidget::showEvent(QShowEvent*)
{
    subscribe();
}

void SessionItemWidget::hideEvent(QHideEvent*)
{
    unsubscribe();
}

void SessionItemWidget::subscribe()
{
    if (!m_currentItem || is_subscribed)
        return;

    m_currentItem->mapper()->setOnItemDestroy([this](SessionItem*) { m_currentItem = 0; }, this);

    subscribeToItem();

    is_subscribed = true;
}

void SessionItemWidget::unsubscribe()
{
    if (m_currentItem)
        m_currentItem->mapper()->unsubscribe(this);

    unsubscribeFromItem();

    is_subscribed = false;
}

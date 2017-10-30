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
#include "SessionItemController.h"

SessionItemWidget::SessionItemWidget(QWidget* parent)
    : QWidget(parent)
    , m_itemController(new SessionItemController(this))
{
    m_itemController->setSubscribeCallback([this](){subscribeToItem();});
    m_itemController->setUnsubscribeCallback([this](){unsubscribeFromItem();});
}

SessionItemWidget::~SessionItemWidget() = default;

#include <QDebug>
void SessionItemWidget::setItem(SessionItem* item)
{
    qDebug() << "SessionItemController::setItem()" << item << isVisible();

    m_itemController->setItem(item);

    if (isVisible())
        m_itemController->subscribe();
}

QList<QAction*> SessionItemWidget::actionList()
{
    return QList<QAction *>();
}

SessionItem* SessionItemWidget::currentItem()
{
    return m_itemController->currentItem();
}

void SessionItemWidget::showEvent(QShowEvent*)
{
    m_itemController->subscribe();
}

void SessionItemWidget::hideEvent(QHideEvent*)
{
    m_itemController->unsubscribe();
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/SessionItemController.h
//! @brief     Defines class SessionItemController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONITEMCONTROLLER_H
#define SESSIONITEMCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>
#include <functional>

class SessionItem;

//! Provides subscribe/unsubscribe mechanism for any QObject to track
//! time of life of SessionItem. Mainly intended for SessionItemWidget.

class BA_CORE_API_ SessionItemController : public QObject
{
    Q_OBJECT
public:
    using callback_t = std::function<void(void)>;

    explicit SessionItemController(QObject* prt);
    ~SessionItemController();

    void setItem(SessionItem* item);

    SessionItem* currentItem();

    void setSubscribeCallback(callback_t fun);
    void setUnsubscribeCallback(callback_t fun);

    void subscribe();
    void unsubscribe();

private:
    void onItemDestroy();
    void onControllerDestroy();
    void subscribeParent();
    void unsubscribeParent();

    callback_t m_subscribe_callback;
    callback_t m_unsubscribe_callback;
    SessionItem* m_item;
    bool m_parent_subscribed;
};

#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/MessageService.cpp
//! @brief     Implements MessageService class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MessageService.h"
#include "GUIMessage.h"
#include <QObject>
#include <QSet>

MessageService::~MessageService() { clear(); }

void MessageService::clear()
{
    for (auto message : m_messages)
        delete message;

    m_messages.clear();
}

void MessageService::send_message(QObject* sender, const QString& message_type,
                                  const QString& description)
{
    m_messages.append(new GUIMessage(sender, message_type, description));
}

const QList<GUIMessage*> MessageService::messages() const
{
    return m_messages;
}

QStringList MessageService::senderList() const
{
    QSet<QString> set;
    for (auto message : messages())
        set.insert(message->senderName());

    return set.toList();
}

int MessageService::messageCount(const QObject* sender, const QString& message_type)
{
    int result(0);
    for (auto message : messages())
        if (message->sender() == sender) {
            if (message_type.isEmpty())
                ++result;
            else if (message->messageType() == message_type)
                ++result;
        }

    return result;
}

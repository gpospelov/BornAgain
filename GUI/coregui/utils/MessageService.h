// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/MessageService.h
//! @brief     Defines MessageService class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include "WinDllMacros.h"
#include <QMap>
#include <QStringList>

class MessageContainer;
class QObject;
class GUIMessage;

//! @class MessageService
//! @brief The service to collect messages from different senders.

class BA_CORE_API_ MessageService
{
public:
    virtual ~MessageService();

    void clear();

    void send_message(QObject* sender, const QString& message_type, const QString& description);

    const QList<GUIMessage*> messages() const;

    QStringList senderList() const;

    int messageCount(const QObject* sender, const QString& message_type = QString());

private:
    QList<GUIMessage*> m_messages;
};

#endif // MESSAGESERVICE_H

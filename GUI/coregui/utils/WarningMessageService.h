// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/WarningMessageService.h
//! @brief     Declares abstract IMessageService interface
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef WARNINGMESSAGESERVICE_H
#define WARNINGMESSAGESERVICE_H

#include "IMessageService.h"
#include <QMap>
#include <QStringList> // need detected by TeamCity

class MessageContainer;
class QObject;

//! @class WarningMessageService
//! @brief The service to collect warning messages from different senders.

class WarningMessageService : public IMessageService {
public:
    typedef QMap<QObject *, MessageContainer *> container_t;
    typedef container_t::iterator iterator;
    typedef container_t::const_iterator const_iterator;

    WarningMessageService(){}
    virtual ~WarningMessageService();

    void clear();

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    MessageContainer *getMessageContainer(QObject *sender);
    const MessageContainer *getMessageContainer(QObject *sender) const;

    void send_message(QObject *sender, const QString &message_type, const QString &description);

    bool hasWarnings(QObject *sender);

    QStringList getMessageStringList(QObject *sender) const;
    QString getMessages(QObject *sender) const;

private:
    container_t m_messageContainer;
};

#endif // WARNINGMESSAGESERVICE_H

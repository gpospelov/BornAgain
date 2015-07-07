// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/WarningMessageService.h
//! @brief     Defines abstract IMessageService interface
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef WARNINGMESSAGESERVICE_H
#define WARNINGMESSAGESERVICE_H

#include "IMessageService.h"
#include <QMap>

class MessageContainer;
class QObject;

//! @class WarningMessageService
//! @brief The service to collect warning messages from different senders.

class WarningMessageService : public IMessageService{
public:
    enum EMessageType {
        XML_FORMAT_ERROR = 0x0001,
        SET_ITEM_PROPERTY_ERROR = 0x0002,
        OPEN_FILE_ERROR = 0x0004,
        EXCEPTION_THROW = 0x0008
    };

    typedef QMap<QObject *, MessageContainer *> container_t;
    typedef container_t::iterator iterator;
    typedef container_t::const_iterator const_iterator;

    WarningMessageService(){}
    virtual ~WarningMessageService();

    void clear();

    iterator begin() { return m_messageContainer.begin(); }
    const_iterator begin() const { return m_messageContainer.begin(); }
    iterator end() { return m_messageContainer.end(); }
    const_iterator end() const { return m_messageContainer.end(); }

    MessageContainer *getMessageContainer(QObject *sender);

    const MessageContainer *getMessageContainer(QObject *sender) const;

    void subscribe(QObject *sender);
    void unsubscribe(QObject *sender);

    void send_message(QObject *sender, EMessageType warning_type, const QString &description);

    QString getMessageTypeString(EMessageType messageType) const;

private:
    container_t m_messageContainer;
    static QMap<EMessageType, QString> m_warningTypeToString;
};

#endif

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
#include "MessageContainer.h"
#include <QObject>

MessageService::~MessageService()
{
    clear();
}

void MessageService::clear()
{
    for(container_t::iterator it=m_messageContainer.begin(); it!=m_messageContainer.end(); ++it) {
        delete it.value();
    }
    m_messageContainer.clear();
}

MessageService::iterator MessageService::begin()
{
    return m_messageContainer.begin();
}

MessageService::const_iterator MessageService::begin() const
{
    return m_messageContainer.begin();
}

MessageService::iterator MessageService::end()
{
    return m_messageContainer.end();
}

MessageService::const_iterator MessageService::end() const
{
    return m_messageContainer.end();
}

MessageContainer *MessageService::getMessageContainer(QObject *sender)
{
    iterator it = m_messageContainer.find(sender);
    if(it != m_messageContainer.end()) {
        return it.value();
    }
    return 0;
}

const MessageContainer *MessageService::getMessageContainer(QObject *sender) const
{
    const_iterator it = m_messageContainer.find(sender);
    if(it != m_messageContainer.end()) {
        return it.value();
    }
    return 0;
}

void MessageService::send_message(QObject *sender, const QString &message_type, const QString &description)
{
    MessageContainer *container = getMessageContainer(sender);
    if(!container) {
        container = new MessageContainer();
        m_messageContainer[sender] = container;
    }

    GUIMessage *message = new GUIMessage(sender->objectName(), message_type, description);
    container->append(message);
}

bool MessageService::hasWarnings(QObject *sender)
{
    MessageContainer *container = getMessageContainer(sender);
    if(container && container->size()) return true;
    return false;
}

//! Returns list of string with error messages
QStringList MessageService::getMessageStringList(QObject *sender) const
{
    QStringList result;
    const MessageContainer *container = getMessageContainer(sender);
    if(container) {
        for(MessageContainer::const_iterator it=container->begin(); it!=container->end(); ++it) {
            result.append((*it)->getText());
        }
    }
    return result;
}

//! Returns multi line string representing all messages
QString MessageService::getMessages(QObject *sender) const
{
    QString result;
    QStringList messages = getMessageStringList(sender);
    for(int i=0; i<messages.size(); ++i) {
        result.append(messages.at(i));
        result.append("\n");
    }
    return result;
}

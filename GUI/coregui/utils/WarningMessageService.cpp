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

#include "WarningMessageService.h"
#include "MessageContainer.h"
#include "GUIMessage.h"
#include "GUIHelpers.h"
#include <QObject>


namespace {

QMap<WarningMessageService::EWarningType, QString> initWarningTypeToString()
{
    QMap<WarningMessageService::EWarningType, QString> result;
    result[WarningMessageService::XML_FORMAT_ERROR]= "XML_FORMAT_ERROR";
    result[WarningMessageService::SET_ITEM_PROPERTY_ERROR]= "SET_ITEM_PROPERTY_ERROR";
    return result;
}

}

QMap<WarningMessageService::EWarningType, QString> WarningMessageService::m_warningTypeToString
= initWarningTypeToString();


WarningMessageService::~WarningMessageService()
{
    clear();
}

void WarningMessageService::clear()
{
    for(container_t::iterator it=m_messageContainer.begin(); it!=m_messageContainer.end(); ++it) {
        delete it.value();
    }
    m_messageContainer.clear();
}

MessageContainer *WarningMessageService::getMessageContainer(QObject *sender)
{
    return m_messageContainer[sender];
}

void WarningMessageService::subscribe(QObject *sender)
{
    MessageContainer *container = getMessageContainer(sender);
    if(!container) {
        container = new MessageContainer();
        m_messageContainer[sender] = container;
    }
    container->setActive(true);
}

void WarningMessageService::unsubscribe(QObject *sender)
{
    MessageContainer *container = getMessageContainer(sender);
    if(container) {
        container->setActive(false);
    }
}

void WarningMessageService::register_warning(QObject *sender, WarningMessageService::EWarningType warning_type, const QString &description)
{
    MessageContainer *container = getMessageContainer(sender);
    if(container && container->isActive()) {
        GUIMessage *message = new GUIMessage(sender->objectName(), getWarningTypeString(warning_type), description);
        container->append(message);
    } else {
        QString message = QString("Warning %1 from object '%2' ->'%3'").arg(getWarningTypeString(warning_type))
                .arg(sender->objectName()).arg(description);
        throw GUIHelpers::Error(message);
    }
}

QString WarningMessageService::getWarningTypeString(WarningMessageService::EWarningType warningType) const
{
    return m_warningTypeToString[warningType];
}

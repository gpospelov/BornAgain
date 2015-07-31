// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIMessage.cpp
//! @brief     Implements class GUIMessage.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIMessage.h"

GUIMessage::GUIMessage(const QString &senderName, const QString &messageType,
                       const QString &messageDescription)
    : m_senderName(senderName), m_messageType(messageType), m_messageDescription(messageDescription)
{
}

QString GUIMessage::getSenderName() const
{
    return m_senderName;
}

QString GUIMessage::getMessageType() const
{
    return m_messageType;
}

QString GUIMessage::getMessageDescription() const
{
    return m_messageDescription;
}

QString GUIMessage::getText() const
{
    QString result
        = QString("%1 %2 %3").arg(m_senderName).arg(m_messageType).arg(m_messageDescription);
    return result;
}

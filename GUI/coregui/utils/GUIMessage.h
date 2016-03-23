// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIMessage.h
//! @brief     Defines class GUIMessage.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUIMESSAGE_H
#define GUIMESSAGE_H

#include <QString>

class GUIMessage
{
public:
    GUIMessage(const QString &senderName, const QString &messageType,
               const QString &messageDescription);

    QString getSenderName() const;
    QString getMessageType() const;
    QString getMessageDescription() const;

    QString getText() const;

private:
    QString m_senderName;
    QString m_messageType;
    QString m_messageDescription;
};

#endif


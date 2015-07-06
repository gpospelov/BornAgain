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

#include <QMap>

class MessageContainer;
class QObject;

//! @class WarningMessageService
//! @brief The service to collect warning messages from different senders.

class WarningMessageService {
public:
    enum EWarningType {
        XML_FORMAT_ERROR = 0x0001,
        SET_ITEM_PROPERTY_ERROR = 0x0002
    };

    typedef QMap<QObject *, MessageContainer *> container_t;

    WarningMessageService(){}
    virtual ~WarningMessageService();

    void clear();

    MessageContainer *getMessageContainer(QObject *sender);

    void subscribe(QObject *sender);
    void unsubscribe(QObject *sender);

    void register_warning(QObject *sender, EWarningType warning_type, const QString &description);

    QString getWarningTypeString(EWarningType warningType) const;
private:
    container_t m_messageContainer;
    static QMap<EWarningType, QString> m_warningTypeToString;
};

#endif

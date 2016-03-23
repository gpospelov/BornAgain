// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModelAssistant.h
//! @brief     Defines class SessionModelAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODELASSISTANT_H
#define SESSIONMODELASSISTANT_H

#include <QString>
#include <QMap>

class SessionItem;

//! @class SessionModelAssistant
//! @brief Assists SessionModel in various aspects. Currently keeps record of all reading errors
//! to make detailed report in the case of project load failure.
//!
//! It has two types of behavior on reported error. In THROW_EXCEPTION mode assistant just
//! throws an exception with error description.
//!
//! In RECORD_ERROR mode it saves errors in a list for later printout. This mode is triggered
//! by start_error_recording() method and intended for use during project loading.

class SessionModelAssistant
{
public:
    enum EOnErrorBehavior {
        THROW_EXCEPTION,
        RECORD_ERROR
    };
    enum EErrorType {
        XML_FORMAT_ERROR = 0x0001,
        SET_ITEM_PROPERTY_ERROR = 0x0002
    };
    class Error {
    public:
        Error(EErrorType error_type, const QString &description)
            : m_error_type(error_type), m_error_description(description){}
        EErrorType m_error_type;
        QString m_error_description;
    };

    SessionModelAssistant();

    void start_error_recording();

    void stop_error_recording();

    void clear_errors();

    bool hasErrors() const;

    void report_unknown_item_property(const SessionItem *item, const QString &property_name);

private:
    QList<Error> m_list_of_errors;
    EOnErrorBehavior m_on_error_behavior;
};

#endif

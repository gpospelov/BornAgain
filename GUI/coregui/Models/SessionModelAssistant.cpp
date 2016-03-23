// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModelAssistant.cpp
//! @brief     Implements class SessionModelAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionModelAssistant.h"
#include "GUIHelpers.h"
#include "SessionItem.h"

SessionModelAssistant::SessionModelAssistant()
    : m_on_error_behavior(THROW_EXCEPTION)
{

}

void SessionModelAssistant::start_error_recording()
{
    clear_errors();
    m_on_error_behavior = RECORD_ERROR;
}

void SessionModelAssistant::stop_error_recording()
{
    m_on_error_behavior = THROW_EXCEPTION;
}

void SessionModelAssistant::clear_errors()
{
    m_list_of_errors.clear();
}

bool SessionModelAssistant::hasErrors() const
{
    return m_list_of_errors.size();
}

void SessionModelAssistant::report_unknown_item_property(const SessionItem *item,
                                                         const QString &property_name)
{
    QString message = QString("Unknown property '%1' for item type '%2'")
                      .arg(item->modelType()).arg(property_name);
    if(m_on_error_behavior == THROW_EXCEPTION) {
        throw GUIHelpers::Error(message);
    }
    m_list_of_errors.push_back(Error(SET_ITEM_PROPERTY_ERROR, message));

}

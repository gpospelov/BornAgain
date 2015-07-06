// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/MessageContainer.cpp
//! @brief     Implements class MessageContainer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MessageContainer.h"
#include "GUIMessage.h"
#include "GUIHelpers.h"

namespace {
int maximum_number_of_messages = 100;
}

MessageContainer::MessageContainer()
    : m_is_active(true)
{

}

MessageContainer::~MessageContainer()
{
    clear();
}

void MessageContainer::clear()
{
    for(QList<GUIMessage *>::iterator it=m_messages.begin(); it!= m_messages.end(); ++it) {
        delete (*it);
    }
    m_messages.clear();
}

//! Sets active flag to accept new messages
void MessageContainer::setActive(bool active)
{
    m_is_active = active;
}

bool MessageContainer::isActive() const
{
    return m_is_active;
}

void MessageContainer::append(GUIMessage *message)
{
    if(!isActive()) {
        GUIHelpers::Error("MessageContainer::append() -> Error. Not active.");
    }

    if(m_messages.size() < maximum_number_of_messages) {
        m_messages.append(message);
    } else {
        GUIHelpers::Error("MessageContainer::append() -> Error. Stack overflow.");
    }
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/MessageContainer.cpp
//! @brief     Implements class MessageContainer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MessageContainer.h"
#include "GUIMessage.h"
#include "GUIHelpers.h"

namespace {
int maximum_number_of_messages = 100;
}

MessageContainer::MessageContainer()
{
}

MessageContainer::~MessageContainer()
{
    clear();
}

MessageContainer::iterator MessageContainer::begin()
{
    return m_messages.begin();
}

MessageContainer::const_iterator MessageContainer::begin() const
{
    return m_messages.begin();
}

MessageContainer::iterator MessageContainer::end()
{
    return m_messages.end();
}

MessageContainer::const_iterator MessageContainer::end() const
{
    return m_messages.end();
}

int MessageContainer::size() const
{
    return m_messages.size();
}

void MessageContainer::clear()
{
    for(QList<GUIMessage *>::iterator it=m_messages.begin(); it!= m_messages.end(); ++it) {
        delete (*it);
    }
    m_messages.clear();
}

void MessageContainer::append(GUIMessage *message)
{
    if(m_messages.size() < maximum_number_of_messages) {
        m_messages.append(message);
    } else {
        GUIHelpers::Error("MessageContainer::append() -> Error. Stack overflow.");
    }
}

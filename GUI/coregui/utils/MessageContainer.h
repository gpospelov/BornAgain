// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/MessageContainer.h
//! @brief     Defines class MessageContainer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MESSAGECONTAINER_H
#define MESSAGECONTAINER_H

#include <QList>

class GUIMessage;

//! @class MessageContainer
//! @brief The class to hold warning messages

class MessageContainer
{
public:
    MessageContainer();
    virtual ~MessageContainer();

    void clear();

    void setActive(bool active);
    bool isActive() const;

    void append(GUIMessage *message);

private:
    bool m_is_active;
    QList<GUIMessage *> m_messages;
};

#endif

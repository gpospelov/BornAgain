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

    typedef QList<GUIMessage *> container_t;
    typedef container_t::iterator iterator;
    typedef container_t::const_iterator const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    int size() const;

    void clear();

    void append(GUIMessage *message);

private:
    container_t m_messages;
};

#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/INamed.h
//! @brief     Defines class INamed.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef INAMED_H
#define INAMED_H

#include <string>

//! Virtual base class for all objects that have a name.

class INamed
{
 public:
    INamed() : m_name(), m_title() {}
    INamed(const std::string &name) : m_name(name), m_title() { }
    INamed(const std::string &name, const std::string &title) : m_name(name), m_title(title) { }
    virtual ~INamed(){}

    void setName(std::string name) { m_name = name; }
    std::string getName() const { return m_name; }

    std::string getTitle() const { return m_title; }
    void setTitle(std::string title) { m_title = title; }

 protected:
    std::string m_name;
    std::string m_title;
};

#endif // INAMED_H

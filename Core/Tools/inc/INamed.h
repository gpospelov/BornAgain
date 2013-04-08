// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/INamed.h
//! @brief     Defines and implements the standard mix-in INamed.
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

//! Standard mix-in for all objects that have a name.

class INamed
{
 public:
    //! Default constructor, setting name="".
    INamed() : m_name() {}

    //! Constructor that sets the _name_.
    INamed(const std::string& name) : m_name(name) {}

    //! Destructor.
    virtual ~INamed() {}

    //! Sets the _name_.
    void setName(std::string name) { m_name = name; }

    //! Returns the name.
    std::string getName() const { return m_name; }

 protected:
    //! The name of this object.
    std::string m_name;
};

#endif // INAMED_H



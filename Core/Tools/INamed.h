// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/INamed.h
//! @brief     Defines and implements the standard mix-in INamed.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INAMED_H
#define INAMED_H

#include "WinDllMacros.h"
#include <string>

//! @class INamed
//! @ingroup tools_internal
//! @brief Interface for named objects.

class BA_CORE_API_ INamed
{
public:
    //! Default constructor, setting name="".
    INamed();

    //! Constructor that sets the _name_.
    INamed(std::string name);

    //! Destructor.
    virtual ~INamed();

    //! Returns the name.
    std::string getName() const;

protected:
    //! Sets the _name_.
    void setName(std::string name);

private:
    //! The name of this object.
    std::string m_name;
};

#endif // INAMED_H



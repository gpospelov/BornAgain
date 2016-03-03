// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/INamedShared.h
//! @brief     Defines and implements the standard mix-in INamedShared.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INAMEDSHARED_H
#define INAMEDSHARED_H

#include "WinDllMacros.h"
#include <string>

//! @class INamedShared
//! @ingroup tools_internal
//! @brief Interface for named objects.

class BA_CORE_API_ INamedShared
{
public:
    //! Default constructor, setting name="".
    INamedShared();

    //! Constructor that sets the _name_.
    INamedShared(std::string name);

    //! Destructor.
    virtual ~INamedShared();

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



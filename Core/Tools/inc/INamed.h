// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/INamed.h
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
#include "ICloneable.h"
#include "IShareable.h"
#include <string>

//! @class INamed
//! @ingroup tools_internal
//! @brief Interface for named objects.
template <typename T>
class BA_CORE_API_ INamedTemplate
{
public:
    //! Default constructor, setting name="".
    INamedTemplate();

    //! Constructor that sets the _name_.
    INamedTemplate(std::string name);

    //! Destructor.
    virtual ~INamedTemplate();

    //! Returns the name.
    std::string getName() const;

protected:
    //! Sets the _name_.
    void setName(std::string name);

private:
    //! The name of this object.
    std::string m_name;
};


// expose to C++
typedef INamedTemplate<ICloneable> INamed;
typedef INamedTemplate<IShareable> INamedShared;



#endif // INAMED_H



// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/INamed.h
//! @brief     Defines INamed class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_INAMED_H
#define BORNAGAIN_CORE_BASICS_INAMED_H

#include "Wrap/WinDllMacros.h"
#include <string>

//! Interface for named objects.
//! @ingroup tools_internal

class BA_CORE_API_ INamed
{
public:
    INamed() : m_name() {}
    INamed(const std::string& name) : m_name(name) {}
    virtual ~INamed();
    std::string getName() const { return m_name; }

protected:
    void setName(const std::string& name) { m_name = name; }

private:
    std::string m_name;
};

#endif // BORNAGAIN_CORE_BASICS_INAMED_H

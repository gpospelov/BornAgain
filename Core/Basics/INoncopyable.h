// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/INoncopyable.h
//! @brief     Defines the standard mix-in INoncopyable.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INONCOPYABLE_H
#define INONCOPYABLE_H

#include "WinDllMacros.h"

//! Mix-in for objects that must not be copied.
//!
//! This virtual base class disables the copy constructor and the operator=
//! in all its child classes.

//! @ingroup tools_internal

class BA_CORE_API_ INoncopyable
{
public:
    INoncopyable() {}
    virtual ~INoncopyable() {}
    INoncopyable(const INoncopyable&) = delete;
    INoncopyable& operator=(const INoncopyable&) = delete;
};

#endif // INONCOPYABLE_H

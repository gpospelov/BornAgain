// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Assert.h
//! @brief     Defines the macro ASSERT.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BASICS_ASSERT_H
#define BORNAGAIN_CORE_BASICS_ASSERT_H

// ASSERT must be declared as a macro, not a function, in order for the error
// message to correctly report the source line where the assertion failed.

#ifdef QT_MESSAGELOGCONTEXT

#include <QtGlobal>
#define ASSERT(condition) if (!(condition)) qFatal("Assertion failed")

#else // QT_MESSAGELOGCONTEXT undefined

#include <cassert>
#define ASSERT(condition) assert(condition)

#endif // QT_MESSAGELOGCONTEXT

#endif // BORNAGAIN_CORE_BASICS_ASSERT_H

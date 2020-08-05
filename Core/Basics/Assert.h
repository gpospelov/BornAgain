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

#ifdef BORNAGAIN_GUI

#include <QtGlobal>
#define ASSERT(condition) \
    if (!(condition)) \
        qFatal("assertion failed");

#else // The non-GUI case is used by our test suite

#include <iostream>
#define ASSERT(condition) \
    if (!(condition)) { \
        std::cerr << "assertion failed" << std::endl; \
        exit(1); \
    }

#endif // BORNAGAIN_GUI

#endif // BORNAGAIN_CORE_BASICS_ASSERT_H

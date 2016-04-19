// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/verify_throw_macro.h
//! @brief     Declares macro to test exception throw
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef VERIFY_THROW_MACRO_H
#define VERIFY_THROW_MACRO_H

#include <QTest>

#define QVERIFY_THROW(expression, ExpectedExceptionType) \
do \
{ \
bool caught_ = false; \
try { expression; } \
catch (ExpectedExceptionType const&) { caught_ = true; } \
catch (...) {} \
if (!QTest::qVerify(caught_, #expression ", " #ExpectedExceptionType, "", __FILE__, __LINE__))\
return; \
} while(0)


#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIPerformanceTest/GUIPerformanceTest.h
//! @brief     Defines GUI performance functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUIPERFORMANCETEST_H
#define GUIPERFORMANCETEST_H

#include "IFunctionalTest.h"

//! Functional test to measure performance of GUI by mimicking activity typical for RealTimeView.

class GUIPerformanceTest : public IFunctionalTest
{
public:
    GUIPerformanceTest();

    bool runTest();

};

#endif // GUIPERFORMANCETEST_H

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
#include <QString>
#include <memory>

class ApplicationModels;

//! Functional test to measure performance of GUI by mimicking activity typical for RealTimeView.

class GUIPerformanceTest : public IFunctionalTest
{
public:
    GUIPerformanceTest();
    ~GUIPerformanceTest();

    void test_domain_to_gui();
    void test_gui_to_domain();
    void test_real_time();

protected:
    bool runTest();

private:
    std::unique_ptr<ApplicationModels> m_models;
    QString m_sample_name;
};

#endif // GUIPERFORMANCETEST_H

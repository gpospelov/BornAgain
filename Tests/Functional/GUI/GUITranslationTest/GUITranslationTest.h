// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITranslationTest/GUITranslationTest.h
//! @brief     Defines GUI translation functional test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUITRANSLATIONTEST_H
#define GUITRANSLATIONTEST_H

#include "IFunctionalTest.h"
#include <memory>

class GISASSimulation;
class ApplicationModels;

class GUITranslationTest : public IFunctionalTest
{
public:
    GUITranslationTest();

    ~GUITranslationTest();
    bool runTest();


private:
    void processParameterTree();

    std::unique_ptr<GISASSimulation> m_simulation;
    std::unique_ptr<ApplicationModels> m_models;
};

#endif

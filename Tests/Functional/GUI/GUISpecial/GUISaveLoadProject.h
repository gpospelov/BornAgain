// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIPerformanceTest/GUISaveLoadProject.h
//! @brief     Defines GUISaveLoadProject test.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUISAVELOADPROJECT_H
#define GUISAVELOADPROJECT_H

#include "IFunctionalTest.h"
#include <QString>
#include <memory>

class ApplicationModels;

//! Functional test to check persistency of application models after save/load.

class GUISaveLoadProject : public IFunctionalTest
{
public:
    GUISaveLoadProject();

protected:
    bool runTest();
};

#endif // GUISAVELOADPROJECT_H

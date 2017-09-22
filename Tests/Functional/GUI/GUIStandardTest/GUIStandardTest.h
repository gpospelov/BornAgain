// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/GUIStandardTest.h
//! @brief     Defines class GUIStandardTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUISTANDARDTEST_H
#define GUISTANDARDTEST_H

#include "IReferencedTest.h"
#include "OutputData.h"

class GISASSimulation;

//! A functional test of the BornAgain GUI.
//!   Performs a given standard simulation directly, and through domain->GUI->domain,
//!   and compares results.
//!   Invoked by GUIStandardTest.

class GUIStandardTest : public IReferencedTest
{
public:
    GUIStandardTest(const std::string& name, const std::string& description,
            GISASSimulation* reference_simulation, double threshold);
    virtual ~GUIStandardTest();

    bool runTest() final;

private:
    void createDomainSimulation();

    GISASSimulation* m_reference_simulation;
    GISASSimulation* m_domain_simulation;
};

#endif // GUISTANDARDTEST_H

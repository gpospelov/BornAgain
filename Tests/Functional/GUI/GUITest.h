// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITest.h
//! @brief     Declares class GUITest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef GUITEST_H
#define GUITEST_H

#include "IFunctionalTest.h" // inheriting from
#include "OutputData.h"

class GISASSimulation;

//! @class GUITest
//! @ingroup standard_samples
//! @brief A functional test of the BornAgain GUI.
//!   Performs a given standard simulation directly, and through domain->GUI->domain,
//!   and compares results.
//!   Invoked by GUIStandardTest.

class GUITest : public IFunctionalTest
{
public:
    GUITest(const std::string& name, const std::string& description,
            GISASSimulation* reference_simulation, double threshold);
    virtual ~GUITest();

    virtual void runTest();
    virtual int analyseResults();

    const OutputData<double>* getOutputData() const;

    virtual void printResults(std::ostream& ostr) const;

private:
    void createDomainSimulation();

    GISASSimulation *m_reference_simulation;
    GISASSimulation *m_domain_simulation;
    double m_threshold;
    double m_difference;
};

#endif // GUITEST_H

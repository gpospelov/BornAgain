// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreStandardTest.h
//! @brief     Defines class CoreStandardTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CORESTANDARDTEST_H
#define CORESTANDARDTEST_H

#include "IReferencedTest.h"

template <class T> class OutputData;
class GISASSimulation;

//! A functional test of BornAgain/Core.
//!   Performs a given standard simulation, and compares results with reference data.
//!   Invoked from CoreStandardTest.

class CoreStandardTest : public IStandardTest
{
public:
    CoreStandardTest(const std::string& name, const std::string& description,
             GISASSimulation* simulation, double threshold);
    ~CoreStandardTest() final;

    bool runTest() final;

private:
    GISASSimulation* m_simulation;
    OutputData<double>* m_reference;
};

#endif // CORESTANDARDTEST_H

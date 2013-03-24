// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestFittingModule3.h 
//! @brief     Defines class TestFittingModule3.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTFITTINGMODULE3_H
#define TESTFITTINGMODULE3_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "Simulation.h"
#include "ISampleBuilder.h"
#include "SafePointerVector.h"
#include <vector>

class FitSuite;

//! Simultaneous fit of several 1D scans.

//! Mixture of cylinders and prisms, 4 parameters.
//!
class TestFittingModule3 : public IFunctionalTest
{
public:
    typedef SafePointerVector<OutputData<double> >  DataScan_t;

    TestFittingModule3();
    virtual ~TestFittingModule3();
    virtual void execute();

private:
    void initializeSample();
    void initializeSimulation();
    void initializeRealData();

    Simulation *m_simulation;
    ISample *m_sample;
    FitSuite *m_fitSuite;
    OutputData<double > *m_real_data;
    DataScan_t m_data_scans;
};

#endif // TESTFITTINGMODULE3_H

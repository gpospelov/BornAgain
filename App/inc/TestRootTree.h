#ifndef TESTROOTTREE_H
#define TESTROOTTREE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestRootTree.h
//! @brief  Definition of TestRootTree class for testing ROOT trees
//! @author Scientific Computing Group at FRM II
//! @date   18.07.2012

#include "IFunctionalTest.h"
#include "ISample.h"
#include "OutputData.h"
#include "GISASExperiment.h"


//- -------------------------------------------------------------------
//! @class TestRootTree.h
//! @brief using ROOT trees to read/write data from/to disk
//- -------------------------------------------------------------------
class TestRootTree : public IFunctionalTest
{
public:
    TestRootTree();
    virtual ~TestRootTree();

    virtual void execute();

private:
    //! example showing writing in the tree simple data structures
    void simple_write();

    //! example showing reading from the tree simple data structures
    void simple_read();

    //! example showing writing in the tree complex data structures
    void complex_write();

    //! example showing reading from the tree complex data structures
    void complex_read();

    void initializeMesoCrystal(double meso_alpha, double meso_phi, double nanopart_radius);

    ISample *m_sample;
    GISASExperiment *m_experiment;
    OutputData<double> *m_data;
};



#endif // TESTROOTTREE_H

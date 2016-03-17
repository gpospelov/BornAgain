// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestRootTree.h
//! @brief     Defines class TestRootTree.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTROOTTREE_H
#define TESTROOTTREE_H

#include "IApplicationTest.h"
#include "ISample.h"
#include "OutputData.h"
#include "GISASSimulation.h"

//! Using ROOT trees to read/write data from/to disk.

class TestRootTree : public IApplicationTest
{
public:
    TestRootTree() : mp_sample(0), mp_simulation(0), mp_data(0) {}
    virtual ~TestRootTree()
    {
        delete mp_sample;
        delete mp_simulation;
        delete mp_data;
    }

    class MesoParSet{
    public:
        MesoParSet(double _npR, double _phi, double _alpha)
            : npR(_npR), phi(_phi), alpha(_alpha) {}
        double npR;
        double phi;
        double alpha;
    };

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

    void initializeMesoCrystal
        (double meso_alpha, double meso_phi, double nanopart_radius);

    ISample *mp_sample;
    GISASSimulation *mp_simulation;
    OutputData<double> *mp_data;
};

#endif // TESTROOTTREE_H



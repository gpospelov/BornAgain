// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestRootTree.h 
//! @brief     Defines class TestRootTree.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTROOTTREE_H
#define TESTROOTTREE_H

#include "IFunctionalTest.h"
#include "ISample.h"
#include "OutputData.h"
#include "Simulation.h"

//! Using ROOT trees to read/write data from/to disk.

class TestRootTree : public IFunctionalTest
{
public:
    class MesoParSet{
    public:
        MesoParSet(double _npR, double _phi, double _alpha) : npR(_npR), phi(_phi), alpha(_alpha){}
        double npR;
        double phi;
        double alpha;
    };


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

    ISample *mp_sample;
    Simulation *mp_simulation;
    OutputData<double> *mp_data;
};

#endif // TESTROOTTREE_H

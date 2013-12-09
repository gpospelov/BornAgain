// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFourier.h
//! @brief     Defines class TestFourier.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFOURIER_H_
#define TESTFOURIER_H_

#include "IApplicationTest.h"
#include "OutputData.h"
#include "ISample.h"

class TestFourier : public IApplicationTest
{
public:
    TestFourier();
    virtual ~TestFourier();
    virtual void execute();

private:
    void initializeSample();
    OutputData<double> *mp_intensity_output;
    ISample *mp_sample;
};

#endif /* TESTFOURIER_H_ */



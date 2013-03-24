// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestFormFactor.h 
//! @brief     Defines class TestFormFactor.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTFORMFACTOR_H
#define TESTFORMFACTOR_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FormFactors.h"


class TestFormFactor : public IFunctionalTest
{
public:
    TestFormFactor();
    ~TestFormFactor();
    virtual void execute();
    void draw();

private:
    OutputData<double> *mp_intensity_output;
    FormFactorCylinder m_ff;
};


#endif // TESTFORMFACTOR_H

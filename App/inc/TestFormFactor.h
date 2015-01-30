// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFormFactor.h
//! @brief     Defines class TestFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFORMFACTOR_H
#define TESTFORMFACTOR_H

#include "IApplicationTest.h"
#include "OutputData.h"
#include "FormFactors.h"

class TestFormFactor : public IApplicationTest
{
public:
    TestFormFactor();
    ~TestFormFactor();
    virtual void execute();
    void draw(), draw4();

private:
    OutputData<double> *mp_intensity_output;
    FormFactorCylinder m_ff;
};

#endif // TESTFORMFACTOR_H



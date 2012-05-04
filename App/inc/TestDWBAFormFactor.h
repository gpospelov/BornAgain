/*
 * TestDWBAFormFactor.h
 *
 *  Created on: May 2, 2012
 *      Author: herck
 */

#ifndef TESTDWBAFORMFACTOR_H_
#define TESTDWBAFORMFACTOR_H_

#include "IAlgorithm.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"
#include "DWBAFormFactor.h"

class TestDWBAFormFactor : public IAlgorithm
{
public:
    TestDWBAFormFactor();
    virtual ~TestDWBAFormFactor();
    virtual void execute();
    void draw();

private:
    OutputData<double> *mp_intensity_output;
    DWBAFormFactor m_dwba_ff;
};

complex_t reflection_fresnel(double alpha_i);
complex_t transmission_fresnel(double alpha_i);

#endif /* TESTDWBAFORMFACTOR_H_ */

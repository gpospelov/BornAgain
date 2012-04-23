#ifndef TESTFORMFACTOR_H
#define TESTFORMFACTOR_H

#include "IAlgorithm.h"
#include "OutputData.h"
#include "FormFactorCylinder.h"

class TestFormFactor : public IAlgorithm
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

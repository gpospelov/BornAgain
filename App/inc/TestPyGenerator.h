#ifndef TESTPYGENERATOR_H
#define TESTPYGENERATOR_H
#include "IApplicationTest.h"
#include "PyGenVisitor.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"

class MultiLayer;

class TestPyGenerator : public IApplicationTest
{
public:
    TestPyGenerator();
    virtual ~TestPyGenerator(){}
    bool testPythonScript(Simulation *simulation);
    virtual void execute();

private:
    PyGenVisitor visitor;
    Simulation *makeSimulation();
    MultiLayer *makeSample();
    Simulation *m_simulation;
    MultiLayer *m_sample;
    const OutputData<double> *m_reference_data;
    const OutputData<double> *m_simulated_data;


};

#endif //


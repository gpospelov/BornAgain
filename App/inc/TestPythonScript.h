#ifndef TESTPYTHONSCRIPT_H
#define TESTPYTHONSCRIPT_H
#include "IApplicationTest.h"
#include "SimulationRegistry.h"

class TestPythonScript : public IApplicationTest
{
public:
    TestPythonScript();
    virtual ~TestPythonScript(){}
    virtual bool compareSamples();

private:
    Simulation *simulation;


};

#endif // TESTPYTHONSCRIPT_H

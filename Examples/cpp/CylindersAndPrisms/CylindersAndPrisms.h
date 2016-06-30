#ifndef CYLINDERSANDPRISMS_H_
#define CYLINDERSANDPRISMS_H_

// Mixture of cylinders and prisms without interference (IsGISAXS example ex-1)
#include "OutputData.h"
#include "Simulation.h"
#include "ISample.h"

class CylindersAndPrismsExample
{
public:
    CylindersAndPrismsExample();
    virtual ~CylindersAndPrismsExample() { delete m_sample; delete m_simulation; delete m_result; }

    void runSimulation();
    void drawResult();

protected:
    void initSample();
    void initSimulation();

private:
    OutputData<double> *m_result;
    Simulation *m_simulation;
    MultiLayer *m_sample;
};

#endif /* CYLINDERSANDPRISMS_H_ */

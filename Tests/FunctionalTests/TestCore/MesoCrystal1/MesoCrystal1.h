#ifndef _TESTMESOCRYSTAL1_H
#define _TESTMESOCRYSTAL1_H

#include "ISampleBuilder.h"
#include "OutputData.h"
#include <string>
#include <vector>

class ISample;
class Simulation;
#include "OutputData.h"


namespace FunctionalTests {

//! functional test: mesocrystal simulation

class MesoCrystal1
{
public:
    MesoCrystal1();
    ~MesoCrystal1();

    //! run fitting
    int run();

private:

    Simulation *createSimulation();
    double getDifference(OutputData<double> *result, const OutputData<double> *reference);

    std::string m_test_name;
    std::string m_test_description;
};

}


#endif

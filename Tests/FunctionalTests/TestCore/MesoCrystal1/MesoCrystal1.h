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
    ~MesoCrystal1() { delete m_result; delete m_reference;}

    //! run fitting
    void run(const std::string &path_to_data = std::string());
    int analyseResults();

private:
    Simulation *createSimulation();

    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;
    OutputData<double> *m_reference;
};

}


#endif

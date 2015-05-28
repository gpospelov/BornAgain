#ifndef _TESTFIT02_H
#define _TESTFIT02_H

#include "ISampleBuilder.h"
#include "OutputData.h"
#include <string>
#include <vector>

class ISample;
class GISASSimulation;

namespace FunctionalTests {

//! functional test: fitting using sample builder
//
//! This test shows how to use SampleBuilder class for constructing the sample
//! and running fitting.

class TestFit02
{
public:
    TestFit02();
    ~TestFit02(){}

    //! run fitting
    int run();

private:

    GISASSimulation *createSimulation();
    OutputData<double> *createRealData(GISASSimulation *simulation);

    std::string m_test_name;
    std::string m_test_description;
};

}


#endif

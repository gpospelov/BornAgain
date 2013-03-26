#ifndef FUNCTIONALTESTS_ISGISAXS08_H
#define FUNCTIONALTESTS_ISGISAXS08_H


#include <string>
#include "OutputData.h"

class MultiLayer;
class Simulation;

namespace FunctionalTests {

class IsGISAXS08
{
 public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_2DDL, kTest_2DDL2, kNumberOfTests };

    IsGISAXS08();
    ~IsGISAXS08();

    void run2DDL(), run2DDL2();
    int analyseResults();

    const OutputData<double> *getOutputData(size_t ntest=0) { return m_results.at(ntest); }

 private:
    std::string m_name;
    std::string m_description;
    std::string m_path;
    results_t m_results;
};


}



#endif

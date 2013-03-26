#ifndef FUNCTIONALTESTS_ISGISAXS09_H
#define FUNCTIONALTESTS_ISGISAXS09_H

#include <string>
#include "OutputData.h"

class MultiLayer;
class Simulation;

namespace FunctionalTests {

class IsGISAXS09
{
 public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_Z0, kTest_Z45, kNumberOfTests };

    IsGISAXS09();
    ~IsGISAXS09();

    void runpyramidZ0(), runpyramidZ45();
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

#ifndef FUNCTIONALTESTS_ISGISAXS03_H
#define FUNCTIONALTESTS_ISGISAXS03_H

#include <string>
#include "OutputData.h"


namespace FunctionalTests {

class IsGISAXS03
{
 public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_DWBA, kTest_BA, kTest_BASize, kNumberOfTests };

    IsGISAXS03();
    ~IsGISAXS03();

    void runDWBA() , runBA(), runBA_Size();
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

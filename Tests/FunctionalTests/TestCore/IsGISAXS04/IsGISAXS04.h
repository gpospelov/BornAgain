#ifndef FUNCTIONALTESTS_ISGISAXS04_H
#define FUNCTIONALTESTS_ISGISAXS04_H

#include <string>
#include "OutputData.h"

class MultiLayer;


namespace FunctionalTests {

class IsGISAXS04
{
 public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_1DDL, kTest_2DDL, kNumberOfTests };

    IsGISAXS04();
    ~IsGISAXS04();

    void run1DDL(), run2DDL();
    int analyseResults(const std::string &path_to_data = std::string());

    const OutputData<double> *getOutputData(size_t ntest=0) { return m_results.at(ntest); }

 private:
    std::string m_name;
    std::string m_description;
    results_t m_results;
};


}


#endif

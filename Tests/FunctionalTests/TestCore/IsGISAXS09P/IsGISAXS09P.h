#ifndef FUNCTIONALTESTS_ISGISAXS09P_H
#define FUNCTIONALTESTS_ISGISAXS09P_H

#include "ISampleBuilder.h"
#include <string>
#include "OutputData.h"


namespace FunctionalTests {

class IsGISAXS09
{
 public:
    IsGISAXS09();
    ~IsGISAXS09() { delete m_result; delete m_reference; }
    void run(const std::string &path_to_data = std::string());
    int analyseResults();
//    const OutputData<double> *getOutputData() { return m_result;}
 private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;
    OutputData<double> *m_reference;
};

}

#endif

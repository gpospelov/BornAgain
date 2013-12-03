#ifndef FUNCTIONALTESTS_ISGISAXS06L2_H
#define FUNCTIONALTESTS_ISGISAXS06L2_H

#include <string>
#include "OutputData.h"
#include "ISampleBuilder.h"

namespace FunctionalTests {

class IsGISAXS06L2
{
 public:
    IsGISAXS06L2();
    ~IsGISAXS06L2() { delete m_result; delete m_reference; }
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

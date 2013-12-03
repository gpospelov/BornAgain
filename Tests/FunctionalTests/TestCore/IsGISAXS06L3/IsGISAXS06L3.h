#ifndef FUNCTIONALTESTS_ISGISAXS06L3_H
#define FUNCTIONALTESTS_ISGISAXS06L3_H

#include <string>
#include "OutputData.h"
#include "ISampleBuilder.h"

namespace FunctionalTests {

class IsGISAXS06L3
{
 public:
    IsGISAXS06L3();
    ~IsGISAXS06L3() { delete m_result; delete m_reference; }
    void run(const std::string &path_to_data = std::string());
    int analyseResults();
 private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;
    OutputData<double> *m_reference;
};

}

#endif

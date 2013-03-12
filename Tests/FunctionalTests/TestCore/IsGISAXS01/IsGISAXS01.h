#ifndef FUNCTIONALTESTS_ISGISAXS01_H
#define FUNCTIONALTESTS_ISGISAXS01_H


#include <string>
#include "OutputData.h"

namespace FunctionalTests {

class IsGISAXS01
{
public:
    IsGISAXS01();
    ~IsGISAXS01() { delete m_result; }
    void run();
    int analyseResults();
    const OutputData<double> *getOutputData() { return m_result;}
private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;
};

}

#endif

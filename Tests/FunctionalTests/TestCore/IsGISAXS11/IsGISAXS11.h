#ifndef FUNCTIONALTESTS_ISGISAXS11_H
#define FUNCTIONALTESTS_ISGISAXS11_H


#include <string>
#include "OutputData.h"


namespace FunctionalTests {

class IsGISAXS11
{
public :
    IsGISAXS11();
    ~IsGISAXS11() { delete m_result; }

    void run();
    int analyseResults();

    const OutputData<double> *getOutputData() { return m_result; }
 private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;
};

}

#endif

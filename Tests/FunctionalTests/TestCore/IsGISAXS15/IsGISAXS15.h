#ifndef FUNCTIONALTESTS_ISGISAXS15_H
#define FUNCTIONALTESTS_ISGISAXS15_H


#include <string>
#include "OutputData.h"


namespace FunctionalTests {

class IsGISAXS15
{
public :
    IsGISAXS15();
    ~IsGISAXS15() { delete m_result; }

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

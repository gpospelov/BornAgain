#ifndef FUNCTIONALTESTS_ISGISAXS02_H
#define FUNCTIONALTESTS_ISGISAXS02_H

#include <string>
#include "OutputData.h"


namespace FunctionalTests {

class IsGISAXS02
{
public :
    IsGISAXS02();
    ~IsGISAXS02() { delete m_result; }
    void run();
    int analyseResults(const std::string &path_to_data = std::string());
    const OutputData<double> *getOutputData() { return m_result; }
 private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;
};

}

#endif

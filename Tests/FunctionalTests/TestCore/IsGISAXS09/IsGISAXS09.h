#ifndef FUNCTIONALTESTS_ISGISAXS09_H
#define FUNCTIONALTESTS_ISGISAXS09_H

#include <string>
#include "OutputData.h"

class MultiLayer;
class GISASExperiment;

namespace FunctionalTests {

class IsGISAXS09
{
public:
    IsGISAXS09();
    ~IsGISAXS09() { delete m_result; }
    void run();
    int analyseResults();
    const OutputData<double> *getOutputData() { return m_result;}
private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;

   // SafePointerVector<OutputData<double> > m_results;


};


}



#endif

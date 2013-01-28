#ifndef FUNCTIONALTESTS_ISGISAXS011_H
#define FUNCTIONALTESTS_ISGISAXS011_H


#include <string>
#include "OutputData.h"

class MultiLayer;
class GISASExperiment;

namespace FunctionalTests {

class IsGISAXS011
{
public :
  IsGISAXS011();
  ~IsGISAXS011() { delete m_result; }
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

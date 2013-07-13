#ifndef FUNCTIONALTESTS_ISGISAXS06_H
#define FUNCTIONALTESTS_ISGISAXS06_H

#include <string>
#include "OutputData.h"

#include "ISampleBuilder.h"
#include "Simulation.h"

class MultiLayer;


namespace FunctionalTests {

class IsGISAXS06
{
 public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_Lattice, kTest_Centered, kTest_Rotated,  kTest_Variants, kNumberOfTests };

    IsGISAXS06();
    ~IsGISAXS06();

    void runlattice(), runcentered(), runrotated(), runvariants();
    int analyseResults(const std::string &path_to_data = std::string());

    const OutputData<double> *getOutputData(size_t ntest=0) { return m_results.at(ntest); }

 private:

    std::string m_name;
    std::string m_description;
    std::string m_path;
    results_t m_results;
    Simulation m_simulation;
};


}


#endif

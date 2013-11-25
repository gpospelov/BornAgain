#ifndef _TESTPOLARIZEDDWBAZEROMAG_H
#define _TESTPOLARIZEDDWBAZEROMAG_H

#include "ISampleBuilder.h"
#include "OutputData.h"
#include <string>
#include <vector>

class ISample;
class Simulation;
#include "OutputData.h"


namespace FunctionalTests {

//! functional test: Polarized DWBA Zero magnetic field  simulation

class PolarizedDWBAZeroMag
{
public:
    PolarizedDWBAZeroMag();
    ~PolarizedDWBAZeroMag() { delete m_result; delete m_reference;}

    //! run fitting
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

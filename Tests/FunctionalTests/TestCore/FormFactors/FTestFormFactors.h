#ifndef FUNCTIONALTESTS_FTESTFORMFACTORS_H
#define FUNCTIONALTESTS_FTESTFORMFACTORS_H

#include <string>
//#include <map>
#include "OutputData.h"
#include "IFormFactor.h"


namespace FunctionalTests {

class FTestFormFactors
{
 public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_Cylinder, kTest_Box, kTest_Cone, kTest_Cone6,
                        kTest_FullSphere, kTest_Parallelepiped,
                        kTest_Prism3, kTest_Prism6,
                        kTest_Pyramid, kTest_Sphere,
                        kTest_Tetrahedron, kTest_Cuboctahedron,
                        kTest_AnisoPyramid, kTest_Ellipscyl,
                        kTest_FullSpheroid, kTest_Spheroid, kTest_HemiEllipsoid,
                        kNumberOfTests };

    FTestFormFactors();
    ~FTestFormFactors();

    void run(IFormFactor* p_form_factor = 0);
    int analyseResults(const std::string &path_to_data = std::string());
    const OutputData<double> *getOutputData(size_t ntest=0)
          { return m_results.at(ntest); }

 private:
    std::string m_name;
    std::string m_description;
    results_t m_results;

 protected:
    IFormFactor* mp_form_factor;

};

}

#endif

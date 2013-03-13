#ifndef FUNCTIONALTESTS_ISGISAXS06_H
#define FUNCTIONALTESTS_ISGISAXS06_H

#include <string>
#include "OutputData.h"

#include "ISampleBuilder.h"

class MultiLayer;
class Simulation;


namespace FunctionalTests {

class IsGISAXS06
{
public:
    typedef std::vector<OutputData<double> *> results_t;
    enum keys_results { kTest_Lattice, kTest_Centered, kTest_Rotated,  kTest_Variants, kNumberOfTests };

    IsGISAXS06();
    ~IsGISAXS06();

    void runlattice(), runcentered(), runrotated(), runvariants();
    int analyseResults();

    const OutputData<double> *getOutputData(size_t ntest=0) { return m_results.at(ntest); }

private:

    class LatticeVariantBuilder : public ISampleBuilder {
    public:
        LatticeVariantBuilder() : m_xi(0.0) {}
        virtual ~LatticeVariantBuilder() {}

        virtual ISample *buildSample() const;

        void setXi(double xi) { m_xi = xi; }
    private:
        double m_xi;
    };

    std::string m_name;
    std::string m_description;
    LatticeVariantBuilder m_builder;
    std::string m_path;

    results_t m_results;
};


}


#endif

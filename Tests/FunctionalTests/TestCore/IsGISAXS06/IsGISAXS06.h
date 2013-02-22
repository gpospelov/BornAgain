#ifndef FUNCTIONALTESTS_ISGISAXS06_H
#define FUNCTIONALTESTS_ISGISAXS06_H

#include <string>
#include "OutputData.h"

#include "ISampleBuilder.h"

class MultiLayer;
class GISASExperiment;


namespace FunctionalTests {

class IsGISAXS06
{
public:
    IsGISAXS06();
    ~IsGISAXS06() { delete m_result; }
    //void run();
    void runlattice(), runcentered(), runrotated(), runvariants();
    int analyseResults();
    const OutputData<double> *getOutputData() { return m_result;}
private:
    std::string m_name;
    std::string m_description;
    OutputData<double> *m_result;

    struct CompareStruct
    {
        CompareStruct(std::string _isginame, std::string _thisname, std::string _descr) : isginame(_isginame), thisname(_thisname), descr(_descr){}
        std::string isginame;
        std::string thisname;
        std::string descr;
    };

    class LatticeVariantBuilder : public ISampleBuilder {
    public:
        LatticeVariantBuilder() : m_xi(0.0) {}
        virtual ~LatticeVariantBuilder() {}

        virtual ISample *buildSample() const;

        void setXi(double xi) { m_xi = xi; }
    private:
        double m_xi;
    };
    LatticeVariantBuilder m_builder;
    std::string m_data_path;
};


}


#endif

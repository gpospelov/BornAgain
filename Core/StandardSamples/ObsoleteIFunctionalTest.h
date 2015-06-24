#ifndef OBSOLETEIFUNCTIONALTEST_H
#define OBSOLETEIFUNCTIONALTEST_H


#include "GISASSimulation.h"
#include <boost/shared_ptr.hpp>
#include <string>


class BA_CORE_API_ ObsoleteIFunctionalTest
{
public:
    virtual ~ObsoleteIFunctionalTest() {}
    virtual void runTest() =0;
};


class BA_CORE_API_ ObsoleteFunctionalTestInfo
{
public:
    ObsoleteFunctionalTestInfo()
        : m_threshold(0) {  }

    ObsoleteFunctionalTestInfo(const std::string &name, const std::string &description,
              const std::string &reference, double threshold, bool normalize = false )
        : m_name(name)
        , m_description(description)
        , m_reference_file(reference)
        , m_threshold(threshold)
        , m_normalize(normalize)
    {  }

    std::string m_name;
    std::string m_description;
    std::string m_reference_file;
    double m_threshold;
    bool m_normalize;
};


class BA_CORE_API_ ObsoleteFunctionalTest : public ObsoleteIFunctionalTest
{
public:
    enum ETestResult { SUCCESS, FAILED};

    ObsoleteFunctionalTest(const ObsoleteFunctionalTestInfo &info);
    ~ObsoleteFunctionalTest();

    GISASSimulation *getSimulation() { return m_simulation; }
    const OutputData<double> *getReference() const { return m_reference; }
    std::string getName() const { return m_info.m_name; }
    std::string getDescription() const { return m_info.m_description; }
    void runTest();
    int analyseResults();

private:
    ObsoleteFunctionalTestInfo m_info;
    GISASSimulation *m_simulation;
    OutputData<double> *m_reference;
};

#endif

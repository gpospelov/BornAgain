#ifndef FUNCTIONALTESTFACTORY_H
#define FUNCTIONALTESTFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FunctionalTestFactory.h
//! @brief  Definition of factory class to hold collection of functional tests
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <string>
#include <map>
#include "ISingleton.h"
#include "IFactory.h"
#include "IFunctionalTest.h"


class TBenchmark;

class FunctionalTestFactory : public ISingleton<FunctionalTestFactory>, public IFactory<std::string, IFunctionalTest>
//before it was template class ISingleton<IFactory<std::string, IFunctionalTest> >;
{
public:
    typedef DescriptionMap_t::iterator iterator;
    typedef DescriptionMap_t::const_iterator const_iterator;

    FunctionalTestFactory();
    virtual ~FunctionalTestFactory();

    //! execute specified test
    void execute(std::string name);

    //! profile specified test
    void profile(std::string name);

    //! execute all registered tests
    void execute_all();

    //! print names of registered tests
    void print_testnames();

    //! print benchmark summary
    void print_benchmarks();

    //! return vector of registered test names and they desciptions map["name"]="description"
    DescriptionMap_t getDescriptionMap();

    iterator begin() { return m_descriptions.begin(); }
    iterator end() { return m_descriptions.end(); }

private:
    TBenchmark *m_benchmark;
};

#endif // FUNCTIONALTESTFACTORY_H

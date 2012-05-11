#ifndef IFUNCTIONALTEST_H
#define IFUNCTIONALTEST_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFunctionalTest.h
//! @brief  Defenition of base class for functional tests
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include <string>


//- -------------------------------------------------------------------
//! @class IFunctionalTest
//! @brief Base class for sophisticated functional tests.
//! See also FunctionalTestFactory
//- -------------------------------------------------------------------
class IFunctionalTest
{
public:
    IFunctionalTest();
    IFunctionalTest(const std::string &name) : m_name(name) {}
    IFunctionalTest(const std::string &name, const std::string &descr) : m_name(name), m_description(descr) {}
    virtual ~IFunctionalTest(){}

    virtual void execute();

    //! get name of test
    std::string getName() const { return m_name; }

    //! set name of test
    void setName(const std::string name) { m_name = name; }

    //! get short description
    std::string getDescription() const { return m_description; }

    //! set short description of test
    void setDescription(const std::string description) { m_description = description; }

protected:
    std::string m_name;
    std::string m_description;

};

#endif // IFUNCTIONALTEST_H

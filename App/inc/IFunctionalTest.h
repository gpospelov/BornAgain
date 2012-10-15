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
#include "INamed.h"

class ProgramOptions;

//- -------------------------------------------------------------------
//! @class IFunctionalTest
//! @brief Base class for sophisticated functional tests.
//! See also FunctionalTestFactory
//- -------------------------------------------------------------------
class IFunctionalTest : public INamed
{
public:
    IFunctionalTest() : mp_options(0) {}
    IFunctionalTest(const std::string &name) : INamed(name), mp_options(0) {}
    IFunctionalTest(const std::string &name, const std::string &title) : INamed(name, title), mp_options(0) {}
    virtual ~IFunctionalTest(){}

    virtual void initialise(ProgramOptions *p_options) {
        mp_options = p_options;
    }
    virtual void execute();
    virtual void finalise() {}
protected:
    ProgramOptions *mp_options;
};

#endif // IFUNCTIONALTEST_H

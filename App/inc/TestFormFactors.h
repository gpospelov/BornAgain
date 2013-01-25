#ifndef TESTFORMFACTORS_H
#define TESTFORMFACTORS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFormFactors.h
//! @brief  Definition of TestFormFactors class for FormFactors validation
//! @author Scientific Computing Group at FRM II
//! @date   Jun 28, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"


//- -------------------------------------------------------------------
//! @class TestFormFactors
//! @brief Comparison with FormFactors ex-1: mean forfactor cylinder and prism
//- -------------------------------------------------------------------
class TestFormFactors : public IFunctionalTest
{
public:
    TestFormFactors(){}
    virtual ~TestFormFactors(){}

    virtual void execute();
    virtual void finalise();
private:
    std::string m_data_path;
};

#endif // TESTFORMFACTORS_H

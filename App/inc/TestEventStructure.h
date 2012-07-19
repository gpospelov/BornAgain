#ifndef TESTEVENTSTRUCTURE_H
#define TESTEVENTSTRUCTURE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestEventStructure.h
//! @brief  Definition of TestEventStructure class for writing in root files
//! @author Scientific Computing Group at FRM II
//! @date   19.07.2012


#include "TObject.h"
#include <vector>

//- -------------------------------------------------------------------
//! @class TestEventStructure
//! @brief test structure to save in the root file
//- -------------------------------------------------------------------
class TestEventStructure
{
public:
    TestEventStructure();
    ~TestEventStructure(){}

    double alpha_i;
    double alpha_f;
    std::vector<double > vec;
    //OutputData<double> m_data;

ClassDef(TestEventStructure,1)
};



#endif // TESTEVENTSTRUCTURE_H

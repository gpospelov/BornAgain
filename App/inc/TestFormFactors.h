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
//! @file   TESTFORMFACTORS.h
//! @brief  Definition of FormFactor class
//! @author Scientific Computing Group at FRM II
//! @date   Oct 1, 2012

#include "IFunctionalTest.h"

//- -------------------------------------------------------------------
//! @class TestFormFactors
//! @brief Comparison with IsGISAXS ex-12:
//- -------------------------------------------------------------------
class TestFormFactors : public IFunctionalTest
{
public:
 TestFormFactors(){}
 virtual ~TestFormFactors(){}

    virtual void execute();
    virtual void finalise();

 //std::string m_results;
 //void clear();
// private:
 //std::vector<OutputData<double> *> m_results;
/*
private:
    // structure to holed info over several compare cases
    struct CompareStruct
    {
        //CompareStruct(std::string _isginame, std::string _thisname, std::string _descr) : isginame(_isginame), thisname(_thisname), descr(_descr){}
        //  std::string isginame;
        //std::string thisname;
        //std::string descr;

    };

    std::string m_data_path;
  */
};

#endif // TESTFORMFACTORS_H

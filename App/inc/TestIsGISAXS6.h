#ifndef TESTISGISAXS6_H_
#define TESTISGISAXS6_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS6.h
//! @brief  Definition of TestIsGISAXS6 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   Jan 22, 2013

#include "IFunctionalTest.h"

//- -------------------------------------------------------------------
//! @class TestIsGISAXS6
//! @brief Comparison with IsGISAXS ex-6: cylinders with regular lattice
//! interference functions
//- -------------------------------------------------------------------
class TestIsGISAXS6 : public IFunctionalTest
{
public:
    TestIsGISAXS6();
    virtual ~TestIsGISAXS6(){}

    virtual void execute();
    virtual void finalise();
private:
    // structure to hold info over several compare cases
    struct CompareStruct
    {
        CompareStruct(std::string _isginame, std::string _thisname, std::string _descr) : isginame(_isginame), thisname(_thisname), descr(_descr){}
        std::string isginame;
        std::string thisname;
        std::string descr;
    };

    std::string m_data_path;
};


#endif /* TESTISGISAXS6_H_ */

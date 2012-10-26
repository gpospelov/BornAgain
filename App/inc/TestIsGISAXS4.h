#ifndef TESTISGISAXS4_H_
#define TESTISGISAXS4_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS4.h
//! @brief  Definition of TestIsGISAXS4 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   Oct 17, 2012

#include "IFunctionalTest.h"

//- -------------------------------------------------------------------
//! @class TestIsGISAXS4
//! @brief Comparison with IsGISAXS ex-4: cylinder with interference 1DDL or 2DDL
//- -------------------------------------------------------------------
class TestIsGISAXS4 : public IFunctionalTest
{
public:
    TestIsGISAXS4();
    virtual ~TestIsGISAXS4(){}

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


#endif /* TESTISGISAXS4_H_ */

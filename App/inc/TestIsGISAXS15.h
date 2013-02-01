#ifndef TESTISGISAXS15_H_
#define TESTISGISAXS15_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS15.h
//! @brief  Definition of TestIsGISAXS15 functional test
//! @author Scientific Computing Group at FRM II
//! @date   Jan 17, 2013

#include "IFunctionalTest.h"

//- -------------------------------------------------------------------
//! @class TestIsGISAXS15
//! @brief Comparison with IsGISAXS ex-15: Size-Spacing Correlation Approximation
//- -------------------------------------------------------------------
class TestIsGISAXS15 : public IFunctionalTest
{
public:
    TestIsGISAXS15();
    virtual ~TestIsGISAXS15(){}

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


#endif /* TESTISGISAXS15_H_ */

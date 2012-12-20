#ifndef TESTISGISAXS7_H_
#define TESTISGISAXS7_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS7.h
//! @brief  Definition of TestIsGISAXS7 class for IsGISAXS evaluation
//! @author Scientific Computing Group at FRM II
//! @date   Dec 20, 2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

#include <string>

//- -------------------------------------------------------------------
//! @class TestIsGISAXS7
//! @brief Comparison with IsGISAXS ex-7: morphology file
//- -------------------------------------------------------------------
class TestIsGISAXS7 : public IFunctionalTest
{
public:
    TestIsGISAXS7();
    virtual ~TestIsGISAXS7(){}
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


#endif /* TESTISGISAXS7_H_ */

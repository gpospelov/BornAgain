#ifndef TESTISGISAXS3_H_
#define TESTISGISAXS3_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS3.h
//! @brief  Definition of TestIsGISAXS3 class for IsGISAXS validation
//! @author herk
//! @date   02.05.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

#include <string>

//- -------------------------------------------------------------------
//! @class TestIsGISAXS3
//! @brief Comparison with IsGISAXS ex-3: cylinder on top of substrate
//- -------------------------------------------------------------------
class TestIsGISAXS3 : public IFunctionalTest
{
public:
    TestIsGISAXS3();
    virtual ~TestIsGISAXS3(){}
    virtual void execute();
    virtual void finalise();

private:
    // structure to holed info over several compare cases
    struct CompareStruct
    {
        CompareStruct(std::string _isginame, std::string _thisname, std::string _descr) : isginame(_isginame), thisname(_thisname), descr(_descr){}
        std::string isginame;
        std::string thisname;
        std::string descr;
    };

    std::string m_data_path;
};
#endif /* TESTISGISAXS3_H_ */

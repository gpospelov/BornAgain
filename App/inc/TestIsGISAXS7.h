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
//!
//! This functional test will generate an output that is quite different
//! from the one originating from IsGISAXS. There are 4 reasons for this:
//! 1) IsGISAXS uses a polarization factor for x-rays, which is not yet
//!    implemented in our framework
//! 2) IsGISAXS neglects the scattering length density in case of a
//!    morphology file with 'morif' option in input file
//! 3) IsGISAXS outputs only the coherent part in the *.ima file
//!    The diffuse part can be seen in the windows version, but contains
//!    bugs (compare the commented diffuse calculation in
//!    IsGISAXSMorphologyFileStrategy.cpp with our actual implementation)
//! 4) The morphology file contains 10 particles, yet it says "Number of particles: 9"
//!    This causes only nine particle descriptions to be read in IsGISASXS
//!
//! The last three of these can be considered IsGISAXS bugs
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

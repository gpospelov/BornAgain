#ifndef TESTISGISAXS12_H
#define TESTISGISAXS12_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestIsGISAXS12.h
//! @brief  Definition of TestIsGISAXS12 class for IsGISAXS validation
//! @author Scientific Computing Group at FRM II
//! @date   08.11.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
#include "ISampleBuilder.h"

#include <string>

//- -------------------------------------------------------------------
//! @class TestIsGISAXS12
//! @brief Comparison with IsGISAXS ex-12: constrained fit example
//- -------------------------------------------------------------------
class TestIsGISAXS12 : public IFunctionalTest
{
public:
    TestIsGISAXS12();
    virtual void execute();
    virtual void finalise();

    //! builds sample for fitter testing
    class TestSampleBuilder : public ISampleBuilder
    {
    public:
        TestSampleBuilder();
        virtual ~TestSampleBuilder(){}

        virtual ISample *buildSample() const;
    protected:
        //! initialize pool parameters, i.e. register some of class members for later access via parameter pool (to overload)
        virtual void init_parameters();
    };


private:

    void read_isgisaxs_datfile(const std::string &filename);

    std::string m_data_path;
};


#endif // TESTISGISAXS12_H

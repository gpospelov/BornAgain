#ifndef TESTDIFFUSEREFLECTION_H
#define TESTDIFFUSEREFLECTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestDiffuseReflection.h
//! @brief  Test of diffusse (incoherent) reflection from rough multilayer in DWBA.
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "TH2D.h"

class MultiLayer;


//- -------------------------------------------------------------------
//! @class TestDiffuseReflection
//! @brief Test diffuse (off-specular) reflection from multilayer
//- -------------------------------------------------------------------
class TestDiffuseReflection : public IFunctionalTest
{
public:
    TestDiffuseReflection();

    void execute();

    void draw();

private:
    MultiLayer *m_sample; //!< pointer to multilayer sample
    OutputData<double  > *m_data_spec; //!< specular reflectivity
    OutputData<double  > *m_data_offspec; //!< off specular reflectivity

    double m_alphaMin; //! min alpha value
    double m_alphaMax; //! max alpha value
    int m_npoints;     //! number of points in range [m_alphaMin, m_alphaMax]

};


#endif // TESTDIFFUSESCATTERING_H

// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestFresnelCoeff.h
//! @brief  Definition of TestFresnelCoeff class for tests of Fresnel coeffs
//! @author Scientific Computing Group at FRM II
//! @date   02.05.2012
#ifndef TESTFRESNELCOEFF_H
#define TESTFRESNELCOEFF_H

#include "IAlgorithm.h"
#include "OpticalFresnel.h"
#include "MultiLayer.h"


class TestFresnelCoeff : public IAlgorithm
{
public:
    TestFresnelCoeff();

    class MyData {
    public:
        double alpha_i;
        OpticalFresnel::MultiLayerCoeff_t coeffs;
    };
    typedef std::vector<MyData > MyDataSet_t;

    void execute();
    void Draw(const MultiLayer &sample,  const MyDataSet_t &data);



private:

};


#endif // TESTFRESNELCOEFF_H

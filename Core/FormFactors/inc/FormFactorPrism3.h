#ifndef FORMFACTORPRISM3_H_
#define FORMFACTORPRISM3_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorPrism3.h
//! @brief  Definition of FormFactorPrism3
//! @author Scientific Computing Group at FRM II
//! @date   Jun 27, 2012

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"


class FormFactorPrism3 : public IFormFactorBorn
{
public:
    FormFactorPrism3(double height, double half_side);
    ~FormFactorPrism3();
    virtual FormFactorPrism3 *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_height;
    double m_half_side;    
    double m_root3; // Cached value of square root of 3
};


#endif /* FORMFACTORPRISM3_H_ */

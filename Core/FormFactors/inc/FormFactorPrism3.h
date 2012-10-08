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

#include "IFormFactor.h"
#include "IStochasticParameter.h"


class FormFactorPrism3 : public IFormFactorBorn
{
public:
    FormFactorPrism3(double height, double half_side);
//    FormFactorPrism3(StochasticParameter<double> *p_height, StochasticParameter<double> *p_half_side);
    ~FormFactorPrism3();
    virtual FormFactorPrism3 *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }


protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorPrism3(const FormFactorPrism3 &);
    FormFactorPrism3 &operator=(const FormFactorPrism3 &);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_height;
    double m_half_side;
//    StochasticParameter<double> *mp_height;
//    StochasticParameter<double> *mp_half_side;
    // Cached value of square root of 3
    double m_root3;
};


#endif /* FORMFACTORPRISM3_H_ */

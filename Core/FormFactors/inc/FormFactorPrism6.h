#ifndef FORMFACTORPRISM6_H
#define FORMFACTORPRISM6_H// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorPris6.h
//! @brief  Definition of FormFactorPrism6
//! @author Scientific Computing Group at FRM II
//! @date   Jun 27, 2012

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"


class FormFactorPrism6 : public IFormFactorBorn
{
public:
    FormFactorPrism6(double height, double half_side);
//    FormFactorPrism6(StochasticParameter<double> *p_height, StochasticParameter<double> *p_half_side);
    ~FormFactorPrism6();
    virtual FormFactorPrism6 *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }


protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorPrism6(const FormFactorPrism6 &);
    FormFactorPrism6 &operator=(const FormFactorPrism6 &);

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

#endif // FORMFACTORPRISM6_H

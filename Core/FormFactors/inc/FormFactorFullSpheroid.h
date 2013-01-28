#ifndef FORMFACTORFULLSPHEROID_H
#define FORMFACTORFULLSPHEROID_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorFullSpheroid.h
//! @brief  Definition of FormFactorFullSpheroid
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"


class FormFactorFullSpheroid : public IFormFactorBorn
{
public:
    FormFactorFullSpheroid(double radius, double height);
    double FullSpheroidIntegral(double Z, void* params) const;
//    FormFactorFullSpheroid(StochasticParameter<double> *p_height, StochasticParameter<double> *p_radius);
    ~FormFactorFullSpheroid();
    virtual FormFactorFullSpheroid *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorFullSpheroid(const FormFactorFullSpheroid &);
    FormFactorFullSpheroid &operator=(const FormFactorFullSpheroid &);


    double evaluate_for_q_real() const;
    complex_t evaluate_for_q_imag() const;
    double FullSpheroidIntegralReal(double Z, void* params) const;
    double FullSpheroidIntegralImaginary(double Z, void* params) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_radius;
    double m_height;
    mutable cvector_t m_q;

};


#endif // FORMFACTORFULLSPHEROID_H

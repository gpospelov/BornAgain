#ifndef FORMFACTORSPHERE_H
#define FORMFACTORSPHERE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorSphere.h
//! @brief  Definition of FormFactorSphere
//! @author Scientific Computing Group at FRM II
//! @date   01.05.2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"


class FormFactorSphere : public IFormFactorBorn
{
public:
    FormFactorSphere(double radius, double height);
    double SphereIntegral(double Z, void* params) const;

    ~FormFactorSphere();
    virtual FormFactorSphere *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorSphere(const FormFactorSphere &);
    FormFactorSphere &operator=(const FormFactorSphere &);



        double evaluate_for_q_real() const;
        complex_t evaluate_for_q_imag() const;
        double SphereIntegralImaginary(double Z, void* params) const;
        double SphereIntegralReal(double Z, void* params) const;

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_height;
    double m_radius;
    mutable cvector_t m_q;
};


#endif // FORMFACTORSPHERE_H

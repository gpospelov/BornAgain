#ifndef FORMFACTORBIGCYLINDER_H_
#define FORMFACTORBIGCYLINDER_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorBigCylinder.h
//! @brief  Definition of FormFactorBigCylinder class
//! @author Scientific Computing Group at FRM II
//! @date   Nov 23, 2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"


class FormFactorBigCylinder : public IFormFactorBorn
{
public:
    FormFactorBigCylinder(double height, double radius);

    ~FormFactorBigCylinder();
    virtual FormFactorBigCylinder *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

    void setBinSize(double bin_size) { m_bin_size = bin_size; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorBigCylinder(const FormFactorBigCylinder &);
    FormFactorBigCylinder &operator=(const FormFactorBigCylinder &);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! approximation to radial function for integration
    double iTilde(double qR) const;

    //! print class
    void print(std::ostream &ostr) const;

//    StochasticParameter<double> *mp_height;
//    StochasticParameter<double> *mp_radius;
    double m_height;
    double m_radius;
    double m_bin_size;
};

#endif /* FORMFACTORBIGCYLINDER_H_ */

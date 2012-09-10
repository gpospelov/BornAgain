#ifndef FORMFACTORGAUSS_H_
#define FORMFACTORGAUSS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorGauss.h
//! @brief  Definition of Gaussian form factor
//! @author Scientific Computing Group at FRM II
//! @date   Aug 30, 2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"


class FormFactorGauss : public IFormFactorBorn
{
public:
    FormFactorGauss(double volume);
    FormFactorGauss(double height, double width);
    ~FormFactorGauss();
    virtual FormFactorGauss *clone() const;

    virtual int getNumberOfStochasticParameters() { return 2; }

protected:
    virtual complex_t evaluate_for_q(cvector_t q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorGauss(const FormFactorGauss &);
    FormFactorGauss &operator=(const FormFactorGauss &);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

//    StochasticParameter<double> *mp_height;
//    StochasticParameter<double> *mp_width;
    double m_height;
    double m_width;
};



#endif /* FORMFACTORGAUSS_H_ */

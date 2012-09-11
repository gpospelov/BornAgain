#ifndef FORMFACTORFULLSPHERE_H_
#define FORMFACTORFULLSPHERE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorFullSphere.h
//! @brief  Definition of FormFactorFullSphere class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 13, 2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"

class FormFactorFullSphere : public IFormFactorBorn
{
public:
    FormFactorFullSphere(double radius);
//    FormFactorFullSphere(StochasticParameter<double> *p_radius);
    ~FormFactorFullSphere();
    virtual FormFactorFullSphere *clone() const;

    virtual int getNumberOfStochasticParameters() { return 1; }

    //! return radius of sphere
    double getRadius() const { return m_radius; }

protected:
    virtual complex_t evaluate_for_q(cvector_t q) const;

private:

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_radius;
//    StochasticParameter<double> *mp_radius;
};


#endif /* FORMFACTORFULLSPHERE_H_ */

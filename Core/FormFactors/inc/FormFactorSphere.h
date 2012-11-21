#ifndef FORMFACTORSPHERE_H
#define FORMFACTORSPHERE_H
//********************************************************************
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
//! @date   03.07.2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"


//- -------------------------------------------------------------------
//! @class FormFactorSphere
//! @brief Form factor of Sphere
//- -------------------------------------------------------------------
class FormFactorSphere : public IFormFactorBorn
{
public:
    //! @brief Sphere constructor
    //! @param height of Sphere
    //! @param radius half of Sphere's base
    //! @param angle in radians between base and facet
    FormFactorSphere(double radius, double height);
//    FormFactorSphere(StochasticParameter<double> *p_height, StochasticParameter<double> *p_half_side, StochasticParameter<double> *p_alpha);
    ~FormFactorSphere();
    virtual FormFactorSphere *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 3; }

    virtual double getHeight() const { return m_radius, m_height; }

protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorSphere(const FormFactorSphere &);
    FormFactorSphere &operator=(const FormFactorSphere &);

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_radius;
    double m_height;


//    StochasticParameter<double> *mp_height;
//    StochasticParameter<double> *mp_half_side;
//    StochasticParameter<double> *mp_alpha;
};

#endif // FORMFACTORSPHERE_H

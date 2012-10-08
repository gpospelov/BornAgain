#ifndef FORMFACTORPARALLELEPIPED_H_
#define FORMFACTORPARALLELEPIPED_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorParallelepiped.h
//! @brief  Definition of FormFactorParallelepiped class
//! @author Scientific Computing Group at FRM II
//! @date   Oct 1, 2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"

class FormFactorParallelepiped : public IFormFactorBorn
{
public:
    FormFactorParallelepiped(double height, double radius);
    ~FormFactorParallelepiped();
    virtual FormFactorParallelepiped *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    //! return radius of parallelepiped
    double getRadius() const { return m_radius; }

    virtual double getVolume() const {
        return 4.0*m_height*m_radius*m_radius;
    }

    virtual double getHeight() const { return m_height; }


protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;

    double m_height;
    double m_radius;
};



#endif /* FORMFACTORPARALLELEPIPED_H_ */

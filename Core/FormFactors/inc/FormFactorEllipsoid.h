#ifndef FORMFACTORELLIPSOID_H
#define FORMFACTORELLIPSOID_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorEllipsoid.h
//! @brief  Definition of FormFactorEllipsoid class
//! @author Scientific Computing Group at FRM II
//! @date   Oct 1, 2012

#include "IFormFactor.h"
#include "IStochasticParameter.h"

class FormFactorEllipsoid : public IFormFactorBorn
{
public:
    FormFactorEllipsoid(double radius, double width, double height );
    ~FormFactorEllipsoid();
    virtual FormFactorEllipsoid *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    //! return radius of Ellipsoid
    double getRadius() const { return m_radius; }

    //! return width of Ellipsoid
    double getWidth() const { return m_width; }

    virtual double getVolume() const {
        return 4.0*m_radius*m_width*m_height;
    }

    virtual double getHeight() const { return m_height; }


protected:
    virtual complex_t evaluate_for_q(const cvector_t &q) const;

private:

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    //! print class
    void print(std::ostream &ostr) const;


    double m_radius;
    double m_width;
    double m_height;


};

#endif // FORMFACTORELLIPSOID_H

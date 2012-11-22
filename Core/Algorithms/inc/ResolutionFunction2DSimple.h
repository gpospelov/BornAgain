#ifndef RESOLUTIONFUNCTION2DSIMPLE_H_
#define RESOLUTIONFUNCTION2DSIMPLE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ResolutionFunction2DSimple.h
//! @brief  Definition of ResolutionFunction2DSimple class
//! @author Scientific Computing Group at FRM II
//! @date   Oct 16, 2012

#include "IResolutionFunction2D.h"

class ResolutionFunction2DSimple : public IResolutionFunction2D
{
public:
    ResolutionFunction2DSimple(double sigma_x, double sigma_y);
    virtual ~ResolutionFunction2DSimple();

    virtual double evaluateCDF(double x, double y) const;

    ResolutionFunction2DSimple *clone() const;

protected:
    virtual void init_parameters();
private:
    //! hiding copy constructor and disabling assignment operator
    ResolutionFunction2DSimple(const ResolutionFunction2DSimple &other);
    ResolutionFunction2DSimple &operator=(const ResolutionFunction2DSimple &);

    double m_sigma_x;
    double m_sigma_y;
};


#endif /* RESOLUTIONFUNCTION2DSIMPLE_H_ */

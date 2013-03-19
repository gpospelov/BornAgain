// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/ResolutionFunction2DSimple.h 
//! @brief     Defines class ResolutionFunction2DSimple.
//
// ************************************************************************** //

#ifndef RESOLUTIONFUNCTION2DSIMPLE_H_
#define RESOLUTIONFUNCTION2DSIMPLE_H_

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

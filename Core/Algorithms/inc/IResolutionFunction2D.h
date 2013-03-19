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
//! @file      Algorithms/IResolutionFunction2D.h 
//! @brief     Defines class IResolutionFunction2D.
//
// ************************************************************************** //

#ifndef IRESOLUTIONFUNCTION2D_H_
#define IRESOLUTIONFUNCTION2D_H_

#include "IParameterized.h"

class IResolutionFunction2D : public IParameterized
{
public:
    virtual ~IResolutionFunction2D() {}

    virtual double evaluateCDF(double x, double y) const=0;
    virtual IResolutionFunction2D *clone() const = 0;
};

#endif /* IRESOLUTIONFUNCTION2D_H_ */

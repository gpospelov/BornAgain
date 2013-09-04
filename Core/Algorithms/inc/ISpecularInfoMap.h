// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ISpecularInfoMap.h
//! @brief     Defines interface ISpecularInfoMap.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISPECULARINFOMAP_H_
#define ISPECULARINFOMAP_H_

#include "ILayerRTCoefficients.h"

class ISpecularInfoMap
{
public:
    virtual ~ISpecularInfoMap() {}

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ILayerRTCoefficients *getCoefficients(
            double alhpa_f, double phi_f) const=0;
};


#endif /* ISPECULARINFOMAP_H_ */

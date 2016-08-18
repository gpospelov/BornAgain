// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ISpecularInfoMap.h
//! @brief     Defines interface ISpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISPECULARINFOMAP_H
#define ISPECULARINFOMAP_H

#include "ILayerRTCoefficients.h"

//! @class ISpecularInfoMap
//! @ingroup algorithms_internal
//! @brief Interface class providing access to the reflection and transmittion coefficients

class BA_CORE_API_ ISpecularInfoMap
{
public:
    ISpecularInfoMap() {}
    virtual ~ISpecularInfoMap() {}

    virtual ISpecularInfoMap* clone() const=0;

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ILayerRTCoefficients* getOutCoefficients(
        double alpha_f, double phi_f, double wavelength) const=0;

    //! Retrieves the amplitude coefficients for the given angles
    virtual const ILayerRTCoefficients* getInCoefficients(
        double alpha_i, double phi_i, double wavelength) const=0;
private:
    // Prevent copy construction and assignment of derived classes
    ISpecularInfoMap(const ISpecularInfoMap& other);
    ISpecularInfoMap& operator=(const ISpecularInfoMap &other);
};

#endif // ISPECULARINFOMAP_H

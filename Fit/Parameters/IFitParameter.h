// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/IFitParameter.h
//! @brief     Defines class IFitParameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IFITPARAMETER_H
#define IFITPARAMETER_H

#include "WinDllMacros.h"

//! @class IFitParameter
//! @ingroup fitting_internal
//! @brief The IFitParameter is a base class for fit parameters.

class BA_CORE_API_ IFitParameter
{
public:
    IFitParameter() {}
    virtual ~IFitParameter() {}
    IFitParameter(const IFitParameter&) = delete;
    IFitParameter& operator=(const IFitParameter&) = delete;

    virtual IFitParameter* clone() const = 0;
};

#endif // IFITPARAMETER_H

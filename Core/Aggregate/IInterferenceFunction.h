// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IInterferenceFunction.h
//! @brief     Defines and implements the interface class IInterferenceFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTION_H
#define IINTERFERENCEFUNCTION_H

#include "ISample.h"
#include "Vectors3D.h"

//! Pure virtual base class of interference functions.
//! @ingroup distribution_internal

class BA_CORE_API_ IInterferenceFunction : public ISample
{
public:
    virtual ~IInterferenceFunction();

    virtual IInterferenceFunction* clone() const=0;
    virtual void accept(INodeVisitor* visitor) const =0;

    //! Evaluates the interference function for a given wavevector transfer (only the real
    //! x and y components are relevant)
    virtual double evaluate(const kvector_t q) const=0;

    //! If defined by this interference function's parameters, returns the particle density (per
    //!  area). Otherwise, returns zero or a user-defined value
    virtual double getParticleDensity() const { return 0.0; }

    //! Indicates if this interference function can be used with a multilayer (DWBA mode)
    virtual bool supportsMultilayer() const { return true; }
};

#endif // IINTERFERENCEFUNCTION_H

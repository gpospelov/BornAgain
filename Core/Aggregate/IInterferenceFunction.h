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

#ifndef BORNAGAIN_CORE_AGGREGATE_IINTERFERENCEFUNCTION_H
#define BORNAGAIN_CORE_AGGREGATE_IINTERFERENCEFUNCTION_H

#include "Core/Scattering/ISample.h"
#include "Core/Vector/Vectors3D.h"

//! Pure virtual base class of interference functions.
//! @ingroup distribution_internal

class BA_CORE_API_ IInterferenceFunction : public ISample
{
public:
    IInterferenceFunction();
    IInterferenceFunction(const IInterferenceFunction& other);
    virtual ~IInterferenceFunction();

    virtual IInterferenceFunction* clone() const = 0;
    virtual void accept(INodeVisitor* visitor) const = 0;

    //! Evaluates the interference function for a given wavevector transfer
    virtual double evaluate(const kvector_t q, double outer_iff = 1.0) const;

    //! Sets the variance of the position for the calculation of the DW factor
    //! It is defined as the variance in each relevant dimension
    void setPositionVariance(double var);

    //! Returns the position variance
    double positionVariance() const { return m_position_var; }

    //! If defined by this interference function's parameters, returns the particle density (per
    //!  area). Otherwise, returns zero or a user-defined value
    virtual double getParticleDensity() const { return 0.0; }

    //! Indicates if this interference function can be used with a multilayer (DWBA mode)
    virtual bool supportsMultilayer() const { return true; }

    //! Evaluates the Debye-Waller factor for a given wavevector transfer
    double DWfactor(kvector_t q) const;

protected:
    //! Calculates the structure factor in the absence of extra inner structure
    double iff_no_inner(const kvector_t q, double outer_iff) const;

    //! Calculates the structure factor without Debye-Waller factor
    virtual double iff_without_dw(const kvector_t q) const = 0;

private:
    void init_parameters();
    double m_position_var;
};

#endif // BORNAGAIN_CORE_AGGREGATE_IINTERFERENCEFUNCTION_H

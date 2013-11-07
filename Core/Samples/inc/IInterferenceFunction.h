// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IInterferenceFunction.h
//! @brief     Defines interface class IInterferenceFunction.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTION_H_
#define IINTERFERENCEFUNCTION_H_

#include "Types.h"
#include "ISample.h"

//! Interface to interference functions.

class BA_CORE_API_ IInterferenceFunction : public ISample
{
public:
    virtual ~IInterferenceFunction() {}

    //! Evaluates the interference function for a given wavevector transfer
    virtual double evaluate(const cvector_t& q) const=0;

    virtual IInterferenceFunction *clone() const=0;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) const { p_visitor->visit(this); }

    //! Retrieves the size-distance coupling constant (default 0.0)
    virtual double getKappa() const { return 0.0; }
};

#endif /* IINTERFERENCEFUNCTION_H_ */



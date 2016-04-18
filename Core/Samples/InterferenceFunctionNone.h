// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/InterferenceFunctionNone.h
//! @brief     Defines class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONNONE_H_
#define INTERFERENCEFUNCTIONNONE_H_

#include "IInterferenceFunction.h"

//! @class InterferenceFunctionNone
//! @ingroup interference
//! @brief Default interference function (i.e. absence of any interference)

class BA_CORE_API_ InterferenceFunctionNone : public IInterferenceFunction
{
public:
    InterferenceFunctionNone();

    virtual InterferenceFunctionNone *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    virtual double evaluate(const kvector_t q) const;
};

#endif /* INTERFERENCEFUNCTIONNONE_H_ */

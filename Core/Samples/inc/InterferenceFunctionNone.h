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
//! @file      Samples/InterferenceFunctionNone.h 
//! @brief     Defines class InterferenceFunctionNone.
//
// ************************************************************************** //

#ifndef INTERFERENCEFUNCTIONNONE_H_
#define INTERFERENCEFUNCTIONNONE_H_

#include "IInterferenceFunction.h"

//! ?

class InterferenceFunctionNone : public IInterferenceFunction
{
public:
    InterferenceFunctionNone() { setName("InterferenceFunctionNone"); }
	virtual ~InterferenceFunctionNone() {}
	virtual InterferenceFunctionNone *clone() const { return new InterferenceFunctionNone(); }

    virtual double evaluate(const cvector_t &q) const { (void)q; return 1.0; }

};

#endif /* INTERFERENCEFUNCTIONNONE_H_ */

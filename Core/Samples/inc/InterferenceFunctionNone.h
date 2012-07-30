#ifndef INTERFERENCEFUNCTIONNONE_H_
#define INTERFERENCEFUNCTIONNONE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   InterferenceFunctionNone.h
//! @brief  Definition of InterferenceFunctionNone class
//! @author herck
//! @date   19.06.2012

#include "IInterferenceFunction.h"

class InterferenceFunctionNone : public IInterferenceFunction
{
public:
    InterferenceFunctionNone() { setName("InterferenceFunctionNone"); }
	virtual ~InterferenceFunctionNone() {}
	virtual InterferenceFunctionNone *clone() const { return new InterferenceFunctionNone(); }

	virtual double evaluate(kvector_t q) const { (void)q; return 1.0; }

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    InterferenceFunctionNone(const InterferenceFunctionNone &);
    InterferenceFunctionNone &operator=(const InterferenceFunctionNone &);

};



#endif /* INTERFERENCEFUNCTIONNONE_H_ */

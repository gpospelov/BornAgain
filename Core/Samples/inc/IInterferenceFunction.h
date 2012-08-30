#ifndef IINTERFERENCEFUNCTION_H_
#define IINTERFERENCEFUNCTION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IInterferenceFunction.h
//! @brief  Definition of IInterferenceFunction interface
//! @author herck
//! @date   18.06.2012

#include "Types.h"
#include "ISample.h"

class IInterferenceFunction : public ISample
{
public:
	virtual ~IInterferenceFunction() {}

	virtual double evaluate(cvector_t q) const=0;
	virtual IInterferenceFunction *clone() const=0;
};


#endif /* IINTERFERENCEFUNCTION_H_ */

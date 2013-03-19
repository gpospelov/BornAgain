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
//! @file      Samples/IInterferenceFunction.h 
//! @brief     Defines class IInterferenceFunction.
//
// ************************************************************************** //

#ifndef IINTERFERENCEFUNCTION_H_
#define IINTERFERENCEFUNCTION_H_

#include "Types.h"
#include "ISample.h"

//! ?

class IInterferenceFunction : public ISample
{
public:
    virtual ~IInterferenceFunction() {}

    virtual double evaluate(const cvector_t &q) const=0;
	virtual IInterferenceFunction *clone() const=0;
    virtual double getKappa() const { return 0.0; }
};

#endif /* IINTERFERENCEFUNCTION_H_ */

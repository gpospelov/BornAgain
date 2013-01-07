#ifndef IDECORATION_H_
#define IDECORATION_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IDecoration.h
//! @brief  Definition of IDecoration interface
//! @author Scientific Computing Group at FRM II
//! @date   Jun 22, 2012

#include "ICompositeSample.h"
#include "IInterferenceFunctionStrategy.h"
#include "IFormFactor.h"

class IDecoration : public ICompositeSample
{
public:
    virtual ~IDecoration() {}

    virtual IDecoration *clone() const=0;
    virtual IInterferenceFunctionStrategy *createStrategy(
            const std::vector<IFormFactor *> &form_factors) const=0;
};

#endif /* IDECORATION_H_ */

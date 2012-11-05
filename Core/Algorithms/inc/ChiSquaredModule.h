#ifndef CHISQUAREDMODULE_H_
#define CHISQUAREDMODULE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   ChiSquaredModule.h
//! @brief  Definition of ChiSquaredModule class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012

#include "IChiSquaredModule.h"
#include "OutputData.h"
#include "IFittingDataSelector.h"
#include "ISquaredFunction.h"

#include <vector>

class ChiSquaredModule : public IChiSquaredModule
{
public:
    ChiSquaredModule(const OutputData<double> &real_data);
    virtual ~ChiSquaredModule();

    virtual void setFittingDataSelector(const IFittingDataSelector &selector);

    void setChiSquaredFunction(const ISquaredFunction &squared_function);

    virtual double calculateChiSquared(const OutputData<double> *p_simulation_data=0);

    //! return squared function
    const ISquaredFunction *getSquaredFunction() const { return mp_squared_function; }

    //! return output data which contains chi^2 values
    virtual OutputData<double > *getChi2DifferenceMap() const;

protected:
    IFittingDataSelector *mp_data_selector;
};


#endif /* CHISQUAREDMODULE_H_ */

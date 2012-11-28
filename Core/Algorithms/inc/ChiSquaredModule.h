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

class ChiSquaredModule : public IChiSquaredModule
{
public:
    ChiSquaredModule(){}
    ChiSquaredModule(const ChiSquaredModule &other);
    ChiSquaredModule(const OutputData<double> &real_data);
    virtual ~ChiSquaredModule();

    virtual ChiSquaredModule *clone() const;

    //! calculate chi squared volume over experimental and simulated data
    virtual double calculateChiSquared(const OutputData<double> *p_simulation_data=0);

    //! return output data which contains chi^2 values
    virtual OutputData<double > *createChi2DifferenceMap() const;
private:
    // disabling assignment operator
    ChiSquaredModule &operator=(const ChiSquaredModule &);
};


#endif /* CHISQUAREDMODULE_H_ */

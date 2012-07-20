#ifndef IFITTINGDATASELECTOR_H_
#define IFITTINGDATASELECTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IFittingDataSelector.h
//! @brief  Definition of IFittingDataSelector class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 20, 2012

#include "OutputData.h"

#include <vector>

class IFittingDataSelector
{
public:
    virtual ~IFittingDataSelector() {}
    virtual IFittingDataSelector *clone() const=0;

    virtual void getFittingData(const OutputData<double> &real_data, const OutputData<double> &simulated_data,
            std::vector<double> &real_data_vector, std::vector<double> &simulated_data_vector,
            std::vector<double> &weights) const=0;
};

class DefaultAllDataSelector : public IFittingDataSelector
{
public:
    DefaultAllDataSelector() {}
    virtual ~DefaultAllDataSelector() {}
    virtual DefaultAllDataSelector *clone() const {
        return new DefaultAllDataSelector();
    }

    virtual void getFittingData(const OutputData<double> &real_data, const OutputData<double> &simulated_data,
            std::vector<double> &real_data_vector, std::vector<double> &simulated_data_vector,
            std::vector<double> &weights) const;
};

#endif /* IFITTINGDATASELECTOR_H_ */

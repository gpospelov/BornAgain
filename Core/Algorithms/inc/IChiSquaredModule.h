#ifndef ICHISQUAREDMODULE_H_
#define ICHISQUAREDMODULE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IChiSquaredModule.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Nov 5, 2012

#include "OutputData.h"
#include "IFittingDataSelector.h"
#include "ISquaredFunction.h"

#include <vector>

class IChiSquaredModule
{
public:
    IChiSquaredModule(const OutputData<double> &real_data);
    virtual ~IChiSquaredModule();

    void setRealData(const OutputData<double> &real_data);

    void setSimulationData(const OutputData<double> &simulation_data);

    virtual void setFittingDataSelector(const IFittingDataSelector &selector) =0;

    virtual double calculateChiSquared(const OutputData<double> *p_simulation_data=0) =0;

    //! return real data
    const OutputData<double> *getRealData() const { return mp_real_data; }

    //! return simulation data
    const OutputData<double> *getSimulationData() const { return mp_simulation_data; }

    //! return chi2 value (should be called after calculateChiSquared)
    virtual double getValue() const { return m_chi2_value; }

    //! return output data which contains chi^2 values
    virtual OutputData<double > *getChi2DifferenceMap() const=0;

protected:
    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulation_data;
    std::vector<double> m_weights;
    std::vector<double> m_real_data_vector;
    std::vector<double> m_simulation_data_vector;
    ISquaredFunction *mp_squared_function;

    double m_chi2_value;
};


#endif /* ICHISQUAREDMODULE_H_ */

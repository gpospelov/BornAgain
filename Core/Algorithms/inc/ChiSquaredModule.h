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

#include "OutputData.h"
#include "IFittingDataSelector.h"
#include "ISquaredFunction.h"

#include <vector>

class ChiSquaredModule
{
public:
    ChiSquaredModule(const OutputData<double> &real_data);
    virtual ~ChiSquaredModule();

    void setRealData(const OutputData<double> &real_data);

    void setSimulationData(const OutputData<double> &simulation_data);

    void setFittingDataSelector(const IFittingDataSelector &selector);

    void setChiSquaredFunction(const ISquaredFunction &squared_function);

    virtual double calculateChiSquared(const OutputData<double> *p_simulation_data=0);

    //! return real data
    const OutputData<double> *getRealData() const { return mp_real_data; }

    //! return simulation data
    const OutputData<double> *getSimulationData() const { return mp_simulation_data; }

    //! return chi2 value (should be called after calculateChiSquared)
    virtual double getValue() const { return m_chi2_value; }

    //! return squared function
    const ISquaredFunction *getSquaredFunction() const { return mp_squared_function; }

protected:
    OutputData<double> *mp_real_data;
    OutputData<double> *mp_simulation_data;
    std::vector<double> m_weights;
    std::vector<double> m_real_data_vector;
    std::vector<double> m_simulation_data_vector;
    IFittingDataSelector *mp_data_selector;
    ISquaredFunction *mp_squared_function;

    double m_chi2_value;
};


#endif /* CHISQUAREDMODULE_H_ */

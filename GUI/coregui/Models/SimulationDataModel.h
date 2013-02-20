#ifndef SIMULATIONDATAMODEL_H_
#define SIMULATIONDATAMODEL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   SimulationDataModel.h
//! @brief  Definition of SimulationDataModel
//! @author Scientific Computing Group at FRM II
//! @date   Feb 19, 2013

#include "SelectionListModel.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "Instrument.h"
#include "SimulationParameters.h"

//- -------------------------------------------------------------------
//! @class SimulationDataModel
//! @brief Definition of SimulationDataModel that holds lists of samples,
//! instruments and simulation parameters
//- -------------------------------------------------------------------
class SimulationDataModel
{
public:
    SimulationDataModel();
    ~SimulationDataModel() {}

    //! retrieve a list of the contained samples
    //! \return a list containing the ISample objects
    SelectionListModel<ISample> &getSampleList() { return m_samples; }

    //! retrieve a list of the contained sample builders
    //! \return a list containing the ISampleBuilder objects
    SelectionListModel<ISampleBuilder> &getSampleBuilderList() { return m_sample_builders; }

    //! retrieve a list of the contained instruments
    //! \return a list containing the Instrument objects
    SelectionListModel<Instrument> &getInstrumentList() { return m_instruments; }

    //! retrieve a list of the contained simulation parameters
    //! \return a list containing the SimulationParamters objects
    SelectionListModel<SimulationParameters> &getSimulationParameterList() { return m_simulation_parameters; }

    //! add sample to sample list
    void addSample(ISample *p_sample);

    //! add sample builder to list
    void addSampleBuilder(ISampleBuilder *p_sample_builder);

    //! add instrument to list
    void addInstrument(Instrument *p_instrument);

    //! add simulation parameters to list
    void addSimulationParameters(SimulationParameters *p_simulation_parameters);
private:
    SelectionListModel<ISample> m_samples;
    SelectionListModel<ISampleBuilder> m_sample_builders;
    SelectionListModel<Instrument> m_instruments;
    SelectionListModel<SimulationParameters> m_simulation_parameters;
};


#endif /* SIMULATIONDATAMODEL_H_ */

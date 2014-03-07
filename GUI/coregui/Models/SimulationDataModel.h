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

#include "ISample.h"
#include "ISampleBuilder.h"
#include "Instrument.h"
#include "SimulationParameters.h"
#include "JobModel.h"

#include <QMap>
#include <QString>

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
    QMap<QString, ISample*> getSampleList() { return m_samples; }

    //! retrieve a list of the contained sample builders
    //! \return a list containing the ISampleBuilder objects
    QMap<QString, ISampleBuilder*> getSampleBuilderList() { return m_sample_builders; }

    //! retrieve a list of the contained instruments
    //! \return a list containing the Instrument objects
    QMap<QString, Instrument*> getInstrumentList() { return m_instruments; }

    //! retrieve a list of the contained simulation parameters
    //! \return a list containing the SimulationParamters objects
    QMap<QString, SimulationParameters*> getSimulationParameterList() { return m_simulation_parameters; }

    //! retrieve a list of the started jobs
    //! \return a list containing the started jobs
    QMap<QString, JobModel*> getJobs() { return m_jobs; }

    //! add sample to sample list
    void addSample(QString name, ISample *p_sample);

    //! add sample builder to list
    void addSampleBuilder(QString name, ISampleBuilder *p_sample_builder);

    //! add instrument to list
    void addInstrument(QString name, Instrument *p_instrument);

    //! replace instrument with given name
    void changeInstrument(QString name, Instrument *p_instrument);

    //! add simulation parameters to list
    void addSimulationParameters(QString name, SimulationParameters *p_simulation_parameters);

    //! add job to list
    void addJob(QString name, JobModel *p_job);
private:
    QMap<QString, ISample*> m_samples;
    QMap<QString, ISampleBuilder*> m_sample_builders;
    QMap<QString, Instrument*> m_instruments;
    QMap<QString, SimulationParameters*> m_simulation_parameters;
    QMap<QString, JobModel*> m_jobs;
};


#endif /* SIMULATIONDATAMODEL_H_ */

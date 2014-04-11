#include "SimulationDataModel.h"

#include <QMessageBox>

SimulationDataModel::SimulationDataModel()
{
}

void SimulationDataModel::addSample(QString name, ISample *p_sample)
{
    if (!m_samples.contains(name)) {
        m_samples.insert(name, p_sample);
    }
}

void SimulationDataModel::addSampleBuilder(QString name, ISampleBuilder *p_sample_builder)
{
    if (!m_sample_builders.contains(name)) {
        m_sample_builders.insert(name, p_sample_builder);
    }
}

void SimulationDataModel::addInstrument(QString name, Instrument *p_instrument)
{
    if (!m_instruments.contains(name)) {
        m_instruments.insert(name, p_instrument);
    }
}

void SimulationDataModel::changeInstrument(QString name, Instrument *p_instrument)
{
    if (!m_instruments.contains(name)) {
        return;
    }
    delete m_instruments[name];
    m_instruments[name] = p_instrument;
}

void SimulationDataModel::addSimulationParameters(QString name, SimulationParameters *p_simulation_parameters)
{
    if (!m_simulation_parameters.contains(name)) {
        m_simulation_parameters.insert(name, p_simulation_parameters);
    }
}


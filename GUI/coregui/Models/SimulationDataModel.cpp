#include "SimulationDataModel.h"

#include <QMessageBox>

SimulationDataModel::SimulationDataModel()
{
}

SimulationDataModel::~SimulationDataModel()
{
    clear();
}


void SimulationDataModel::clear()
{
    qDeleteAll(m_samples);
    m_samples.clear();

    qDeleteAll(m_sample_builders);
    m_sample_builders.clear();

    qDeleteAll(m_instruments);
    m_instruments.clear();

    qDeleteAll(m_simulation_parameters);
    m_simulation_parameters.clear();
}


void SimulationDataModel::addSample(QString name, ISample *p_sample)
{
    m_samples.insertMulti(name, p_sample);
}

void SimulationDataModel::addSampleBuilder(QString name, ISampleBuilder *p_sample_builder)
{
    if (!m_sample_builders.contains(name)) {
        m_sample_builders.insert(name, p_sample_builder);
    }
}

void SimulationDataModel::addInstrument(QString name, Instrument *p_instrument)
{
    m_instruments.insertMulti(name, p_instrument);
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


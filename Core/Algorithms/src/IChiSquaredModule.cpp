#include "IChiSquaredModule.h"

IChiSquaredModule::IChiSquaredModule(const OutputData<double>& real_data)
: mp_simulation_data(0)
, mp_weights(0)
, m_chi2_value(0)
{
    mp_real_data = real_data.clone();
    mp_squared_function = new DefaultSquaredFunction();
    mp_data_selector = new DefaultAllDataSelector();
}

IChiSquaredModule::~IChiSquaredModule()
{
    delete mp_real_data;
    delete mp_simulation_data;
    delete mp_weights;
    delete mp_squared_function;
    delete mp_data_selector;
}

void IChiSquaredModule::setRealData(const OutputData<double>& real_data)
{
    delete mp_real_data;
    mp_real_data = real_data.clone();
}

void IChiSquaredModule::setSimulationData(
        const OutputData<double>& simulation_data)
{
    delete mp_simulation_data;
    mp_simulation_data = simulation_data.clone();
}

void IChiSquaredModule::setFittingDataSelector(
        const IFittingDataSelector& selector)
{
    delete mp_data_selector;
    mp_data_selector = selector.clone();
}

void IChiSquaredModule::setChiSquaredFunction(
        const ISquaredFunction& squared_function)
{
    delete mp_squared_function;
    mp_squared_function = squared_function.clone();
}

void IChiSquaredModule::initWeights()
{
    delete mp_weights;
    mp_weights = mp_data_selector->createWeightMap(*mp_real_data, *mp_simulation_data);
}

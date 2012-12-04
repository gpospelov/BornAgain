#include "IChiSquaredModule.h"


IChiSquaredModule::IChiSquaredModule()
    : mp_real_data(0)
    , mp_simulation_data(0)
    , mp_weights(0)
    , mp_squared_function(0)
    , mp_data_selector(0)
    , mp_data_normalizer(0)
    , mp_intensity_function(0)
    , m_ndegree_of_freedom(0)
    , m_chi2_value(0)
{
    mp_squared_function = new SquaredFunctionDefault();
    mp_data_selector = new DefaultAllDataSelector();
}


IChiSquaredModule::IChiSquaredModule(const IChiSquaredModule &other)
    : mp_real_data(0)
    , mp_simulation_data(0)
    , mp_weights(0)
    , mp_squared_function(0)
    , mp_data_selector(0)
    , mp_data_normalizer(0)
    , mp_intensity_function(0)
    , m_ndegree_of_freedom(0)
    , m_chi2_value(0)
{
    if(other.mp_real_data) mp_real_data = other.mp_real_data->clone();
    if(other.mp_simulation_data) mp_simulation_data = other.mp_simulation_data->clone();
    if(other.mp_weights) mp_weights = other.mp_weights->clone();
    if(other.mp_squared_function) mp_squared_function = other.mp_squared_function->clone();
    if(other.mp_data_selector) mp_data_selector = other.mp_data_selector->clone();
    if(other.mp_data_normalizer) mp_data_normalizer = other.mp_data_normalizer->clone();
    if(other.mp_intensity_function) mp_intensity_function = other.mp_intensity_function->clone();
    m_ndegree_of_freedom = other.m_ndegree_of_freedom;
}


IChiSquaredModule::~IChiSquaredModule()
{
    delete mp_real_data;
    delete mp_simulation_data;
    delete mp_weights;
    delete mp_squared_function;
    delete mp_data_selector;
    delete mp_data_normalizer;
    delete mp_intensity_function;
}


void IChiSquaredModule::setRealAndSimulatedData(const OutputData<double > &real_data, const OutputData<double >&simulation_data)
{
    delete mp_real_data;
    mp_real_data=real_data.clone();
    delete mp_simulation_data;
    mp_simulation_data = simulation_data.clone();
}


void IChiSquaredModule::setFittingDataSelector(const IFittingDataSelector& selector)
{
    delete mp_data_selector;
    mp_data_selector = selector.clone();
}


void IChiSquaredModule::setChiSquaredFunction(const ISquaredFunction& squared_function)
{
    delete mp_squared_function;
    mp_squared_function = squared_function.clone();
}

void IChiSquaredModule::setOutputDataNormalizer(const IOutputDataNormalizer &data_normalizer)
{
    delete mp_data_normalizer;
    mp_data_normalizer = data_normalizer.clone();
}


void IChiSquaredModule::setIntensityFunction(const IIntensityFunction &intensity_function)
{
    delete mp_intensity_function;
    mp_intensity_function = intensity_function.clone();
}


void IChiSquaredModule::initWeights()
{
    delete mp_weights;
    if( !mp_real_data ) throw NullPointerException("IChiSquaredModule::initWeights() -> Error! No real data has been set");
    if( !mp_simulation_data ) throw NullPointerException("IChiSquaredModule::initWeights() -> Error! No simulated data has been set");
    mp_weights = mp_data_selector->createWeightMap(*mp_real_data, *mp_simulation_data);
}


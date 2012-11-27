#include "ChiSquaredModule.h"


ChiSquaredModule::ChiSquaredModule(const ChiSquaredModule &other) : IChiSquaredModule(other)
{
}


ChiSquaredModule::~ChiSquaredModule()
{
}


ChiSquaredModule *ChiSquaredModule::clone() const
{
    return new ChiSquaredModule(*this);
}


double ChiSquaredModule::calculateChiSquared()
{
    if( !mp_real_data ) throw NullPointerException("ChiSquaredModule::calculateChiSquared() -> Error! No real data has been set");
    if( !mp_simulation_data ) throw NullPointerException("ChiSquaredModule::calculateChiSquared() -> Error! No simulated data has been set");

    double result = 0.0;
    size_t data_size = mp_real_data->getAllocatedSize();
    initWeights();

    if(mp_data_normalizer) {
        OutputData<double > *normalized_simulation = mp_data_normalizer->createNormalizedData(*mp_simulation_data);
        delete mp_simulation_data;
        mp_simulation_data = normalized_simulation;
    }

    OutputData<double> *p_difference = createChi2DifferenceMap();
    OutputData<double>::const_iterator it_weights = mp_weights->begin();
    OutputData<double>::const_iterator it_diff = p_difference->begin();
    while(it_diff != p_difference->end()) {
        result += (*it_diff++)*(*it_weights++);
    }
    delete p_difference;
    m_chi2_value = result/data_size;
    return m_chi2_value;
}


OutputData<double>* ChiSquaredModule::createChi2DifferenceMap() const
{
    OutputData<double > *p_difference = mp_simulation_data->clone();
    p_difference->setAllTo(0.0);

    OutputData<double>::iterator it_diff = p_difference->begin();
    OutputData<double>::const_iterator it_sim = mp_simulation_data->begin();
    OutputData<double>::const_iterator it_real = mp_real_data->begin();

    while (it_diff != p_difference->end()) {
        double value_simu = *it_sim++;
        double value_real = *it_real++;
        double squared_difference = mp_squared_function->calculateSquaredDifference(value_real, value_simu);
        *it_diff = squared_difference;
        ++it_diff;
    }

    return p_difference;
}

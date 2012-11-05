#include "ChiSquaredFrequency.h"

ChiSquaredFrequency::ChiSquaredFrequency(const OutputData<double>& real_data)
: IChiSquaredModule(real_data)
{
}

ChiSquaredFrequency::~ChiSquaredFrequency()
{
}

double ChiSquaredFrequency::calculateChiSquared(
        const OutputData<double>* p_simulation_data)
{
    if (p_simulation_data!=0) {
        setSimulationData(*p_simulation_data);
    }
    if (mp_simulation_data==0) {
        throw LogicErrorException("No simulation data present for calculating chi squared.");
    }
    double result = 0.0;
    size_t data_size = mp_real_data->getAllocatedSize();
    initWeights();
    OutputData<double> *p_difference = createChi2DifferenceMap();
    mp_weights->resetIndex();
    p_difference->resetIndex();
    while(p_difference->hasNext()) {
        result += p_difference->next()*mp_weights->next();
    }
    delete p_difference;
    m_chi2_value = result/data_size;
    return m_chi2_value;}

OutputData<double>* ChiSquaredFrequency::createChi2DifferenceMap() const
{
    OutputData<double > *p_difference = mp_simulation_data->clone();
    p_difference->setAllTo(0.0);

    mp_simulation_data->resetIndex();
    mp_real_data->resetIndex();
    p_difference->resetIndex();
    while (mp_real_data->hasNext()) {
        double value_simu = mp_simulation_data->next();
        double value_real = mp_real_data->next();
        double squared_difference = mp_squared_function->calculateSquaredDifference(value_real, value_simu);
        p_difference->next() = squared_difference;
    }

    return p_difference;}

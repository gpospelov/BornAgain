#include "ChiSquaredFrequency.h"

ChiSquaredFrequency::ChiSquaredFrequency(const OutputData<double>& real_data)
: IChiSquaredModule(real_data)
, mp_real_ft(0)
, mp_simulation_ft(0)
, m_cutoff(1.0)
{
}

ChiSquaredFrequency::~ChiSquaredFrequency()
{
    delete mp_real_ft;
    delete mp_simulation_ft;
}

double ChiSquaredFrequency::calculateChiSquared(
        const OutputData<double>* p_simulation_data)
{
    if (p_simulation_data!=0) {
        setSimulationData(*p_simulation_data);
    }

    double result = 0.0;
    initWeights();
    size_t data_size = mp_weights->getAllocatedSize();
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
    OutputData<double> *p_difference = mp_weights->clone();

    p_difference->resetIndex();
    mp_simulation_ft->resetIndex();
    mp_real_ft->resetIndex();

    while (p_difference->hasNext()) {
        complex_t diff = mp_simulation_ft->next() - mp_real_ft->next();
        double squared_difference = std::norm(diff);
        p_difference->next() = squared_difference;
    }

    return p_difference;
}

void ChiSquaredFrequency::initWeights()
{
    if (mp_simulation_data==0) {
        throw LogicErrorException("No simulation data present for calculating chi squared.");
    }
    delete mp_real_ft;
    delete mp_simulation_ft;
    mp_real_ft = new OutputData<complex_t>();
    mp_simulation_ft = new OutputData<complex_t>();
    fourierTransform(*mp_real_data, mp_real_ft);
    fourierTransform(*mp_simulation_data, mp_simulation_ft);
    delete mp_weights;
    mp_weights = new OutputData<double>();
    size_t rank = mp_simulation_ft->getDimension();
    int *n_dims = new int[rank];
    for (size_t i=0; i<rank; ++i) {
        n_dims[i] = mp_simulation_ft->getAxis(i)->getSize();
    }
    mp_weights->setAxisSizes(rank, n_dims);
    delete n_dims;
    mp_weights->resetIndex();
    size_t nbr_rows = mp_weights->getAllSizes()[0];
    size_t row_length = mp_weights->getAllSizes()[1];
    size_t row_number = 0;
    size_t counter = 0;
    while (mp_weights->hasNext()) {
        double weight = 0.0;
        size_t column_index = counter%row_length;
        int shift = (column_index>=row_length/2 ? -(int)row_length : 0);
        int centered_column_index = (int)column_index - shift;
        if (row_number<m_cutoff*nbr_rows && centered_column_index < m_cutoff*row_length/2.0) {
            weight = 1.0;
        }
        mp_weights->next() = weight;
        ++counter;
        if (counter%row_length==0) ++row_number;
    }
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/ChiSquaredFrequency.cpp
//! @brief     Implements class ChiSquaredFrequency.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "ChiSquaredFrequency.h"
#include "OutputDataFunctions.h"

#include <cassert>

ChiSquaredFrequency::ChiSquaredFrequency()
    : mp_real_ft(0) , mp_simulation_ft(0) , m_cutoff(1.0)
{
}

ChiSquaredFrequency::~ChiSquaredFrequency()
{
    delete mp_real_ft;
    delete mp_simulation_ft;
}

double ChiSquaredFrequency::calculateChiSquared()
{
    if( !mp_real_data )
        throw NullPointerException("ChiSquaredFrequency::calculateChiSquared() -> Error! No real data has been set");
    if( !mp_simulation_data )
        throw NullPointerException("ChiSquaredFrequency::calculateChiSquared() -> Error! No simulated data has been set");

    double result = 0.0;
    initWeights();
    size_t data_size = mp_weights->getAllocatedSize();
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

OutputData<double>* ChiSquaredFrequency::createChi2DifferenceMap() const
{
    assert(mp_simulation_ft != NULL);
    assert(mp_real_ft != NULL);

    OutputData<double> *p_difference = mp_weights->clone();

    OutputData<double>::iterator it_diff = p_difference->begin();
    OutputData<complex_t>::const_iterator it_sim = mp_simulation_ft->begin();
    OutputData<complex_t>::const_iterator it_real = mp_real_ft->begin();

    while (it_diff != p_difference->end()) {
        complex_t real = *it_real++;
        complex_t simu = *it_sim++;
        complex_t diff = real - simu;
//        double sum_norms = std::max(std::norm(real), 1.0);
        double squared_difference = std::norm(diff); // /std::sqrt(sum_norms);
        *it_diff = squared_difference;
        ++it_diff;
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
    OutputDataFunctions::fourierTransform(*mp_real_data, mp_real_ft);
    OutputDataFunctions::fourierTransform(*mp_simulation_data, mp_simulation_ft);
    delete mp_weights;
    mp_weights = new OutputData<double>();
    size_t rank = mp_simulation_ft->getRank();
    int *n_dims = new int[rank];
    for (size_t i=0; i<rank; ++i) {
        n_dims[i] = (int)mp_simulation_ft->getAxis(i)->getSize();
    }
    mp_weights->setAxisSizes(rank, n_dims);
    delete [] n_dims;
    OutputData<double>::iterator it_weights = mp_weights->begin();
    size_t nbr_rows = mp_weights->getAllSizes()[0];
    size_t row_length = mp_weights->getAllSizes()[1];
    size_t row_number = 0;
    while (it_weights != mp_weights->end()) {
        double weight = 0.0;
        size_t linear_index = it_weights.getIndex();
        size_t column_index = linear_index%row_length;
        int shift = (column_index>=row_length/2 ? -(int)row_length : 0);
        int centered_column_index = (int)column_index - shift;
        if (row_number<m_cutoff*nbr_rows && centered_column_index < m_cutoff*row_length/2.0) {
            weight = 1.0;
        }
        *it_weights = weight;
        if (linear_index%row_length==0) ++row_number;
        ++it_weights;
    }
}

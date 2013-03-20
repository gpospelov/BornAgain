// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/ChiSquaredModule.cpp
//! @brief     Implements class ChiSquaredModule.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "ChiSquaredModule.h"
#include "OutputDataFunctions.h"
#include <cassert>

ChiSquaredModule::ChiSquaredModule(const ChiSquaredModule &other)
     : IChiSquaredModule(other)
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

    initWeights();

    if(mp_data_normalizer) {
        OutputData<double > *normalized_simulation = mp_data_normalizer->createNormalizedData(*mp_simulation_data);
        delete mp_simulation_data;
        mp_simulation_data = normalized_simulation;
    }

    if( mp_intensity_function ) {
        OutputDataFunctions::applyFunction(*mp_simulation_data, mp_intensity_function);
        OutputDataFunctions::applyFunction(*mp_real_data, mp_intensity_function);
    }

    OutputData<double> *p_difference = createChi2DifferenceMap();
    OutputData<double>::const_iterator it_weights = mp_weights->begin();
    OutputData<double>::const_iterator it_diff = p_difference->begin();
    double result(0);
    while(it_diff != p_difference->end()) {
        result += (*it_diff++)*(*it_weights++);
    }
    delete p_difference;

    double fnorm(0);
    m_ndegree_of_freedom > 0 ? fnorm=double(m_ndegree_of_freedom) : fnorm = double(mp_real_data->getAllocatedSize());
    m_chi2_value = result/fnorm;
    return m_chi2_value;
}

double ChiSquaredModule::getResidualValue(size_t index ) const
{
    assert(mp_real_data != NULL );
    assert(mp_simulation_data != NULL);
    assert(mp_weights != NULL);
    assert(index < mp_real_data->getAllocatedSize() );
    double value_real = (*mp_real_data)[index];
    double value_simu  = (*mp_simulation_data)[index];
    double weight = (*mp_weights)[index];
    double squared_error = getSquaredFunction()->calculateSquaredError(value_real, value_simu);
    assert(squared_error);
    assert(weight);
    //double residual = std::sqrt(weight)*(value_real - value_simu)/std::sqrt(squared_error);
    double residual = std::sqrt(weight)*(value_simu - value_real)/std::sqrt(squared_error);
    return residual;
}

OutputData<double>* ChiSquaredModule::createChi2DifferenceMap() const
{
    if( !mp_real_data ) throw NullPointerException("ChiSquaredModule::calculateChiSquared() -> Error! No real data has been set");
    if( !mp_simulation_data ) throw NullPointerException("ChiSquaredModule::calculateChiSquared() -> Error! No simulated data has been set");

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

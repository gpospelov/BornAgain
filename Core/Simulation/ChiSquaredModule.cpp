// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/ChiSquaredModule.cpp
//! @brief     Implements class ChiSquaredModule.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ChiSquaredModule.h"

//! Updates mp_simulation_data and mp_weights, returns chi^2.

//double ChiSquaredModule::calculateChiSquared()
//{
//    if( !mp_real_data )
//        throw Exceptions::NullPointerException("ChiSquaredModule::calculateChiSquared() -> "
//                                   "Error! No real data has been set");
//    if( !mp_simulation_data )
//        throw Exceptions::NullPointerException("ChiSquaredModule::calculateChiSquared() -> "
//                                   "Error! No simulated data has been set");

//    if(mp_data_normalizer) {
//        OutputData<double> *normalized_simulation =
//            mp_data_normalizer->createNormalizedData(*mp_simulation_data);
//        delete mp_simulation_data;
//        mp_simulation_data = normalized_simulation;
//    }

////    if( mp_intensity_function ) {
////        OutputDataFunctions::applyFunction(
////            *mp_simulation_data, mp_intensity_function);
////        OutputDataFunctions::applyFunction(
////            *mp_real_data, mp_intensity_function);
////    }

//    initWeights();
//    OutputData<double> *p_difference = createChi2DifferenceMap();

////    OutputData<double>::const_iterator it_weights = mp_weights->begin();
////    OutputData<double>::const_iterator it_diff = p_difference->begin();
////    double sum = 0;
////    while(it_diff != p_difference->end())
////        sum += (*it_diff++)*(*it_weights++);
////    delete p_difference;

////    double fnorm = m_ndegree_of_freedom > 0 ?
////        m_ndegree_of_freedom :
////        mp_real_data->getAllocatedSize();

//    double sum(0.0);
//    int nentries(0);
//    for(size_t index=0; index<p_difference->getAllocatedSize(); ++index) {
//        if(mp_masks && (*mp_masks)[index]) continue;
//        sum += (*p_difference)[index]*(*mp_weights)[index];
//        ++nentries;
//    }
//    double fnorm = m_ndegree_of_freedom > 0 ?
//           m_ndegree_of_freedom :
//           nentries;


//    return sum/fnorm;
//}

//double ChiSquaredModule::getResidualValue(size_t index ) const
//{
//    assert(mp_real_data != nullptr );
//    assert(mp_simulation_data != nullptr);
//    assert(mp_weights != nullptr);
//    assert(index < mp_real_data->getAllocatedSize() );
//    double value_real = (*mp_real_data)[index];
//    double value_simu  = (*mp_simulation_data)[index];

//    if(mp_intensity_function) {
//        value_simu = mp_intensity_function->evaluate(value_simu);
//        value_real = mp_intensity_function->evaluate(value_real);
//    }

//    double weight = (*mp_weights)[index];
//    double squared_error = getSquaredFunction()->calculateSquaredError(
//        value_real, value_simu);
//    assert(squared_error);
//    assert(weight);
//    double residual = std::sqrt(weight)*(value_simu - value_real)/
//        std::sqrt(squared_error);
//    return residual;
//}


//OutputData<double>* ChiSquaredModule::createChi2DifferenceMap() const
//{
//    if( !mp_real_data )
//        throw Exceptions::NullPointerException("ChiSquaredModule::calculateChiSquared() -> "
//                                   "Error! No real data has been set");
//    if( !mp_simulation_data )
//        throw Exceptions::NullPointerException("ChiSquaredModule::calculateChiSquared() -> "
//                                   "Error! No simulated data has been set");

//    OutputData<double > *p_difference = mp_simulation_data->clone();
//    p_difference->setAllTo(0.0);

////    OutputData<double>::iterator it_diff = p_difference->begin();
////    OutputData<double>::const_iterator it_sim = mp_simulation_data->begin();
////    OutputData<double>::const_iterator it_real = mp_real_data->begin();

////    while (it_diff != p_difference->end()) {
////        if( (it_sim.getIndex() != it_real.getIndex()) ||
////            (it_sim.getIndex() != it_diff.getIndex()) ) {
////            throw Exceptions::DomainErrorException(
////                "ChiSquaredModule::calculateChiSquared() -> Iterator inconsistency");
////        }
////        double value_simu = *it_sim++;
////        double value_real = *it_real++;

////        if(mp_intensity_function) {
////            value_simu = mp_intensity_function->evaluate(value_simu);
////            value_real = mp_intensity_function->evaluate(value_real);
////        }

////        double squared_difference =
////            mp_squared_function->calculateSquaredDifference(
////                value_real, value_simu);
////        *it_diff = squared_difference;
////        ++it_diff;
////    }

//    if(mp_masks && mp_masks->getAllocatedSize() != mp_real_data->getAllocatedSize()) {
//        throw Exceptions::LogicErrorException(
//             "ChiSquaredModule::createChi2DifferenceMap() -> Error. "
//             "Size of mask array differs from real data.");
//    }

//    for(size_t index=0; index<mp_real_data->getAllocatedSize(); ++index) {
//        if(mp_masks && (*mp_masks)[index]) continue;
//            double value_simu = (*mp_simulation_data)[index];
//            double value_real = (*mp_real_data)[index];

//            if(mp_intensity_function) {
//                value_simu = mp_intensity_function->evaluate(value_simu);
//                value_real = mp_intensity_function->evaluate(value_real);
//            }

//            double squared_difference =
//                mp_squared_function->calculateSquaredDifference(
//                    value_real, value_simu);
//        (*p_difference)[index] = squared_difference;
//    }

//    return p_difference;
//}


void ChiSquaredModule::processFitElements(std::vector<FitElement>::iterator first,
                                          std::vector<FitElement>::iterator last)
{
    assert(mp_squared_function);

    for (std::vector<FitElement>::iterator it = first; it != last; ++it) {
        double value_simu = it->getSimulValue();
        double value_real = it->getRealValue();
        double weight = it->getWeight();

        if(mp_intensity_function) {
            value_simu = mp_intensity_function->evaluate(value_simu);
            value_real = mp_intensity_function->evaluate(value_real);
        }

        double squared_difference =
            mp_squared_function->calculateSquaredDifference(
                value_real, value_simu)*weight;

        it->setSquaredDifference(squared_difference);

        double squared_error = mp_squared_function->calculateSquaredError(value_real, value_simu);
        double residual = std::sqrt(weight)*(value_simu - value_real)/std::sqrt(squared_error);

        it->setResidual(residual);
    }
}

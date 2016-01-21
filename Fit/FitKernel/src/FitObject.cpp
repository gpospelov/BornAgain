// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/FitObject.cpp
//! @brief     Implements class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitObject.h"
#include "GISASSimulation.h"
#include "Exceptions.h"
#include "MessageService.h"
#include "IIntensityNormalizer.h"
#include <boost/scoped_ptr.hpp>

FitObject::FitObject(
    const GISASSimulation& simulation, const OutputData<double >& real_data,
    double weight)
    : m_simulation(simulation.clone())
    , m_real_data(real_data.clone())
    , m_weight(weight)
{
    setName("FitObject");
//    if( !m_real_data->hasSameShape(*m_simulation->getOutputData()) ) {
//        msglog(MSG::INFO) << "FitObject::FitObject() -> Info. "
//            "Real data and output data in the simulation have different shape. "
//            "Adjusting simulation's detector.";
//    } else {
//        msglog(MSG::INFO) << "FitObject::FitObject() -> Info. "
//            "Real data and output data in the simulation have same shape.";
//    }
    m_simulation->setDetectorParameters(*m_real_data);
    if( !m_real_data->hasSameShape(*m_simulation->getOutputData()) ) {

    }
}

FitObject::~FitObject()
{
}

const OutputData<double> *FitObject::getRealData() const
{
    return m_real_data.get();
}

const OutputData<double> *FitObject::getSimulationData() const
{
    return m_simulation_data.get();
}


//! Adds parameters from local pool to external pool
std::string FitObject::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path = IParameterized::addParametersToExternalPool(
        path, external_pool, copy_number);

    // add parameters of the simulation
    if(m_simulation)
        m_simulation->addParametersToExternalPool(new_path, external_pool, -1);

    return new_path;
}

double FitObject::getWeight() const
{
    return m_weight;
}

size_t FitObject::getSizeOfData() const
{
    // FIXME Fix this hell
    size_t result = m_real_data->getAllocatedSize() - m_simulation->getInstrument().getDetector()->getDetectorMask()->getNumberOfMaskedChannels();
    return result;
}

//! Runs simulation and put results (the real and simulated intensities) into
//! external vector. Masked channels will be excluded from the vector.
void FitObject::prepareFitElements(std::vector<FitElement> &fit_elements, double weight,
                                   IIntensityNormalizer *normalizer)
{
    m_simulation->runSimulation();
//    m_simulation->normalize();
    m_simulation_data.reset(m_simulation->getDetectorIntensity());

    if(normalizer) {
        normalizer->apply(*m_simulation_data.get());
    }

    const OutputData<bool> *masks(0);
    if(m_simulation->getInstrument().getDetector()->hasMasks()) {
        masks = m_simulation->getInstrument().getDetector()->getDetectorMask()->getMaskData();
    }

    for(size_t index=0; index<m_simulation_data->getAllocatedSize(); ++index) {
        if(masks && (*masks)[index]) continue;
        FitElement element(index, (*m_simulation_data)[index], (*m_real_data)[index], weight);
        fit_elements.push_back(element);
    }
}

//!Creates ChiSquared map from external vector.
// It is used from Python in one example, didn't find nicer way/place to create such map.
OutputData<double> *FitObject::getChiSquaredMap(std::vector<FitElement>::const_iterator first,
                                                std::vector<FitElement>::const_iterator last) const
{
    OutputData<double> *result = new OutputData<double>;
    result->copyShapeFrom(*m_simulation_data.get());

    for(std::vector<FitElement>::const_iterator it=first; it!=last; ++it) {
        (*result)[it->getIndex()] = it->getSquaredDifference();

    }

    return result;
}

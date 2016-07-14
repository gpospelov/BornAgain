// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitObject.cpp
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
#include "IIntensityNormalizer.h"

FitObject::FitObject(const GISASSimulation& simulation, const OutputData<double >& real_data,
    double weight, bool adjust_detector_to_data)
    : m_simulation(simulation.clone())
    , m_real_data(real_data.clone())
    , m_chi2_data(new OutputData<double>)
    , m_weight(weight)
    , m_adjust_detector_to_data(adjust_detector_to_data)
{
    setName("FitObject");
    init_dataset();
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

const GISASSimulation *FitObject::getSimulation() const
{
    return m_simulation.get();
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

//! Initialize detector, if necessary, to match experimental data
void FitObject::init_dataset()
{
    if(!same_dimensions_dataset()) {
        if(m_adjust_detector_to_data && is_possible_to_adjust_simulation()) {
            m_simulation->setDetectorParameters(*m_real_data);
        } else {
            throw Exceptions::LogicErrorException(get_error_message());
        }
    }
    m_chi2_data->copyShapeFrom(*m_real_data);
}

bool FitObject::same_dimensions_dataset() const
{
    return m_real_data->hasSameDimensions(*m_simulation->getOutputData());
}

//! returns true if it is possible to adjust detector axes to the axes of real data
//! * rank of two data should coinside
//! * for every axis, number of real data axis bins should be not large than simulation axis
//! * for every axis, (min,max) values of real axis should be inside simulation axis
bool FitObject::is_possible_to_adjust_simulation() const
{
    if(m_simulation->getOutputData()->getRank() != m_real_data->getRank()) return false;
    for(size_t i=0; i<m_real_data->getRank(); ++i) {
        const IAxis *ra = m_real_data->getAxis(i);
        const IAxis *sa = m_simulation->getOutputData()->getAxis(i);
        if(ra->getSize() > sa->getSize()) return false;
        if(ra->getMin() < sa->getMin()) return false;
        if(ra->getMax() > sa->getMax()) return false;
    }
    return true;
}

std::string FitObject::get_error_message() const
{
    std::ostringstream message;
    message << "FitObject::init_dataset() -> Error. "
            << "Real data and detector have different shape. \n"
            << "Real data axes -> ";
    for(size_t i=0; i<m_real_data->getRank(); ++i) {
        message << "#"<< i << ": " << (*m_real_data->getAxis(i)) << " ";
    }
    message << "\nDetector axes  -> ";
    for(size_t i=0; i<m_simulation->getOutputData()->getRank(); ++i) {
        message << "#"<< i << ": " << (*m_simulation->getOutputData()->getAxis(i)) << " ";
    }
    return message.str();
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
    m_simulation_data.reset(m_simulation->getDetectorIntensity());

    if(normalizer) {
        normalizer->apply(*m_simulation_data.get());
    }

    const OutputData<bool> *masks(0);
    if(m_simulation->getInstrument().getDetector()->hasMasks()) {
        masks = m_simulation->getInstrument().getDetector()->getDetectorMask()->getMaskData();
    }

    if(masks && m_simulation_data->getAllocatedSize() != masks->getAllocatedSize()) {
        std::ostringstream message;
        message << "FitObject::prepareFitElements() -> Error. Size mismatch. "
                << "m_simulation_data->getAllocatedSize():" << m_simulation_data->getAllocatedSize()
                << " " << "masks->getAllocatedSize()" << masks->getAllocatedSize()
                << std::endl;
        throw Exceptions::RuntimeErrorException(message.str());
    }

    for(size_t index=0; index<m_simulation_data->getAllocatedSize(); ++index) {
        if(masks && (*masks)[index]) continue;
        FitElement element(index, (*m_simulation_data)[index], (*m_real_data)[index], weight);
        fit_elements.push_back(element);
    }
}

//!Creates ChiSquared map from external vector.
// It is used from Python in one example, didn't find nicer way/place to create such map.
const OutputData<double> *FitObject::getChiSquaredMap(std::vector<FitElement>::const_iterator first,
                                                std::vector<FitElement>::const_iterator last) const
{
    m_chi2_data->setAllTo(0.0);
    for(std::vector<FitElement>::const_iterator it=first; it!=last; ++it) {
        (*m_chi2_data)[it->getIndex()] = it->getSquaredDifference();

    }

    return m_chi2_data.get();
}

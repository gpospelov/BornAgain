// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitObject.cpp
//! @brief     Implements class FitObject.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObject.h"
#include "BornAgainNamespace.h"
#include "DetectorFunctions.h"
#include "FitElement.h"
#include "IHistogram.h"
#include "IIntensityNormalizer.h"
#include "Simulation.h"
#include "SimulationArea.h"
#include "UnitConverterUtils.h"

static_assert(std::is_copy_constructible<FitObject>::value == false,
              "FitObject should not be copy constructable");
static_assert(std::is_copy_assignable<FitObject>::value == false,
              "FitObject should not be copy assignable");

FitObject::FitObject(const Simulation& simulation, const OutputData<double>& real_data,
                     double weight)
    : m_simulation(simulation.clone()), m_weight(weight), m_fit_elements_count(0)

{
    setName("FitObject");
    m_fit_elements_count = m_simulation->numberOfSimulationElements();
    registerChild(m_simulation.get());
    init_dataset(real_data);
    m_simulation_result = m_simulation->result();
}

FitObject::~FitObject() {}

const OutputData<double>& FitObject::simulationData() const { return *m_simulation_data.get(); }

std::vector<const INode*> FitObject::getChildren() const
{
    return std::vector<const INode*>() << m_simulation;
}

SimulationResult FitObject::simulationResult() const
{
    return m_simulation_result;
}

SimulationResult FitObject::experimentalData() const
{
    return m_experimental_data;
}

//! Check if real_data shape corresponds with the detector.

void FitObject::init_dataset(const OutputData<double>& real_data)
{
    auto converter = UnitConverterUtils::createConverter(*m_simulation);
    auto roi_data = UnitConverterUtils::createOutputData(*converter.get(), converter->defaultUnits());

    auto detector = m_simulation->getInstrument().getDetector();

    if (roi_data->hasSameDimensions(real_data)) {
        // data is already cropped to ROI
        roi_data->setRawDataVector(real_data.getRawDataVector());

    }  else if(DetectorFunctions::hasSameDimensions(*detector, real_data)) {
        // exp data has same shape as the detector and will be placed in roi_data
        detector->iterate([&](IDetector::const_iterator it){
            (*roi_data)[it.roiIndex()] = real_data[it.detectorIndex()];
        }, /*visit_masked*/true);

    } else {
        throw std::runtime_error("FitObject::init_dataset() -> Error. Detector and exp data have "
                                 "different shape.");
    }

    m_experimental_data = SimulationResult(*roi_data, *converter);
    m_real_data.reset(real_data.clone());
}

size_t FitObject::numberOfFitElements() const { return m_fit_elements_count; }

//! Runs simulation and put results (the real and simulated intensities) into external vector.
//! Masked channels will be excluded from the vector.

void FitObject::prepareFitElements(std::vector<FitElement>& fit_elements, double weight,
                                   IIntensityNormalizer* normalizer)
{
    m_simulation->runSimulation();
    m_simulation_result = m_simulation->result();
    m_simulation_data.reset(m_simulation_result.data());

    if (normalizer)
        normalizer->apply(*m_simulation_data.get());

    m_simulation->getInstrument().getDetector()->iterate([&](IDetector::const_iterator it){
        // FIXME find elegant way (issue #2018)
        size_t rdata_index
            = m_simulation_data->getAllocatedSize() == m_real_data->getAllocatedSize()
                  ? it.roiIndex()
                  : it.detectorIndex();

        if (rdata_index >= m_real_data->getAllocatedSize())
            throw ("FitObject::prepareFitElements() -> Error. Out-of-bounds.");
        FitElement element(it.roiIndex(), (*m_simulation_data)[it.roiIndex()],
                           (*m_real_data)[rdata_index], weight);
        fit_elements.push_back(element);
    });
}

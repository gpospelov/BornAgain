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
#include "IntensityDataFunctions.h"
#include "Numeric.h"
#include "ArrayUtils.h"

static_assert(std::is_copy_constructible<FitObject>::value == false,
              "FitObject should not be copy constructable");
static_assert(std::is_copy_assignable<FitObject>::value == false,
              "FitObject should not be copy assignable");

FitObject::FitObject(const Simulation& simulation, const OutputData<double>& data, double weight)
    : m_simulation(simulation.clone()), m_weight(weight), m_fit_elements_count(0)

{
    init_parameters();
    m_experimental_data = IntensityDataFunctions::ConvertData(simulation, data, false);
}

FitObject::FitObject(const Simulation& simulation, const std::vector<std::vector<double>>& data,
                     double weight)
    : m_simulation(simulation.clone()), m_weight(weight), m_fit_elements_count(0)

{
    init_parameters();
    m_experimental_data = IntensityDataFunctions::ConvertData(simulation, data, false);
}

FitObject::~FitObject() = default;

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

SimulationResult FitObject::relativeDifference() const
{
    auto converter = UnitConverterUtils::createConverter(*m_simulation);
    auto roi_data = UnitConverterUtils::createOutputData(*converter.get(), converter->defaultUnits());
    auto detector = m_simulation->getInstrument().getDetector();

    detector->iterate([&](IDetector::const_iterator it){
        const size_t index = it.roiIndex();
        (*roi_data)[index] = Numeric::get_relative_difference(
                    m_simulation_result[index], m_experimental_data[index]);
    });

    return SimulationResult(*roi_data, *converter);
}

void FitObject::runSimulation()
{
    m_simulation->runSimulation();
    m_simulation_result = m_simulation->result();
}

std::vector<double> FitObject::experimental_array() const
{
    std::vector<double> result;
    result.reserve(numberOfFitElements());

    auto detector = m_simulation->getInstrument().getDetector();
    detector->iterate([&](IDetector::const_iterator it){
        result.push_back(m_experimental_data[it.roiIndex()]);
    });

    return result;
}

std::vector<double> FitObject::simulation_array() const
{
    std::vector<double> result;
    result.reserve(numberOfFitElements());

    auto detector = m_simulation->getInstrument().getDetector();
    detector->iterate([&](IDetector::const_iterator it){
        result.push_back(m_simulation_result[it.roiIndex()]);
    });

    return result;
}

void FitObject::init_parameters()
{
    setName("FitObject");
    m_fit_elements_count = m_simulation->numberOfSimulationElements();
    registerChild(m_simulation.get());
    m_simulation_result = m_simulation->result();
}

size_t FitObject::numberOfFitElements() const { return m_fit_elements_count; }

//! Runs simulation and put results (the real and simulated intensities) into external vector.
//! Masked channels will be excluded from the vector.

void FitObject::prepareFitElements(std::vector<FitElement>& fit_elements, double weight,
                                   IIntensityNormalizer* )
{
    m_simulation->runSimulation();
    m_simulation_result = m_simulation->result();

// TODO FIXE Consider normalizer removal. Now FitScaleAndShift example is broken.
//    if (normalizer)
//        normalizer->apply(*m_simulation_data.get());

    m_simulation->getInstrument().getDetector()->iterate([&](IDetector::const_iterator it){
        FitElement element(it.roiIndex(), m_simulation_result[it.roiIndex()],
                           m_experimental_data[it.roiIndex()], weight);
        fit_elements.push_back(element);
    });
}

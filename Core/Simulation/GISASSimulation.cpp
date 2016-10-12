// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/GISASSimulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GISASSimulation.h"
#include "BornAgainNamespace.h"
#include "Histogram2D.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "SimulationElement.h"

GISASSimulation::GISASSimulation()
{
    initialize();
}

GISASSimulation::GISASSimulation(const MultiLayer& p_sample)
    : Simulation(p_sample)
{
    initialize();
}

GISASSimulation::GISASSimulation(std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation(p_sample_builder)
{
    initialize();
}

GISASSimulation::GISASSimulation(const GISASSimulation& other)
    : Simulation(other)
{
    initialize();
}

void GISASSimulation::prepareSimulation()
{
    if (m_instrument.getDetectorDimension() != 2)
        throw Exceptions::LogicErrorException("GISASSimulation::prepareSimulation() "
                "-> Error. The detector was not properly configured.");
    getInstrument().initDetector();
    Simulation::prepareSimulation();
}

int GISASSimulation::getNumberOfSimulationElements() const
{
    if (m_instrument.getDetectorDimension()!=2)
        throw Exceptions::RuntimeErrorException("GISASSimulation::getNumberOfSimulationElements: "
                                    "detector is not two-dimensional");
    const IAxis& x_axis = m_instrument.getDetectorAxis(BornAgain::X_AXIS_INDEX);
    const IAxis& y_axis = m_instrument.getDetectorAxis(BornAgain::X_AXIS_INDEX);
    int nmasked = getInstrument().getDetector()->getNumberOfMaskedChannels();
    return x_axis.getSize()*y_axis.getSize() - nmasked;
}

OutputData<double>* GISASSimulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type) const
{
    OutputData<double>* ret = m_instrument.getDetectorIntensity(m_intensity_map, units_type);
    ret->setVariability( m_options.getDefaultVariability() );
    return ret;
}

Histogram2D* GISASSimulation::getIntensityData(IDetector2D::EAxesUnits units_type) const
{
    const std::unique_ptr<OutputData<double>> data(getDetectorIntensity(units_type));
    return new Histogram2D(*data);
}

void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength<=0.0)
        throw Exceptions::ClassInitializationException(
            "Simulation::setBeamParameters() -> Error. Incoming wavelength <= 0.");
    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
}

void GISASSimulation::setDetector(const IDetector2D& detector)
{
    m_instrument.setDetector(detector);
    updateIntensityMap();
}

void GISASSimulation::setDetectorParameters(const OutputData<double>& output_data)
{
    m_instrument.matchDetectorAxes(output_data);

    m_intensity_map.clear();
    m_intensity_map.copyShapeFrom(output_data); // to copy mask too
    m_intensity_map.setAllTo(0.);
}

void GISASSimulation::setDetectorParameters(const IHistogram& histogram)
{
    const std::unique_ptr<OutputData<double>> data(histogram.createOutputData());
    setDetectorParameters(*data);
}

void GISASSimulation::setDetectorParameters(size_t n_phi, double phi_min, double phi_max,
                                            size_t n_alpha, double alpha_min, double alpha_max)
{
    m_instrument.setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);
    updateIntensityMap();
}

std::string GISASSimulation::addParametersToExternalPool(
    const std::string& path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path = IParameterized::addParametersToExternalPool(
            path, external_pool, copy_number);

    // add parameters of the instrument
    m_instrument.addParametersToExternalPool(new_path, external_pool, -1);

    new_path = addSimulationParametersToExternalPool(new_path, external_pool);

    return new_path;
}

void GISASSimulation::removeMasks()
{
    m_instrument.getDetector()->removeMasks();
}

void GISASSimulation::addMask(const Geometry::IShape2D& shape, bool mask_value)
{
    m_instrument.getDetector()->addMask(shape, mask_value);
}

void GISASSimulation::maskAll()
{
    m_instrument.getDetector()->maskAll();
}

// *** protected ***

void GISASSimulation::initSimulationElementVector()
{
    m_sim_elements = m_instrument.createSimulationElements();
}

void GISASSimulation::transferResultsToIntensityMap()
{
    size_t detector_dimension = m_instrument.getDetectorDimension();
    if (detector_dimension!=2)
        throw Exceptions::RuntimeErrorException("GISASSimulation::transferResultsToIntensityMap: "
                                    "detector is not two-dimensional");
    size_t element_index(0);
    for(size_t index=0; index<m_intensity_map.getAllocatedSize(); ++index) {
        if(m_instrument.getDetector()->isMasked(index)) continue;
        m_intensity_map[index] = m_sim_elements[element_index++].getIntensity();
    }
}

void GISASSimulation::updateIntensityMap()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim)
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
    m_intensity_map.setAllTo(0.);
}

void GISASSimulation::initialize()
{
    setName(BornAgain::GISASSimulationType);
}

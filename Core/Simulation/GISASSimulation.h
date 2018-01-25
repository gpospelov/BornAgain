// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/GISASSimulation.h
//! @brief     Defines class GISASSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASSIMULATION_H
#define GISASSIMULATION_H

#include "Simulation2D.h"
#include "SimulationElement.h"
#include "SimulationResult.h"

class MultiLayer;
class IMultiLayerBuilder;
class IHistogram;
class Histogram2D;

//! Main class to run a Grazing-Incidence Small-Angle Scattering simulation.
//! @ingroup simulation

class BA_CORE_API_ GISASSimulation : public Simulation2D
{
public:
    GISASSimulation();
    GISASSimulation(const MultiLayer& p_sample);
    GISASSimulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder);

    ~GISASSimulation() {}

    GISASSimulation* clone() const override { return new GISASSimulation(*this); }

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Put into a clean state for running a simulation
    void prepareSimulation() override;

    //! Gets the number of elements this simulation needs to calculate
    size_t numberOfSimulationElements() const override;

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays
    SimulationResult result() const;

    //! Returns clone of the detector intensity map with detector resolution applied
    OutputData<double>* getDetectorIntensity(
            AxesUnits units_type = AxesUnits::DEFAULT) const override;

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

private:
    GISASSimulation(const GISASSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    void initialize();
};

#endif // GISASSIMULATION_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.h
//! @brief     Defines class SpecularSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSIMULATION_H
#define SPECULARSIMULATION_H

#include "Simulation.h"
#include "ILayerRTCoefficients.h"
#include "OutputData.h"

class IAxis;
class IComputation;
class IFootprintFactor;
class IMultiLayerBuilder;
class ISample;
class ISpecularDataHandler;
class MultiLayer;
class Histogram1D;
class SpecularSimulationElement;

//! Main class to run a specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulation : public Simulation
{
public:
    SpecularSimulation();
    SpecularSimulation(const MultiLayer& sample);
    SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    ~SpecularSimulation() override;

    SpecularSimulation* clone() const override;

    //! Put into a clean state for running a simulation.
    void prepareSimulation() override;

    void accept(INodeVisitor* visitor) const override final {visitor->visit(this);}

    size_t numberOfSimulationElements() const override;

    //! Returns the results of the simulation in a format that supports unit conversion and export
    //! to numpy arrays. If simulation was not run, returns an array of proper size filled with
    //! zeros.
    SimulationResult result() const override;

    void setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max,
                           const IFootprintFactor* beam_shape = nullptr);
    void setBeamParameters(double lambda, std::vector<double> incident_angle_values,
                           const IFootprintFactor* beam_shape = nullptr);
    //! Sets beam parameters for specular simulation. _lambda_ defines the wavelength of incoming
    //! beam (in nm), _alpha_axis_ defines the range of incident angles, while _beam_shape_
    //! (optional parameter) is required to take footprint effects into account.
    //! Incident angle axis can be defined as a numpy array of values. This overload
    //! facilitates defining non-uniform incident angle axis.
    //! Another overload accepts the number of bins (_nbins_), as well as
    //! minimal (_alpha_i_min_) and maximal (_alpha_i_max_) angle values.
    //! With using this overload a uniform angle axis in the given range is assigned to the beam.
    void setBeamParameters(double lambda, const IAxis& alpha_axis,
                           const IFootprintFactor* beam_shape = nullptr);

    //! Returns a pointer to coordinate axis.
    const IAxis* coordinateAxis() const;

private:
    SpecularSimulation(const SpecularSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    //! Generate simulation elements for given beam
    std::vector<SpecularSimulationElement> generateSimulationElements(const Beam& beam);

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    std::unique_ptr<IComputation> generateSingleThreadedComputation(size_t start,
                                                                    size_t n_elements) override;

    void checkCache() const;

    //! Checks the distribution validity for simulation.
    void validateParametrization(const ParameterDistribution& par_distr) const override;

    //! Initializes simulation
    void initialize();

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle
    //! for single simulation element specified by _index_.
    void normalizeIntensity(size_t index, double beam_intensity) override;

    void addBackGroundIntensity(size_t start_ind, size_t n_elements) override;

    void addDataToCache(double weight) override;

    void moveDataFromCache() override;

    //! Creates intensity data from simulation elements
    std::unique_ptr<OutputData<double>> createIntensityData() const;

    std::vector<double> rawResults() const override;
    void setRawResults(const std::vector<double>& raw_data) override;

    std::unique_ptr<ISpecularDataHandler> m_data_handler;
    std::vector<SpecularSimulationElement> m_sim_elements;
    std::vector<double> m_cache;
};

#endif // SPECULARSIMULATION_H

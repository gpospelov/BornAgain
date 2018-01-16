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
#include "SimulationElement.h"
#include "ILayerRTCoefficients.h"
#include "OutputData.h"

class IAxis;
class IComputation;
class ISample;
class IMultiLayerBuilder;
class MultiLayer;
class Histogram1D;

//! Main class to run a specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulation : public Simulation
{
public:
    SpecularSimulation();
    SpecularSimulation(const MultiLayer& sample);
    SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder);
    virtual ~SpecularSimulation();

    SpecularSimulation* clone() const override;

    //! Put into a clean state for running a simulation.
    void prepareSimulation() override;

    void accept(INodeVisitor* visitor) const override final {visitor->visit(this);}

    size_t numberOfSimulationElements() const override;

    //! Sets beam parameters with alpha_i of the beam defined in the range.
    void setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i = 0.0);
    void setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max,
                           double phi_i = 0.0);

    //! Returns a pointer to incident angle axis.
    const IAxis* getAlphaAxis() const;

    //! Returns detector count values in the form of OutputData<double>. Detector counts are
    //! proportional to \f$Reflectivity = |R|^2\f$ from the upper layer.
    OutputData<double>* getDetectorIntensity(
            AxesUnits units_type= AxesUnits::DEFAULT) const override;

    //! Returns reflectivity values \f$Reflectivity = |R|^2\f$ in the form of 1D Histogram
    //! for the upper sample layer.
    Histogram1D* reflectivity() const;

    //! Returns transmissivity values \f$Transmissivity = |T|^2\f$ in the form of 1D Histogram
    //! for the sample bottom layer.
    Histogram1D* transmissivity() const;

    //! Returns vector of reflection coefficients (\f$R\f$) for all alpha_i angles for given layer index.
    std::vector<complex_t> getScalarR(size_t i_layer) const;

    //! Returns vector of transmission coefficients for all alpha_i angles for given layer index.
    std::vector<complex_t> getScalarT(size_t i_layer) const;

    //! Returns vector of Kz coefficients for all alpha_i angles for given layer index.
    std::vector<complex_t> getScalarKz(size_t i_layer) const;

private:
    typedef complex_t (ILayerRTCoefficients::*DataGetter)() const;

    SpecularSimulation(const SpecularSimulation& other);

    //! Initializes the vector of Simulation elements
    void initSimulationElementVector() override;

    std::vector<complex_t> getData(size_t i_layer, DataGetter fn_ptr) const;

    std::unique_ptr<OutputData<double>> getDataByAbsValue(size_t i_layer, DataGetter fn_ptr) const;

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    std::unique_ptr<IComputation> generateSingleThreadedComputation(size_t start,
                                                                    size_t n_elements) override;

    //! Checks if simulation data is ready for retrieval
    void validityCheck(size_t i_layer) const;

    //! Initializes simulation
    void initialize();

    //! Normalize the detector counts to beam intensity, to solid angle, and to exposure angle
    //! for single simulation element specified by _index_.
    void normalizeIntensity(size_t index, double beam_intensity) override;

    void addBackGroundIntensity(size_t start_ind, size_t n_elements) override;

    void addDataToCache(double weight) override;

    void moveDataFromCache() override;

    std::vector<SimulationElement> m_sim_elements;
    std::vector<SimulationElement> m_cache;
};

#endif // SPECULARSIMULATION_H

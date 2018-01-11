// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/OffSpecSimulation.h
//! @brief     Defines class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef OFFSPECSIMULATION_H
#define OFFSPECSIMULATION_H

#include "Simulation.h"
#include "SimulationElement.h"

class Histogram2D;

//! Main class to run an off-specular simulation.
//! @ingroup simulation

class BA_CORE_API_ OffSpecSimulation : public Simulation
{
public:
    OffSpecSimulation();
    OffSpecSimulation(const MultiLayer& p_sample);
    OffSpecSimulation(const std::shared_ptr<class IMultiLayerBuilder> p_sample_builder);
    ~OffSpecSimulation() final {}

    OffSpecSimulation* clone() const { return new OffSpecSimulation(*this); }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    //! Put into a clean state for running a simulation
    void prepareSimulation() final;

    //! Gets the number of elements this simulation needs to calculate
    size_t numberOfSimulationElements() const final;

    //! Returns clone of the detector intensity map
    OutputData<double>* getDetectorIntensity(
        AxesUnits units_type = AxesUnits::DEFAULT) const {
        (void) units_type; return m_intensity_map.clone(); }

    //! Returns clone of the detector intensity map in the form of 2D histogram.
    Histogram2D* getIntensityData() const;

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_x, double x_min, double x_max,
                               size_t n_y, double y_min, double y_max);

private:
    OffSpecSimulation(const OffSpecSimulation& other);

    //! Generate a single threaded computation for a given range of simulation elements
    //! @param start Index of the first element to include into computation
    //! @param n_elements Number of elements to process
    virtual std::unique_ptr<IComputation>
    generateSingleThreadedComputation(size_t start, size_t n_elements) override;

    //! Initializes the vector of Simulation elements
    //! @param init_storage Initialize storage for accumulating results
    virtual void initSimulationElementVector(bool init_storage) override;

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    void transferResultsToIntensityMap() final;

    //! Default implementation only adds the detector axes
    void updateIntensityMap() final;

    //! Normalize, apply detector resolution and transfer detector image corresponding to
    //! alpha_i = mp_alpha_i_axis->getBin(index)
    void transferDetectorImage(size_t index);

    //! Check correct number of axes
    void checkInitialization() const;

    void initialize();

    virtual void normalizeIntensity(size_t index, double beam_intensity) override;

    virtual void addBackGroundIntensity(size_t start_ind, size_t n_elements) override;

    virtual bool isStorageInited() const override {return !m_storage.empty();}

    virtual void addDataToStorage(double weight) override;

    virtual void moveDataFromStorage() override;

    IAxis* mp_alpha_i_axis;
    OutputData<double> m_intensity_map;
    std::vector<SimulationElement> m_storage;
};

#endif // OFFSPECSIMULATION_H

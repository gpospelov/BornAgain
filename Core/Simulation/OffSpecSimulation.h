// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/OffSpecSimulation.h
//! @brief     Defines class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OFFSPECSIMULATION_H
#define OFFSPECSIMULATION_H

#include "Simulation.h"
#include "Instrument.h"

class Histogram2D;

//! Main class to run an off-specular simulation.
//! @ingroup simulation

class BA_CORE_API_ OffSpecSimulation : public Simulation
{
public:
    OffSpecSimulation();
    OffSpecSimulation(const ISample& p_sample);
    OffSpecSimulation(std::shared_ptr<class ISampleBuilder> p_sample_builder);
    virtual ~OffSpecSimulation() {}

    OffSpecSimulation* clone() const { return new OffSpecSimulation(*this); }

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const;

    //! Returns detector intensity map
    const OutputData<double>* getOutputData() const { return &m_intensity_map; }

    //! Returns clone of the detector intensity map
    OutputData<double>* getDetectorIntensity(
        IDetector2D::EAxesUnits units_type = IDetector2D::DEFAULT) const {
        (void) units_type; return m_intensity_map.clone(); }

    //! Returns clone of the detector intensity map in the form of 2D histogram.
    Histogram2D* getIntensityData() const;

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const { return m_instrument; }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity);

    //! Sets the beam polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t bloch_vector);

    //! Sets detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double>& output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_x, double x_min, double x_max,
                               size_t n_y, double y_min, double y_max);

    //! Define resolution function for detector
    void setDetectorResolutionFunction(const IResolutionFunction2D& resolution_function);

    //! Removes detector resolution function
    void removeDetectorResolutionFunction();

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission = 1.0);

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool* external_pool,
                                                    int copy_number = -1) const;

protected:
    OffSpecSimulation(const OffSpecSimulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters() {}

    //! Initializes the vector of Simulation elements
    virtual void initSimulationElementVector();

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap();

    //! Returns the intensity of the beam
    virtual double getBeamIntensity() const;

    //! Default implementation only adds the detector axes
    void updateIntensityMap();

    // components describing an off-specular experiment and its simulation:
    Instrument m_instrument;
    IAxis* mp_alpha_i_axis;
    OutputData<double> m_intensity_map;

private:
    //! Normalize, apply detector resolution and transfer detector image corresponding to
    //! alpha_i = mp_alpha_i_axis->getBin(index)
    void transferDetectorImage(int index);

    //! Check correct number of axes
    void checkInitialization() const;

    void initialize();
};

#endif // OFFSPECSIMULATION_H

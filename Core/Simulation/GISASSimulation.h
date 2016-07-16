// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/GISASSimulation.h
//! @brief     Declares class GISASSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GISASSIMULATION_H
#define GISASSIMULATION_H

#include "Instrument.h"
#include "Simulation.h"

//! @class Simulation
//! @ingroup simulation
//! @brief Main class to run the simulation.

class BA_CORE_API_ GISASSimulation : public Simulation
{
public:
    GISASSimulation();
    GISASSimulation(const class ISample& p_sample);
    GISASSimulation(std::shared_ptr<class ISampleBuilder> p_sample_builder);

    virtual ~GISASSimulation() {}

    GISASSimulation* clone() const { return new GISASSimulation(*this); }

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const;

    //! Returns detector intensity map (no detector resolution)
    const OutputData<double>* getOutputData() const { return &m_intensity_map; }

    //! Returns clone of the detector intensity map with detector resolution applied
    OutputData<double>* getDetectorIntensity(
        IDetector2D::EAxesUnits units_type = IDetector2D::DEFAULT) const;

    //! Returns clone of the detector intensity map with detector resolution applied in the form
    //! of 2D histogram.
    class Histogram2D* getIntensityData(
        IDetector2D::EAxesUnits units_type = IDetector2D::DEFAULT) const;

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const { return m_instrument; }
    Instrument& getInstrument() { return m_instrument; }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity);

    //! Sets the beam polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t bloch_vector);

    //! Sets the detector (axes can be overwritten later)
    void setDetector(const IDetector2D& detector);

    //! Sets detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double> &output_data);
    void setDetectorParameters(const class IHistogram& histogram);

    //! Sets spherical detector parameters using angle ranges
    //! @param n_phi number of phi-axis bins
    //! @param phi_min low edge of first phi-bin
    //! @param phi_max upper edge of last phi-bin
    //! @param n_alpha number of alpha-axis bins
    //! @param alpha_min low edge of first alpha-bin
    //! @param alpha_max upper edge of last alpha-bin
    void setDetectorParameters(size_t n_phi, double phi_min, double phi_max,
                               size_t n_alpha, double alpha_min, double alpha_max);

    //! Define resolution function for detector
    void setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function);

    //! Removes detector resolution function
    void removeDetectorResolutionFunction();

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t direction, double efficiency,
                               double total_transmission=1.0);

    //! removes all masks from the detector
    void removeMasks();

    //! Adds mask of given shape to the stack of detector masks. The mask value 'true' means
    //! that the channel will be excluded from the simulation. The mask which is added last
    //! has priority.
    //! @param shape The shape of mask (Rectangle, Polygon, Line, Ellipse)
    //! @param mask_value The value of mask
    void addMask(const class Geometry::IShape2D& shape, bool mask_value = true);

    //! Put the mask for all detector channels (i.e. exclude whole detector from the analysis)
    void maskAll();

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    GISASSimulation(const GISASSimulation& other);

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

    // extra components describing a GISAS experiment and its simulation:
    Instrument m_instrument;
    OutputData<double> m_intensity_map;
private:
    void initialize();
};

#endif // GISASSIMULATION_H

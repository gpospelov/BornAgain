// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/GISASSimulation.h
//! @brief     Defines class GISASSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GISASSIMULATION_H_
#define GISASSIMULATION_H_

#include "ISampleBuilder.h"
#include "Instrument.h"
#include "SimulationParameters.h"
#include "DistributionHandler.h"
#include "ProgressHandler.h"
#include "Simulation.h"

#include "EigenCore.h"

#include <boost/function.hpp>

class ProgramOptions;
class ProgressHandlerDWBA;

//! @class Simulation
//! @ingroup simulation
//! @brief Main class to run the simulation.

class BA_CORE_API_ GISASSimulation : public Simulation
{
public:
    GISASSimulation();
    GISASSimulation(const ProgramOptions *p_options);
    GISASSimulation(const ISample& p_sample, const ProgramOptions *p_options=0);
    GISASSimulation(SampleBuilder_t p_sample_builder,
               const ProgramOptions *p_options=0);
    ~GISASSimulation() {}

    GISASSimulation *clone() const;

    //! Put into a clean state for running a simulation
    virtual void prepareSimulation();

    //! Normalize the detector counts
    void normalize();

    //! Gets the number of elements this simulation needs to calculate
    virtual int getNumberOfSimulationElements() const;

    //! Returns detector intensity map for all scan parameters (no detector resolution)
    const OutputData<double>* getOutputData() const { return &m_intensity_map; }

    //! Clone detector intensity map for all scan parameters (apply detector resolution function first)
    OutputData<double>* getIntensityData() const;

    //! Sets the instrument containing beam and detector information
    void setInstrument(const Instrument& instrument);

    //! Returns the instrument containing beam and detector information
    const Instrument& getInstrument() const { return m_instrument; }

    //! Sets beam parameters from here (forwarded to Instrument)
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets beam intensity from here (forwarded to Instrument)
    void setBeamIntensity(double intensity);

    //! Sets the beam polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t& bloch_vector);

    //! Sets detector parameters using axes of output data
    void setDetectorParameters(const OutputData<double> &output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
        size_t n_alpha, double alpha_f_min, double alpha_f_max,
        bool isgisaxs_style=false);

    //! Sets detector parameters using parameter object
    void setDetectorParameters(const DetectorParameters& params);

    //! Define resolution function for detector
    void setDetectorResolutionFunction(
        const IResolutionFunction2D &resolution_function);

    //! Removes detector resolution function
    void removeDetectorResolutionFunction();

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t &direction, double efficiency,
                               double total_transmission=1.0);

    //! Adds parameters from local to external pool, and call recursion over direct children
    std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const;

    //! OffSpecSimulation needs protected copy constructor
    friend class OffSpecSimulation;

    //! returns wavelength
    virtual double getWavelength() const;

protected:
    GISASSimulation(const GISASSimulation& other);

    //! Registers some class members for later access via parameter pool
    void init_parameters();

    //! Initializes the vector of Simulation elements
    virtual void initSimulationElementVector();

    //! Creates the appropriate data structure (e.g. 2D intensity map) from the calculated
    //! SimulationElement objects
    virtual void transferResultsToIntensityMap();

    //! Default implementation only adds the detector axes
    void updateIntensityMap();

    // extra components describing a GISAS experiment and its simulation:
    Instrument m_instrument;
    OutputData<double> m_intensity_map;
};

#endif /* GISASSIMULATION_H_ */

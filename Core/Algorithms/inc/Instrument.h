// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Instrument.h
//! @brief     Defines class Instrument.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_

#include "Beam.h"
#include "IDetector2D.h"
#include "IResolutionFunction2D.h"

#include <boost/scoped_ptr.hpp>

//! @class Instrument
//! @ingroup simulation_internal
//! @brief Assembles beam, detector and their relative positions wrt the sample.

class BA_CORE_API_ Instrument : public IParameterized
{
public:
    Instrument();
    Instrument(const Instrument &other);
    Instrument& operator=(const Instrument& other);

    ~Instrument(){}

    //! Returns the beam data
    Beam getBeam() const;

    //! Sets the beam data
    void setBeam(const Beam &beam);

    //! Sets the beam wavelength and incoming angles
    void setBeamParameters(double wavelength, double alpha_i, double phi_i);

    //! Sets the beam's intensity
    void setBeamIntensity(double intensity)
    {
        m_beam.setIntensity(intensity);
    }

    //! Sets the beam's polarization according to the given Bloch vector
    void setBeamPolarization(const kvector_t &bloch_vector)
    {
        m_beam.setPolarization(bloch_vector);
    }

    //! Returns the beam's intensity
    double getIntensity() const
    {
        return m_beam.getIntensity();
    }

    //! Returns the detector data
    const IDetector2D *getDetector() const;
    IDetector2D *getDetector();

    //! Returns a detector axis
    const IAxis &getDetectorAxis(size_t index) const;

    //! Returns the detector's dimension
    size_t getDetectorDimension() const
    {
        return mP_detector->getDimension();
    }

    //! Sets the detector (axes can be overwritten later)
    void setDetector(const IDetector2D& detector);

    //! Sets detector parameters using axes of output data
    void matchDetectorAxes(const OutputData<double> &output_data);

    //! Sets detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max, size_t n_alpha,
                               double alpha_f_min, double alpha_f_max, bool isgisaxs_style = false);

    //! Sets detector parameters using axes
    void setDetectorAxes(const IAxis &axis0, const IAxis &axis1);

    //! Sets detector resolution function
    void setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function);
    void setDetectorResolutionFunction(const IResolutionFunction2D &p_resolution_function);

    //! Sets the polarization analyzer characteristics of the detector
    void setAnalyzerProperties(const kvector_t &direction, double efficiency,
                               double total_transmission=1.0) {
        mP_detector->setAnalyzerProperties(direction, efficiency, total_transmission);
    }

    //! apply the detector resolution to the given intensity map
    void applyDetectorResolution(OutputData<double> *p_intensity_map) const;

    //! Adds parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

#ifndef GCCXML_SKIP_THIS
    //! normalize a detector image
    void normalize(OutputData<double> *p_intensity) const;

    //! Create a vector of SimulationElement objects according to the beam, detector and its mask
    std::vector<SimulationElement> createSimulationElements();
#endif

protected:
    virtual void print(std::ostream &ostr) const;

    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

    boost::scoped_ptr<IDetector2D> mP_detector;
    Beam m_beam;
};

inline Beam Instrument::getBeam() const
{
    return m_beam;
}

inline void Instrument::setBeam(const Beam &beam)
{
    m_beam = beam;
}

inline void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    m_beam.setCentralK(wavelength, alpha_i, phi_i);
}

inline const IDetector2D *Instrument::getDetector() const
{
    return mP_detector.get();
}

inline IDetector2D *Instrument::getDetector()
{
    return mP_detector.get();
}

inline const IAxis &Instrument::getDetectorAxis(size_t index) const
{
    return mP_detector->getAxis(index);
}

#endif /* INSTRUMENT_H_ */

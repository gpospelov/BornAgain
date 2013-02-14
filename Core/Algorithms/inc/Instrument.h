#ifndef INSTRUMENT_H_
#define INSTRUMENT_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Instrument.h
//! @brief  Definition of Instrument class
//! @author Scientific Computing Group at FRM II
//! @date   Feb 14, 2013

#include "Beam.h"
#include "Detector.h"

//- -------------------------------------------------------------------
//! @class Instrument
//! @brief Definition of Instrument object that assembles the information
//! of the beam, detector and their relative positions wrt the sample
//- -------------------------------------------------------------------
class Instrument : public IParameterized
{
public:
    Instrument();
    ~Instrument() {}

    //! get the beam data
    Beam getBeam() const;

    //! set the beam data
    void setBeam(Beam beam);

    //! get the detector data
    Detector getDetector() const;

    //! set detector parameters using axes of output data
    void matchDetectorParameters(const OutputData<double > &output_data);

    //! set detector parameters using angle ranges
    void setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style=false);

    //! set detector parameters using parameter object
    void setDetectorParameters(const DetectorParameters &params);

    //! add parameters from local pool to external pool and call recursion over direct children
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    Detector m_detector;
    Beam m_beam;
};

inline Beam Instrument::getBeam() const
{
    return m_beam;
}

inline void Instrument::setBeam(Beam beam)
{
    m_beam = beam;
}

inline Detector Instrument::getDetector() const
{
    return m_detector;
}

#endif /* INSTRUMENT_H_ */

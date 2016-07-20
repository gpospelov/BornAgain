// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Beam.h
//! @brief     Declares class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAM_H
#define BEAM_H

#include "EigenCore.h"
#include "IParameterized.h"
#include "Vectors3D.h"

//! @class Beam
//! @ingroup simulation
//! @brief Ideal collimated beam defined by wavelength, direction and intensity.

class BA_CORE_API_ Beam : public IParameterized
{
public:
    Beam();
    Beam(const Beam& other);
    Beam& operator=(const Beam& other);

    virtual ~Beam() {}

    //! Get the value of the wavevector
    kvector_t getCentralK() const;

    //! Sets the value of the incoming wavevector in terms of wavelength
    //! and incoming angles
    void setCentralK(double wavelength, double alpha_i, double phi_i);

    //! Gets the beam intensity in neutrons/sec
    double getIntensity() const { return m_intensity; }

    //! Sets the beam intensity in neutrons/sec
    void setIntensity(double intensity) { m_intensity = intensity; }

    //! Sets the polarization density matrix according to the given Bloch vector
    void setPolarization(const kvector_t bloch_vector);

#ifndef SWIG
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const  { return m_polarization; }
#endif

    double getWavelength() const { return m_wavelength; }
    double getAlpha() const { return m_alpha; }
    double getPhi() const { return m_phi; }

protected:
    virtual void print(std::ostream& ostr) const;

    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

private:
    //! Swap method.
    void swapContent(Beam& other);

    //! Initialize polarization (for constructors).
    void initPolarization();

#ifndef SWIG
    Eigen::Matrix2cd calculatePolarization(const kvector_t bloch_vector) const;
#endif

    double m_wavelength, m_alpha, m_phi; //!< wavelength and angles of beam
    double m_intensity;                  //!< beam intensity (neutrons/sec)
#ifndef SWIG
    Eigen::Matrix2cd m_polarization;     //!< polarization density matrix
#endif
};

#endif // BEAM_H

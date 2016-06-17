// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/Beam.h
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
    double getIntensity() const;

    //! Sets the beam intensity in neutrons/sec
    void setIntensity(double intensity);

    //! Sets the polarization density matrix according to the given Bloch vector
    void setPolarization(const kvector_t bloch_vector);

#ifndef SWIG
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const;
#endif

    double getWavelength() const;
    double getAlpha() const;
    double getPhi() const;

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

inline double Beam::getIntensity() const
{
    return m_intensity;
}

inline void Beam::setIntensity(double intensity)
{
    m_intensity = intensity;
}

#ifndef SWIG
inline Eigen::Matrix2cd Beam::getPolarization() const
{
    return m_polarization;
}
#endif

inline double Beam::getWavelength() const
{
    return m_wavelength;
}

inline double Beam::getAlpha() const
{
    return m_alpha;
}

inline double Beam::getPhi() const
{
    return m_phi;
}

#endif // BEAM_H

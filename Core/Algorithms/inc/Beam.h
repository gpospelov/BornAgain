// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/Beam.h
//! @brief     Defines class Beam.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BEAM_H_
#define BEAM_H_

#include "WinDllMacros.h"
#include "Types.h"
#include "IParameterized.h"

#ifndef GCCXML_SKIP_THIS
#include <Eigen/Core>
#endif

//! Ideal collimated Beam defined by wavelength, direction and intensity.

class BA_CORE_API_ Beam : public IParameterized
{
 public:
    Beam();
    Beam(const Beam& other);
    Beam& operator=(const Beam& other);

    virtual ~Beam() {}

    //! Get the value of the wavevector
    cvector_t getCentralK() const { return m_central_k; }

    //! Sets the value of the incoming wavevector
    void setCentralK(const cvector_t& k_i);

    //! Sets the value of the incoming wavevector in terms of wavelength
    //! and incoming angles
    void setCentralK(double lambda, double alpha_i, double phi_i);

    //! Gets the beam intensity in neutrons/sec
    double getIntensity() const { return m_intensity; }

    //! Sets the beam intensity in neutrons/sec
    void setIntensity(double intensity) { m_intensity = intensity; }

#ifndef GCCXML_SKIP_THIS
    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const { return m_polarization; }
#endif

#ifndef GCCXML_SKIP_THIS
    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd &polarization);
#endif

    //! Sets the polarization density matrix to a value representing
    //! a mixed ensemble with the given fraction of positive z spin
    void SetSpinUpFraction(double up_fraction);

#ifndef GCCXML_SKIP_THIS
    //! Checks if the given matrix can represent a physical density matrix
    bool checkPolarization(const Eigen::Matrix2cd &polarization) const;
#endif

 protected:
    //! Registers some class members for later access via parameter pool
    virtual void init_parameters();

 private:
    //! swap function
    void swapContent(Beam& other);

    //! Initialize polarization (for constructors)
    void initPolarization();

    cvector_t m_central_k;  //!< incoming wavevector
    double m_intensity;     //!< beam intensity (neutrons/sec)
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_polarization; //!< polarization density matrix
#endif
};

#endif /* BEAM_H_ */





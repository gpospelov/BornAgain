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

#include "Types.h"
#include "IParameterized.h"

//! Ideal collimated Beam defined by wavelength, direction and intensity.

class Beam : public IParameterized
{
public:
    Beam();
    Beam(const Beam &other);
    Beam &operator=(const Beam &other);

    virtual ~Beam() {}

    cvector_t getCentralK() const { return m_central_k; }
    
    void setCentralK(const cvector_t &k_i);
    void setCentralK(double lambda, double alpha_i, double phi_i);

    double getIntensity() const { return m_intensity; }

    void setIntensity(double intensity) { m_intensity = intensity; }

protected:
    //! Register some class members for later access via parameter pool
    virtual void init_parameters();

private:
    //! swap function
    void swapContent(Beam &other);

    cvector_t m_central_k;
    double m_intensity;
};

#endif /* BEAM_H_ */

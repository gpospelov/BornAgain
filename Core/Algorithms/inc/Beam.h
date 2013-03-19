// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/Beam.h 
//! @brief     Defines class Beam.
//
// ************************************************************************** //

#ifndef BEAM_H_
#define BEAM_H_

#include "Types.h"
#include "IParameterized.h"

//- -------------------------------------------------------------------
//! @class Beam
//! @brief Definition of Beam with direction and defined intensity
//- -------------------------------------------------------------------
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
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    //! swap function
    void swapContent(Beam &other);

	cvector_t m_central_k;
    double m_intensity;
};


#endif /* BEAM_H_ */

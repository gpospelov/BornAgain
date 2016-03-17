// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPolarizedMeso.h
//! @brief     Defines class TestPolarizedMeso.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPOLARIZEDMESO_H_
#define TESTPOLARIZEDMESO_H_

#include "IApplicationTest.h"
#include "MultiLayer.h"

class MesoCrystal;
class Lattice;

//! Functional test for polarized DWBA with mesocrystal.

class TestPolarizedMeso : public IApplicationTest
{
public:
    TestPolarizedMeso();
    virtual ~TestPolarizedMeso();

    virtual void execute();

private:
    MultiLayer *createSample() const;
    MesoCrystal* createMeso(double a, double c, const IMaterial &p_material,
            double cube_size, const IFormFactor* p_meso_form_factor) const;
    const Lattice *createLattice(double a, double c) const;
    MultiLayer *mp_sample; //!< pointer to multilayer sample
    double m_meso_width;
    double m_surface_filling_ratio;
    double m_meso_size_steps;
//    double m_sigma_meso_height;
//    double m_sigma_meso_radius;
    double m_lattice_length_a;
    double m_lattice_length_c;
    double m_nanoparticle_size;
    double m_sigma_nanoparticle_size;
//    double m_sigma_lattice_length_a;
    double m_roughness;
};




#endif /* TESTPOLARIZEDMESO_H_ */

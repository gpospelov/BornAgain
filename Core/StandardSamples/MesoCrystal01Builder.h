// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/MesoCrystal01Builder.h
//! @brief     Defines class MesoCrystal01Builder.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MESOCRYSTAL01BUILDER_H
#define MESOCRYSTAL01BUILDER_H

#include "ISampleBuilder.h"
#include "Types.h"

class Lattice;
class MesoCrystal;


//! @class MesoCrystal01Builder
//! @ingroup standard_samples
//! @brief Builds sample: mesocrystals of cylindrical shape composed by
//! spherical nanoparticles.

class BA_CORE_API_  MesoCrystal01Builder : public ISampleBuilder
{
public:
    MesoCrystal01Builder();

    virtual ~MesoCrystal01Builder(){}
    virtual ISample *buildSample() const;

protected:
    virtual void init_parameters();

private:
    MesoCrystal *createMesoCrystal(double stacking_radius_a, double stacking_radius_c, complex_t n_particle, const IFormFactor *p_meso_form_factor) const;
    const Lattice *createLattice(double stacking_radius_a, double stacking_radius_c) const;
    double m_lattice_length_a;
    double m_lattice_length_c;
    double m_nanoparticle_radius;
    double m_sigma_nanoparticle_radius;
    double m_meso_height;
    double m_meso_radius;
    double m_sigma_meso_height;
    double m_sigma_meso_radius;
    double m_sigma_lattice_length_a;
    double m_surface_filling_ratio;
    double m_roughness;
    double m_nphi_rotations;
};


#endif // MESOCRYSTAL01BUILDER_H


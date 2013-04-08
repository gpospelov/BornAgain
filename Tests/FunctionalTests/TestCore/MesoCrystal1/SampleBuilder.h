#ifndef MESOSAMPLEBUILDER_H
#define MESOSAMPLEBUILDER_H

#include "ISampleBuilder.h"
#include "Types.h"
class MesoCrystal;
class Lattice;
class IFormFactor;

namespace FunctionalTests {

//! Builds sample using set of input parameters.
//! Mesocrystal of cylindrical shape composed by sperical nanoparticles
//! at FCC lattice points
class SampleBuilder : public ISampleBuilder
{
public:
    SampleBuilder();

    virtual ~SampleBuilder(){}
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
};

}



#endif // SAMPLEBUILDER_H

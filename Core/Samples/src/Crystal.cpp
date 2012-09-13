#include "Crystal.h"
#include "FormFactorCrystal.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "Units.h"
#include "MathFunctions.h"
#include "FormFactorFullSphere.h"
#include "DiffuseParticleInfo.h"

Crystal::Crystal(const LatticeBasis& lattice_basis,
        const Lattice& lattice)
: m_lattice(lattice)
, m_dw_factor(0.0)
{
    setName("Crystal");
    mp_lattice_basis = lattice_basis.clone();
    registerChild(mp_lattice_basis);
}

Crystal::~Crystal()
{
    delete mp_lattice_basis;
}

Crystal* Crystal::clone() const
{
    Crystal *p_new = new Crystal(*mp_lattice_basis, m_lattice);
    p_new->setDWFactor(m_dw_factor);
    return p_new;
}

IFormFactor* Crystal::createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor,
        complex_t ambient_refractive_index) const
{
    IFormFactor *p_ff_crystal = new FormFactorCrystal(this, meso_crystal_form_factor, ambient_refractive_index);
    if (m_dw_factor>0.0) {
        return new FormFactorDecoratorDebyeWaller(p_ff_crystal, m_dw_factor);
    }
    return p_ff_crystal;
}

std::vector<DiffuseParticleInfo*>* Crystal::createDiffuseParticleInfo(
        const ParticleInfo& parent_info) const
{
    double primitive_cell_volume = m_lattice.getVolume();
    double parent_volume = parent_info.getParticle()->getSimpleFormFactor()->getVolume();
    const Geometry::Transform3D *p_parent_transform = parent_info.getTransform3D();
    double depth = parent_info.getDepth();
    double weight = parent_info.getAbundance();
    double np_density = 3.0*parent_volume/primitive_cell_volume;
    //TODO: refine this method; current implementation only serves as a test
    double height = 0.2*Units::micrometer;
    size_t nbr_heights = 181;
    double mean_radius = 5.1*Units::nanometer;
    double sigma = 2.0*Units::nanometer;
    size_t nbr_radii = 13;
    complex_t n_particle(0.999966, 5.62664e-7);
    std::vector<DiffuseParticleInfo *> *p_infos = new std::vector<DiffuseParticleInfo *>();
    double total_prob = 0.0;
    for (size_t i=0; i<nbr_radii; ++i) {
        double radius = (mean_radius-1.5*sigma) + 3.0*sigma/(nbr_radii-1);
        total_prob += MathFunctions::Gaussian(radius, mean_radius, sigma);
    }
    total_prob *= nbr_heights;
    for (size_t i=0; i<nbr_radii; ++i) {
        double radius;
        if (nbr_radii<2) {
            radius = mean_radius;
        }
        else {
            radius = (mean_radius-2.0*sigma) + 4.0*sigma*i/(nbr_radii-1);
        }
        double particle_weight = weight*MathFunctions::Gaussian(radius, mean_radius, sigma)/total_prob;
        Particle particle(n_particle, new FormFactorFullSphere(radius));
        DiffuseParticleInfo *p_new_np_info;
        if (nbr_heights<2) {
            Geometry::Transform3D *p_new_transform(0);
            if(p_parent_transform) p_new_transform = new Geometry::Transform3D(*p_parent_transform);
            p_new_np_info = new DiffuseParticleInfo(particle.clone(),
                    p_new_transform, 5.0*Units::nanometer, particle_weight);
            p_new_np_info->setNumberPerMeso(np_density*particle_weight);
            p_infos->push_back(p_new_np_info);
        }
        else {
            for (size_t j=0; j<nbr_heights; ++j) {
//                double particle_depth = depth - height*MathFunctions::GenerateUniformRandom();
                double particle_depth = depth - j*height/(nbr_heights-1);
                p_new_np_info = new DiffuseParticleInfo(particle.clone(),
                                    new Geometry::Transform3D(*p_parent_transform), particle_depth, particle_weight);
                p_new_np_info->setNumberPerMeso(np_density*particle_weight);
                p_infos->push_back(p_new_np_info);
            }
        }
    }
    return p_infos;
}

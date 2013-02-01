#include "Crystal.h"
#include "FormFactors.h"
#include "Units.h"
#include "MathFunctions.h"
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
    std::vector<DiffuseParticleInfo *> *p_result = new std::vector<DiffuseParticleInfo *>(
            mp_lattice_basis->createDiffuseParticleInfos());
    if (p_result->empty()) return p_result;

    double primitive_cell_volume = m_lattice.getVolume();
    double parent_volume = parent_info.getParticle()->getSimpleFormFactor()->getVolume();
    double parent_height = parent_info.getParticle()->getSimpleFormFactor()->getHeight();
    double parent_depth = parent_info.getDepth();

    const Geometry::Transform3D *p_parent_transform = parent_info.getTransform3D();

    double nbr_unit_cells = parent_volume/primitive_cell_volume;

    for (size_t i=0; i<p_result->size(); ++i) {
        DiffuseParticleInfo *p_info = (*p_result)[i];
        p_info->setTransform(*p_parent_transform);
        p_info->setDepth(parent_depth);
        p_info->setNumberPerMeso(nbr_unit_cells*p_info->getNumberPerMeso());
        p_info->setHeightRange(parent_height);
    }

    return p_result;
}

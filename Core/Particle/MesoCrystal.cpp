// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/MesoCrystal.cpp
//! @brief     Implements class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MesoCrystal.h"
#include "BornAgainNamespace.h"
#include "FormFactorDecoratorPositionFactor.h"
#include "FormFactorDecoratorRotation.h"
#include "IClusteredParticles.h"

MesoCrystal::MesoCrystal(const IClusteredParticles& particle_structure,
                         const IFormFactor& form_factor)
    : mp_particle_structure(particle_structure.clone()), mp_meso_form_factor(form_factor.clone())
{
    initialize();
}

MesoCrystal::~MesoCrystal()
{}

MesoCrystal* MesoCrystal::clone() const
{
    MesoCrystal* p_result
        = new MesoCrystal(mp_particle_structure->clone(), mp_meso_form_factor->clone());
    p_result->setAbundance(m_abundance);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

MesoCrystal* MesoCrystal::cloneInvertB() const
{
    MesoCrystal* p_result
        = new MesoCrystal(mp_particle_structure->cloneInvertB(), mp_meso_form_factor->clone());
    p_result->setAbundance(m_abundance);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

void MesoCrystal::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

IFormFactor*MesoCrystal::createSlicedFormFactor(ZLimits limits) const
{
    if (!mp_particle_structure || !mp_meso_form_factor)
        return nullptr;
    std::unique_ptr<IRotation> P_rotation(IRotation::createIdentity());
    if (mP_rotation)
        P_rotation.reset(mP_rotation->clone());
    std::unique_ptr<IFormFactor> P_temp_ff(
                mp_meso_form_factor->createSlicedFormFactor(limits, *P_rotation, m_position));
    IFormFactor* p_result = mp_particle_structure->createTotalFormFactor(
                                *P_temp_ff, P_rotation.get(), m_position);
    return p_result;
}

SlicedParticle MesoCrystal::createSlicedParticle(ZLimits limits) const
{
    if (!mp_particle_structure || !mp_meso_form_factor)
        return {};
    std::unique_ptr<IRotation> P_rotation(IRotation::createIdentity());
    if (mP_rotation)
        P_rotation.reset(mP_rotation->clone());
    std::unique_ptr<IFormFactor> P_temp_ff(
                mp_meso_form_factor->createSlicedFormFactor(limits, *P_rotation, m_position));
    std::unique_ptr<IFormFactor> P_total_ff( mp_particle_structure->createTotalFormFactor(
                                                 *P_temp_ff, P_rotation.get(), m_position) );
    double meso_volume = mp_meso_form_factor->volume();
    auto regions = mp_particle_structure->homogeneousRegions();
    for (auto& region : regions)
        region.m_volume *= meso_volume;
    SlicedParticle result;
    result.mP_slicedff = std::move(P_total_ff);
    result.m_regions = regions;
    return result;
}

std::vector<const INode*> MesoCrystal::getChildren() const
{
    return std::vector<const INode*>() <<  IParticle::getChildren()
                                       << mp_particle_structure << mp_meso_form_factor;
}

MesoCrystal::MesoCrystal(IClusteredParticles* p_particle_structure, IFormFactor* p_form_factor)
    : mp_particle_structure(p_particle_structure), mp_meso_form_factor(p_form_factor)
{
    initialize();
}

void MesoCrystal::initialize()
{
    setName(BornAgain::MesoCrystalType);
    registerParticleProperties();
    registerChild(mp_particle_structure.get());
    registerChild(mp_meso_form_factor.get());
}

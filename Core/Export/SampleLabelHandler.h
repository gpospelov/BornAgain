//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.h
//! @brief     Defines classes LabelMap and SampleLabelHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_CORE_EXPORT_SAMPLELABELHANDLER_H
#define BORNAGAIN_CORE_EXPORT_SAMPLELABELHANDLER_H

#include "Core/Export/OrderedMap.h"
#include <map>
#include <vector>

class Crystal;
class IAbstractParticle;
class ParticleLayout;
class Material;
class ISample;
class IRotation;
class Lattice2D;
class Lattice3D;
class MultiLayer;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;
class MesoCrystal;

template <class Key> class LabelMap : public OrderedMap<Key, std::string> {};

//! The handler which construct labels for sample variables during python script generation.
//! @ingroup tools_internal

class SampleLabelHandler {
public:
    typedef LabelMap<const Crystal*> crystals_t;
    typedef LabelMap<const ParticleLayout*> layouts_t;
    typedef LabelMap<const Material*> materials_t;
    typedef LabelMap<const Lattice2D*> lattices2D_t;
    typedef LabelMap<const Lattice3D*> lattices3D_t;
    typedef LabelMap<const MesoCrystal*> mesocrystals_t;
    typedef LabelMap<const MultiLayer*> multilayers_t;
    typedef LabelMap<const ParticleComposition*> particlecompositions_t;
    typedef LabelMap<const ParticleDistribution*> particledistributions_t;
    typedef LabelMap<const Particle*> particles_t;
    typedef LabelMap<const ParticleCoreShell*> particlescoreshell_t;
    typedef LabelMap<const IRotation*> rotations_t;

    SampleLabelHandler() {}
    crystals_t* crystalMap() { return &m_CrystalLabel; }
    layouts_t* particleLayoutMap() { return &m_ParticleLayoutLabel; }
    materials_t* materialMap() { return &m_MaterialLabel; }
    lattices2D_t* lattice2DMap() { return &m_Lattice2DLabel; }
    lattices3D_t* lattice3DMap() { return &m_Lattice3DLabel; }
    mesocrystals_t* mesocrystalMap() { return &m_MesoCrystalLabel; }
    multilayers_t* multiLayerMap() { return &m_MultiLayerLabel; }
    particlecompositions_t* particleCompositionMap() { return &m_ParticleCompositionLabel; }
    particledistributions_t* particleDistributionsMap() { return &m_ParticleDistributionLabel; }
    particles_t* particleMap() { return &m_ParticleLabel; }
    particlescoreshell_t* particleCoreShellMap() { return &m_ParticleCoreShellLabel; }
    rotations_t* rotationsMap() { return &m_RotationsLabel; }

    std::string labelCrystal(const Crystal* sample);
    std::string labelLayout(const ParticleLayout* sample);
    std::string labelMaterial(const Material* sample);
    std::string labelLattice2D(const Lattice2D* sample);
    std::string labelLattice3D(const Lattice3D* sample);
    std::string labelMultiLayer(const MultiLayer* sample);
    std::string labelParticle(const IAbstractParticle* sample);
    std::string labelRotation(const IRotation* sample);

    void insertCrystal(const Crystal* sample);
    void insertLayout(const ParticleLayout* sample);
    void insertMaterial(const Material* sample);
    void insertLattice2D(const Lattice2D* sample);
    void insertLattice3D(const Lattice3D* sample);
    void insertMesoCrystal(const MesoCrystal* sample);
    void insertMultiLayer(const MultiLayer* sample);
    void insertParticleComposition(const ParticleComposition* sample);
    void insertParticleDistribution(const ParticleDistribution* sample);
    void insertParticle(const Particle* sample);
    void insertParticleCoreShell(const ParticleCoreShell* sample);
    void insertRotation(const IRotation* sample);

    void insertKeyedObject(const std::string& key, const ISample* s);

    template <class T> std::vector<const T*> objectsOfType() const;
    std::string obj2key(const ISample* s) const;

private:
    crystals_t m_CrystalLabel;
    layouts_t m_ParticleLayoutLabel;
    materials_t m_MaterialLabel;
    lattices2D_t m_Lattice2DLabel;
    lattices3D_t m_Lattice3DLabel;
    mesocrystals_t m_MesoCrystalLabel;
    multilayers_t m_MultiLayerLabel;
    particlecompositions_t m_ParticleCompositionLabel;
    particledistributions_t m_ParticleDistributionLabel;
    particles_t m_ParticleLabel;
    particlescoreshell_t m_ParticleCoreShellLabel;
    rotations_t m_RotationsLabel;

    std::map<std::string, std::vector<const ISample*>> m_objects;
};


template <class T> std::vector<const T*> SampleLabelHandler::objectsOfType() const {
    std::vector<const T*> ret;
    for (auto it: m_objects)
        for (const ISample* s : it.second)
            if (const auto* c = dynamic_cast<const T*>(s); c)
                ret.emplace_back(c);
    return ret;
}

#endif // BORNAGAIN_CORE_EXPORT_SAMPLELABELHANDLER_H

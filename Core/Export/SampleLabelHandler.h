// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.h
//! @brief     Declares SampleLabelHandler class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLELABELHANDLER_H
#define SAMPLELABELHANDLER_H

#include "Exceptions.h"
#include <cassert>
#include <list>
#include <map>

#include <iostream>

class IAbstractParticle;
class IFormFactor;
class IInterferenceFunction;
class ILayout;
class IMaterial;
class IRotation;
class Layer;
class LayerRoughness;
class MultiLayer;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;

template<class Key>
class LabelMap
{
public:
    typedef std::pair<Key, std::string> entry_t;
    typedef std::list<entry_t> list_t;
    typedef typename list_t::iterator iterator;
    typedef typename list_t::const_iterator const_iterator;
    typedef std::map<Key, iterator> map_t;

    LabelMap() {}
    virtual ~LabelMap(){}

    void clear() {
        m_map.clear();
        m_list.clear();
    }

    const_iterator begin() const { return m_list.begin(); }
    const_iterator end() const { return m_list.end(); }
    iterator begin() { return m_list.begin(); }
    iterator end() { return m_list.end(); }

    size_t size() {
        assert(m_list.size() == m_map.size());
        return m_list.size();
    }

    // if such key exists, pair will be deleted, and new pair appended to the end
    void insert(const Key& key, const std::string& object) {
        erase(key);
        iterator it = m_list.insert(m_list.end(), std::make_pair(key, object));
        m_map[key] = it;
    }

    const iterator find(const Key& key) const {
        if(m_map.find(key) == m_map.end())
            return m_list.end();
        return m_map[key];
    }

    iterator find(const Key& key) {
        if(m_map.find(key) == m_map.end())
            return m_list.end();
        return m_map[key];
    }

    size_t erase(const Key& key) {
        if(m_map.find(key) == m_map.end())
            return 0;
        iterator it = m_map[key];
        m_list.erase(it);
        m_map.erase(key);
        return 1;
    }

    const std::string& value(const Key& key) {
        typename map_t::const_iterator mit = m_map.find(key);
        if(mit == m_map.end())
            throw Exceptions::RuntimeErrorException("LabelMap::value() -> No such key");
        const_iterator it = mit->second;
        return (*it).second;
    }

    const std::string& operator[](const Key& key) { return value(key); }

private:
    map_t m_map;
    list_t m_list;
};

//! @class SampleLabelHandler
//! @ingroup tools_internal
//! @brief The handler which construct labels for sample variables during python script generation

class BA_CORE_API_ SampleLabelHandler
{
public:
    typedef LabelMap<const IFormFactor*> formfactors_t;
    typedef LabelMap<const IInterferenceFunction*> interferences_t;
    typedef LabelMap<const ILayout*> layouts_t;
    typedef LabelMap<const IMaterial*> materials_t;
    typedef LabelMap<const IRotation*> rotations_t;
    typedef LabelMap<const Layer*> layers_t;
    typedef LabelMap<const LayerRoughness*> roughnesses_t;
    typedef LabelMap<const MultiLayer*> multilayers_t;
    typedef LabelMap<const Particle*> particles_t;
    typedef LabelMap<const ParticleComposition*> particlecompositions_t;
    typedef LabelMap<const ParticleCoreShell*> particlescoreshell_t;
    typedef LabelMap<const ParticleDistribution*> particledistributions_t;

    SampleLabelHandler() {}
    formfactors_t* getFormFactorMap();
    interferences_t* getInterferenceFunctionMap();
    layers_t* getLayerMap();
    layouts_t* getParticleLayoutMap();
    materials_t* getMaterialMap();
    multilayers_t* getMultiLayerMap();
    particlecompositions_t* getParticleCompositionMap();
    particledistributions_t* getParticleDistributionsMap();
    particles_t* getParticleMap();
    particlescoreshell_t* getParticleCoreShellMap();
    rotations_t* getRotationsMap();
    roughnesses_t* getLayerRoughnessMap();

    std::string getLabel(const IAbstractParticle* sample);
    std::string getLabel(const IFormFactor* sample);
    std::string getLabel(const IInterferenceFunction* sample);
    std::string getLabel(const ILayout* sample);
    std::string getLabel(const IMaterial* sample);
    std::string getLabel(const IRotation* sample);
    std::string getLabel(const Layer* sample);
    std::string getLabel(const LayerRoughness* sample);
    std::string getLabel(const MultiLayer* sample);
    std::string getLabel(const ParticleComposition* sample);
    std::string getLabel(const ParticleCoreShell* sample);
    std::string getLabel(const ParticleDistribution* sample);

    void insertMaterial(const IMaterial* sample);
    void setLabel(const IFormFactor* sample);
    void setLabel(const IInterferenceFunction* sample);
    void setLabel(const ILayout* sample);
    void setLabel(const IRotation* sample);
    void setLabel(const Layer* sample);
    void setLabel(const LayerRoughness* sample);
    void setLabel(const MultiLayer* sample);
    void setLabel(const Particle* sample);
    void setLabel(const ParticleComposition* sample);
    void setLabel(const ParticleCoreShell* sample);
    void setLabel(const ParticleDistribution* sample);

private:
    formfactors_t m_FormFactorLabel;
    interferences_t m_InterferenceFunctionLabel;
    layers_t m_LayerLabel;
    layouts_t m_ILayoutLabel;
    materials_t m_MaterialLabel;
    multilayers_t m_MultiLayerLabel;
    particlecompositions_t m_ParticleCompositionLabel;
    particledistributions_t m_ParticleDistributionLabel;
    particles_t m_ParticleLabel;
    particlescoreshell_t m_ParticleCoreShellLabel;
    rotations_t m_RotationsLabel;
    roughnesses_t m_LayerRoughnessLabel;
};

#endif // SAMPLELABELHANDLER_H

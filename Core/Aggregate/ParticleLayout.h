// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ParticleLayout.h
//! @brief     Defines class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUT_H
#define PARTICLELAYOUT_H

#include "ILayout.h"
#include "Vectors3D.h"
#include <memory>

class IAbstractParticle;
class IInterferenceFunction;
class IParticle;

//! Decorator class that adds particles to ISample objects.
//! @ingroup samples

class BA_CORE_API_ ParticleLayout : public ILayout
{
public:
    ParticleLayout();
    ParticleLayout(const IAbstractParticle& particle);
    ParticleLayout(const IAbstractParticle& particle, double abundance);
    ~ParticleLayout();

    ParticleLayout* clone() const final override;
    ParticleLayout* cloneWithOffset(double offset) const final override;

    void accept(INodeVisitor* visitor) const final override { visitor->visit(this); }

    void addParticle(const IAbstractParticle& particle);
    void addParticle(const IAbstractParticle& particle, double abundance); // TODO delete this
    void addParticle(const IParticle& particle, double abundance, const kvector_t position);
    void addParticle(const IParticle& particle, double abundance,
                     const kvector_t position, const IRotation& rotation);

    SafePointerVector<const IParticle> particles() const final override;

    double getTotalAbundance() const final override;

    void setInterferenceFunction(const IInterferenceFunction& interference_function);

    double totalParticleSurfaceDensity() const final override;
    void setTotalParticleSurfaceDensity(double particle_density) final override;

    std::vector<const INode*> getChildren() const final override;

private:
    void addAndRegisterAbstractParticle(IAbstractParticle* child);
    void setAndRegisterInterferenceFunction(IInterferenceFunction* child);

    void registerParticleDensity(bool make_registered = true);

    SafePointerVector<IAbstractParticle> m_particles; //!< Vector of particle types
    std::unique_ptr<IInterferenceFunction> mP_interference_function;
    double m_total_particle_density;
};

#endif // PARTICLELAYOUT_H

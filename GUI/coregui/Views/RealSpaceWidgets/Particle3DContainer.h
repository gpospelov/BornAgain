// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/TransformTo3D.cpp
//! @brief     Implements namespace TransformTo3D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef PARTICLE3DCONTAINER_H
#define PARTICLE3DCONTAINER_H

#include "WinDllMacros.h"
#include <QString>
#include <memory>
#include <vector>

namespace RealSpace{ namespace Particles { class Particle; } }

class BA_CORE_API_ Particle3DContainer
{
public:
    Particle3DContainer() {m_cumulativeAbundance = 0;}
    Particle3DContainer(const Particle3DContainer& other); // copy constructor
    Particle3DContainer& operator=(const Particle3DContainer& rhs); // copy assignment
    ~Particle3DContainer() noexcept;

    Particle3DContainer(Particle3DContainer &&other) noexcept; // move constructor
    Particle3DContainer& operator=(Particle3DContainer&& other) noexcept; // move assignment

    void clearContainer();

    size_t containerSize() const { return m_container.size(); }
    double cumulativeAbundance() const { return m_cumulativeAbundance; }
    const QString particleType() const { return m_particleType; }

    void addParticle(RealSpace::Particles::Particle* particle3D);
    void setCumulativeAbundance(double cumulativeAbundance);
    void setParticleType(QString particleType);

    std::unique_ptr<RealSpace::Particles::Particle> createParticle(const size_t &index) const;

private:
    std::vector<RealSpace::Particles::Particle*> m_container;
    // Contains the constituents of the 3D Particle (e.g. core and shell of a ParticleCoreShell)
    double m_cumulativeAbundance;
    QString m_particleType; // type of 3D Particle e.g. ParticleType, ParticleCompositionType etc.
};

#endif // PARTICLE3DCONTAINER_H

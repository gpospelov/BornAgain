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

#include "Particle3DContainer.h"
#include <ba3d/model/particles.h>

// copy constructor
Particle3DContainer::Particle3DContainer(const Particle3DContainer& other)
    : m_cumulativeAbundance(other.m_cumulativeAbundance), m_particleType(other.m_particleType)
{
    m_container.resize(other.m_container.size());
    for (size_t i = 0; i < m_container.size(); ++i)
        m_container[i] = new RealSpace::Particles::Particle(*other.m_container[i]);
}

// copy assignment
Particle3DContainer& Particle3DContainer::operator=(const Particle3DContainer& rhs)
{
    if (this != &rhs) {
        clearContainer();
        m_container.resize(rhs.containerSize());
        for (size_t i = 0; i < m_container.size(); ++i)
            m_container[i] = new RealSpace::Particles::Particle(*rhs.m_container[i]);

        m_cumulativeAbundance = rhs.m_cumulativeAbundance;
        m_particleType = rhs.m_particleType;
    }
    return *this;
}

// destructor
Particle3DContainer::~Particle3DContainer() noexcept
{
    clearContainer();
}

// move constructor
Particle3DContainer::Particle3DContainer(Particle3DContainer&& other) noexcept
    : m_container(std::move(other.m_container)),
      m_cumulativeAbundance(std::move(other.m_cumulativeAbundance)),
      m_particleType(std::move(other.m_particleType))
{
}

// move assignment
Particle3DContainer& Particle3DContainer::operator=(Particle3DContainer&& rhs) noexcept
{
    if (this != &rhs) {
        clearContainer();
        m_container = std::move(rhs.m_container);
        m_cumulativeAbundance = std::move(rhs.m_cumulativeAbundance);
        m_particleType = std::move(rhs.m_particleType);
    }
    return *this;
}

void Particle3DContainer::clearContainer()
{
    for (auto it = m_container.begin(); it != m_container.end(); ++it)
        delete (*it);

    m_container.clear();
}

void Particle3DContainer::addParticle(RealSpace::Particles::Particle* particle3D)
{
    m_container.emplace_back(particle3D);
}

void Particle3DContainer::setCumulativeAbundance(double cumulativeAbundance)
{
    m_cumulativeAbundance = cumulativeAbundance;
}

void Particle3DContainer::setParticleType(QString particleType)
{
    m_particleType = particleType;
}

std::unique_ptr<RealSpace::Particles::Particle>
Particle3DContainer::createParticle(const size_t& index) const
{
    auto particle = new RealSpace::Particles::Particle(*m_container.at(index));
    return std::unique_ptr<RealSpace::Particles::Particle>(particle);
}

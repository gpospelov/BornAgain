#include "PositionParticleInfo.h"

PositionParticleInfo::PositionParticleInfo(Particle* p_particle,
        Geometry::Transform3D* p_transform, kvector_t position,
        double abundance)
: ParticleInfo(p_particle, p_transform, position.z(), abundance)
, m_position(position)
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::PositionParticleInfo(Particle* p_particle,
        kvector_t position, double abundance)
: ParticleInfo(p_particle, 0, position.z(), abundance)
, m_position(position)
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::~PositionParticleInfo()
{
}

PositionParticleInfo* PositionParticleInfo::clone() const
{
    Geometry::Transform3D *p_transform(0);
    if(mp_transform) p_transform = new Geometry::Transform3D(*mp_transform);
    return new PositionParticleInfo(mp_particle->clone(), p_transform, m_position, m_abundance);
}

void PositionParticleInfo::setDepth(double depth)
{
    ParticleInfo::setDepth(depth);
    m_position.z() = -depth;
}

void PositionParticleInfo::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("x_position", &(m_position.x()));
    getParameterPool()->registerParameter("y_position", &(m_position.y()));
    getParameterPool()->registerParameter("z_position", &(m_position.z()));
}

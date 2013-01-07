#include "PositionParticleInfo.h"

PositionParticleInfo::PositionParticleInfo(Particle* p_particle,
        Geometry::Transform3D* p_transform, kvector_t position,
        double abundance)
: ParticleInfo(p_particle, p_transform, position.z(), abundance)
, m_pos_x(position.x())
, m_pos_y(position.y())
{
    setName("PositionParticleInfo");
    init_parameters();
}

PositionParticleInfo::PositionParticleInfo(Particle* p_particle,
        kvector_t position, double abundance)
: ParticleInfo(p_particle, 0, position.z(), abundance)
, m_pos_x(position.x())
, m_pos_y(position.y())
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
    kvector_t position(m_pos_x, m_pos_y, -m_depth);
    return new PositionParticleInfo(mp_particle->clone(), p_transform, position, m_abundance);
}

void PositionParticleInfo::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("x_position", &m_pos_x);
    getParameterPool()->registerParameter("y_position", &m_pos_y);
    getParameterPool()->registerParameter("z_position", &m_depth);
}

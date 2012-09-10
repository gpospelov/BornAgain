#include "DiffuseParticleInfo.h"

DiffuseParticleInfo::DiffuseParticleInfo(Particle* p_particle, Geometry::Transform3D *transform, double depth, double abundance)
: ParticleInfo(p_particle, transform, depth, abundance)
, m_number_per_meso(0.0)
{
}

DiffuseParticleInfo::~DiffuseParticleInfo()
{
}


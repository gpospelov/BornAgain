#include "DiffuseNanoParticleInfo.h"

DiffuseNanoParticleInfo::DiffuseNanoParticleInfo(Particle* p_particle, Geometry::Transform3D *transform, double depth, double abundance)
: NanoParticleInfo(p_particle, transform, depth, abundance)
, m_number_per_meso(0.0)
{
}

DiffuseNanoParticleInfo::~DiffuseNanoParticleInfo()
{
}


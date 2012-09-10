#include "ParticleInfo.h"



ParticleInfo::ParticleInfo(Particle* p_particle, Geometry::Transform3D *transform, double depth, double abundance)
: mp_particle(p_particle)
, m_transform(transform)
, m_depth(depth)
, m_abundance(abundance)
{
    setName("ParticleInfo");
    registerChild(mp_particle);
    init_parameters();
}


ParticleInfo::~ParticleInfo()
{
    delete mp_particle;
    delete m_transform;
}


// initialize pool parameters, i.e. register some of class members for later access via parameter pool
void ParticleInfo::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("depth", &m_depth);
}


/* ************************************************************************* */
// clone method
/* ************************************************************************* */
ParticleInfo *ParticleInfo::clone() const
{
    Geometry::Transform3D *transform(0);
    if(m_transform) transform = new Geometry::Transform3D(*m_transform);
    return new ParticleInfo(mp_particle->clone(), transform, m_depth, m_abundance);
}

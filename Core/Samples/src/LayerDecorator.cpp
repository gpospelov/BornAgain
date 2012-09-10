#include "LayerDecorator.h"

LayerDecorator::LayerDecorator(const Layer &layer)
: mp_decorated_layer(layer.clone())
, mp_decoration(0)
{
}

LayerDecorator::LayerDecorator(const Layer &layer,
        const ParticleDecoration &decoration)
: mp_decorated_layer(layer.clone())
, mp_decoration(decoration.clone())
{
    setName("LayerDecorator");
    registerChild(mp_decorated_layer);
    registerChild(mp_decoration);
    init_parameters();
}

LayerDecorator::LayerDecorator(const LayerDecorator& other)
: Layer(other)
{
    mp_decorated_layer = other.getDecoratedLayer()->clone();
    mp_decoration = other.getDecoration()->clone();

    setName("LayerDecorator");
    registerChild(mp_decorated_layer);
    registerChild(mp_decoration);
    init_parameters();
}

LayerDecorator* LayerDecorator::clone() const
{
    return new LayerDecorator(*this);
}

LayerDecorator::~LayerDecorator()
{
    delete mp_decorated_layer;
    delete mp_decoration;
}

// LayerDecorator is derived from Layer and it has to clean all parameters created by Layer
void LayerDecorator::init_parameters()
{
    getParameterPool()->clear();
}

DiffuseDWBASimulation* LayerDecorator::createDiffuseDWBASimulation() const
{
    DiffuseDWBASimulation *p_sim = new DiffuseDWBASimulation;
    size_t nbr_particles = mp_decoration->getNumberOfParticles();
    double meso_density = mp_decoration->getTotalParticleSurfaceDensity();
    double nps_per_meso = 0.0;
    double total_abundance = 0.0;
    for (size_t i=0; i<nbr_particles; ++i) {
        const ParticleInfo *p_info = mp_decoration->getParticleInfo(i);
        std::vector<DiffuseParticleInfo *> *p_diffuse_nps =
                p_info->getParticle()->createDiffuseParticleInfo(*p_info);
        if (p_diffuse_nps) {
            for (size_t j=0; j<p_diffuse_nps->size(); ++j) {
                p_sim->addParticleInfo((*p_diffuse_nps)[j]);
                nps_per_meso += (*p_diffuse_nps)[j]->getNumberPerMeso();
            }
            total_abundance += p_info->getAbundance();
            delete p_diffuse_nps;
            break; // TODO: remove this (temporarely to increase speed)
        }
    }
    if (p_sim->getSize()>0) {
        p_sim->setRefractiveIndex(getRefractiveIndex());
        p_sim->setSurfaceDensity(meso_density*nps_per_meso);
        p_sim->rescaleAbundances(1.0/total_abundance);
        return p_sim;
    }
    delete p_sim;
    return 0;
}

/* ************************************************************************* */
// print content of multilayer
/* ************************************************************************* */
void LayerDecorator::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
}

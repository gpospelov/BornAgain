#include "LayerDecorator.h"

LayerDecorator::LayerDecorator(const Layer &layer)
: mp_decorated_layer(layer.clone())
{
}

LayerDecorator::LayerDecorator(const Layer &layer,
        const NanoParticleDecoration &decoration)
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

/* ************************************************************************* */
// print content of multilayer
/* ************************************************************************* */
void LayerDecorator::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
}

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
}

LayerDecorator::LayerDecorator(const LayerDecorator& other)
: Layer(other)
{
    mp_decorated_layer = other.getDecoratedLayer()->clone();
    mp_decoration = other.getDecoration()->clone();
}

LayerDecorator& LayerDecorator::operator =(const LayerDecorator& other)
{
    if (this!=&other) {
        clear();
        mp_decorated_layer = other.getDecoratedLayer()->clone();
        mp_decoration = other.getDecoration()->clone();
    }
    return *this;
}

LayerDecorator* LayerDecorator::clone() const
{
    return new LayerDecorator(*this);
}

LayerDecorator::~LayerDecorator()
{
    clear();
}

void LayerDecorator::init_parameters()
{
}

void LayerDecorator::clear()
{
    delete mp_decorated_layer;
    delete mp_decoration;
}




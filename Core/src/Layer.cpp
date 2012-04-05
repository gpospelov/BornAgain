#include "Layer.h"
#include <stdexcept>

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::setThickness(double thickness)
{
    if (thickness>=0.0)
    {
        m_thickness = thickness;
        return;
    }
    throw new std::domain_error("Layer thickness cannot be negative");
}

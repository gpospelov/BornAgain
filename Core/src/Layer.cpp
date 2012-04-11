#include "Layer.h"
#include <stdexcept>

Layer::Layer() : mp_bulk_material(0), m_thickness(0)
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


void Layer::setMaterial(IMaterial* p_material, double thickness)
{
    setMaterial(p_material);
    setThickness(thickness);
}

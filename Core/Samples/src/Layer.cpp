#include "Layer.h"
#include "Exceptions.h"


/* ************************************************************************* */
// constructors, assignment operator, destructors
/* ************************************************************************* */
Layer::Layer() : mp_material(0), m_thickness(0)
{
    setName("layer");
}


Layer::Layer(const Layer &other) : ISample(other)
{
    mp_material = other.mp_material;
    m_thickness = other.m_thickness;
}


Layer &Layer::operator=(const Layer &other)
{
    if( this != &other)
    {
        ISample::operator=(other);
        mp_material = other.mp_material;
        m_thickness = other.m_thickness;
    }
    return *this;
}


Layer::~Layer()
{

}


/* ************************************************************************* */
// clone
/* ************************************************************************* */
Layer *Layer::clone() const
{
    return new Layer(*this);
}


/* ************************************************************************* */
void Layer::setThickness(double thickness)
{
    if (thickness>=0.0)
    {
        m_thickness = thickness;
        return;
    }
    throw DomainErrorException("Layer thickness cannot be negative");
}


void Layer::setMaterial(const IMaterial* p_material, double thickness)
{
    setMaterial(p_material);
    setThickness(thickness);
}


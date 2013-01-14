#include "Layer.h"
#include "Exceptions.h"
#include <iomanip>

/* ************************************************************************* */
// constructors, assignment operator, destructors
/* ************************************************************************* */
Layer::Layer() : mp_material(0), m_thickness(0)
{
    setName("Layer");
    init_parameters();
}

Layer::Layer(const IMaterial* p_material, double thickness) : mp_material(0), m_thickness(0)
{
    setName("Layer");
    setMaterial(p_material);
    setThickness(thickness);
    init_parameters();
}


Layer::Layer(const Layer &other) : ICompositeSample()
{
    mp_material = other.mp_material;
    m_thickness = other.m_thickness;
    init_parameters();
}


//Layer &Layer::operator=(const Layer &other)
//{
//    if( this != &other)
//    {
//        ISample::operator=(other);
//        mp_material = other.mp_material;
//        m_thickness = other.m_thickness;
//        init_parameters();
//    }
//    return *this;
//}



/* ************************************************************************* */
// initialize pool parameters, i.e. register some of class members for later
// access via parameter pool
/* ************************************************************************* */
void Layer::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("thickness", &m_thickness);
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


/* ************************************************************************* */
// print content of multilayer
/* ************************************************************************* */
void Layer::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
    ostr << *getMaterial();
//    ostr << getName()
//         << " " << std::setw(12) << this
//         << " " << getThickness() << "nm > "
//         << *getMaterial();
}


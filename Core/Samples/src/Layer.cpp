// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Layer.cpp
//! @brief     Implements class Layer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

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


//! Registers some class members for later access via parameter pool

void Layer::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("thickness", &m_thickness);
}

Layer *Layer::clone() const
{
    return new Layer(*this);
}

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

//! Prints content of multilayer

void Layer::print(std::ostream &ostr) const
{
    ICompositeSample::print(ostr);
    ostr << *getMaterial();
}

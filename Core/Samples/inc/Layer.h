// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Layer.h
//! @brief     Defines class Layer.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef LAYER_H
#define LAYER_H

#include "ICompositeSample.h"
#include "IMaterial.h"
#include "HomogeneousMaterial.h"
#include "LayerDWBASimulation.h"

//! A Layer with thickness and pointer to the material

class Layer : public ICompositeSample
{
 public:
    //! Constructs empty layer.
    Layer() : mp_material(0), m_thickness(0)
    {
        setName("Layer");
        init_parameters();
    }

    //! Constructs layer made of _material_ with _thickness_ in Angstrom.
    Layer(const IMaterial* material, double thickness=0)
        : m_thickness(thickness)
    {
        setName("Layer");
        setMaterial(material);
        init_parameters();
    }

    virtual ~Layer() {}

    virtual Layer *clone() const { return new Layer(*this); }

    //! Sets layer thickness in Angstrom.
    virtual void setThickness(double thickness);

    //! Returns layer thickness in Angstrom.
    virtual double getThickness() const { return m_thickness; }

    //! Sets _material_ of the layer.
    virtual void setMaterial(const IMaterial* material);

    //! Sets _material_ and _thickness_.
    virtual void setMaterial(const IMaterial* material, double thickness)
    { setMaterial(material); setThickness(thickness); }

    //! Returns layer's material.
    virtual const IMaterial* getMaterial() const { return mp_material; }

    //! Returns refractive index of the layer's material.
    virtual complex_t getRefractiveIndex() const
    {
        return (dynamic_cast<const HomogeneousMaterial *>
                (mp_material))->getRefractiveIndex();
    }

    //! Returns false (override is important for polymorphism of LayerDecorator).
    virtual bool hasDWBASimulation() const { return false; }

    //! Returns zero pointer (override is important for polymorphism of LayerDecorator).
    virtual LayerDWBASimulation *createDWBASimulation() const { return 0; }

 protected:
    Layer(const Layer& other)
    {
        mp_material = other.mp_material;
        m_thickness = other.m_thickness;
        init_parameters();
    }

    virtual void init_parameters()
    {
        getParameterPool()->clear();
        getParameterPool()->registerParameter("thickness", &m_thickness);
    }

    void print(std::ostream& ostr) const;

    const IMaterial* mp_material;    //!< pointer to the material
    double m_thickness;              //!< layer thickness in nanometers
};

#endif // LAYER_H

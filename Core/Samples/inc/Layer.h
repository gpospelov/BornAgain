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
    Layer();
    Layer(const IMaterial* p_material, double thickness=0);
    virtual ~Layer() { }

    //! make layer's clone
    virtual Layer *clone() const;

    //! set layer thickness in _angstrom_
    virtual void setThickness(double thickness);

    //! return layer thickness in _angstrom_
    virtual double getThickness() const { return m_thickness; }

    //! set material of the layer
    virtual void setMaterial(const IMaterial* p_material)
    { 
        p_material ?
            mp_material = p_material :
            throw NullPointerException("The material doesn't exist");
    }

    //! @brief set material of given thickness to the layer
    //! @param p_material   pointer to the material of layer
    //! @param thickness    thickness of the material in angstrom
    virtual void setMaterial(const IMaterial* p_material, double thickness);

    //! return layer's material
    virtual const IMaterial* getMaterial() const { return mp_material; }

    //! return refractive index of the layer's material
    virtual complex_t getRefractiveIndex() const
    {
        return (dynamic_cast<const HomogeneousMaterial *>(mp_material))->
            getRefractiveIndex();
    }

    //! return false (override is important for polymorphism of LayerDecorator)
    virtual bool hasDWBASimulation() const { return false; }

    //! return zero pointer (override is important for polymorphism of LayerDecorator)
    virtual LayerDWBASimulation *createDWBASimulation() const { return 0; }

 protected:
    Layer(const Layer &other);

    //! register some class members for later access via parameter pool
    virtual void init_parameters();

 private:
    //! print class
    void print(std::ostream &ostr) const;

    const IMaterial* mp_material;    //!< pointer to the material
    double m_thickness;              //!< layer thickness in nanometers
};

#endif // LAYER_H

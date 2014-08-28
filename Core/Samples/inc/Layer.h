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

#include "Materials.h"
#include "DiffuseDWBASimulation.h"
#include "ICompositeSample.h"
#include "LayerDWBASimulation.h"
#include "ParticleLayout.h"

//! @class Layer
//! @ingroup samples
//! @brief A layer with thickness and material

class BA_CORE_API_ Layer : public ICompositeSample
{
public:
    //! Constructs empty layer.
    Layer();

    //! Constructs layer made of _material_ with _thickness_ in nanometers and decoration
//    Layer(const IMaterial* material, double thickness=0, ILayout *decoration=0);
    Layer(const IMaterial &material, double thickness = 0);

    virtual ~Layer();

    virtual Layer *clone() const { return new Layer(*this); }

    //! Returns a clone with inverted magnetic fields
    virtual Layer *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets layer thickness in nanometers.
    virtual void setThickness(double thickness);

    //! Returns layer thickness in nanometers.
    virtual double getThickness() const { return m_thickness; }

    //! Sets _material_ of the layer.
    virtual void setMaterial(const IMaterial &material);

    //! Sets _material_ and _thickness_.
    virtual void setMaterialAndThickness(const IMaterial &material,
                                         double thickness);

    //! Returns layer's material.
    virtual const IMaterial* getMaterial() const { return mp_material; }

    //! Returns refractive index of the layer's material.
    virtual complex_t getRefractiveIndex() const;

    //! sets particle layout
    virtual void setLayout(const ILayout &decoration);

    //! returns particle decoration
    virtual const ILayout* getLayout() const { return mp_layout; }

    //! Returns true if decoration is present
    virtual bool hasDWBASimulation() const {
        return (mp_layout ? true : false);
    }

    //! creates and return LayerDWBASimulation in the case of present decoration
    virtual LayerDWBASimulation *createDWBASimulation() const;

    virtual DiffuseDWBASimulation *createDiffuseDWBASimulation() const;

    virtual double getTotalParticleSurfaceDensity() const;

    void setParentMultiLayer(const MultiLayer *parent) {
        mp_parent_multilayer = parent;
    }

    size_t getNumberOfLayers() const;

protected:
    Layer(const Layer& other);

    void init_parameters();

    void print(std::ostream& ostr) const;

    //! sets particle layout (separate pointer version due to python-bindings)
    virtual void setLayoutPtr(ILayout *layout);

    double m_thickness;       //!< layer thickness in nanometers
    IMaterial* mp_material;   //!< pointer to the material
    ILayout *mp_layout;       //!< particle layout
    const MultiLayer *mp_parent_multilayer;
};


inline complex_t Layer::getRefractiveIndex() const
{
    return (mp_material ? mp_material->getRefractiveIndex()
                        : complex_t(1.0,0.0));
}

inline double Layer::getTotalParticleSurfaceDensity() const
{
    if (mp_layout) {
        return mp_layout->getTotalParticleSurfaceDensity();
    }
    return 0.0;
}


#endif // LAYER_H



// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/LayerDecorator.h
//! @brief     Defines class LayerDecorator.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERDECORATOR_H_
#define LAYERDECORATOR_H_

#include "Layer.h"
#include "ParticleDecoration.h"
#include "LayerDecoratorDWBASimulation.h"

//! Combines a Layer with an IDecoration.

class LayerDecorator : public Layer
{
 public:
    //! Constructs LayerDecorator object by cloning _layer_ and _decoration_.
    LayerDecorator(const Layer& layer, const IDecoration& decoration)
        : mp_decorated_layer(layer.clone()), mp_decoration(decoration.clone())
    {
        setName("LayerDecorator");
        registerChild(mp_decorated_layer);
        registerChild(mp_decoration);
        init_parameters();
    }

    virtual ~LayerDecorator()
    {
        delete mp_decorated_layer;
        delete mp_decoration;
    }

    virtual LayerDecorator *clone() const
    { return new LayerDecorator(*this); }

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) { p_visitor->visit(this); }

    //! Sets _thickness_ in nanometers.
    virtual void setThickness(double thickness)
    { mp_decorated_layer->setThickness(thickness); }

    //! Returns thickness in nanometers.
    virtual double getThickness() const
    { return mp_decorated_layer->getThickness(); }

    //! Sets _material_.
    virtual void setMaterial(const IMaterial* material)
    { mp_decorated_layer->setMaterial(material); }

    //! Sets _material_ and _thickness_ in nanometers.
    virtual void setMaterial(const IMaterial* material, double thickness)
    { mp_decorated_layer->setMaterial(material, thickness); }

    //! Returns material
    const virtual IMaterial* getMaterial() const
    { return mp_decorated_layer->getMaterial(); }

    //! Returns refractive index.
    virtual complex_t getRefractiveIndex() const
    { return mp_decorated_layer->getRefractiveIndex(); }

    virtual void init_parameters()
    { getParameterPool()->clear(); }

    const Layer* getDecoratedLayer() const { return mp_decorated_layer; }

    const IDecoration* getDecoration() const { return mp_decoration; }

    virtual bool hasDWBASimulation() const { return true; }

    virtual LayerDecoratorDWBASimulation *createDWBASimulation() const
    { return new LayerDecoratorDWBASimulation(this); }

    virtual DiffuseDWBASimulation *createDiffuseDWBASimulation() const;

    virtual double getTotalParticleSurfaceDensity() const {
        if (mp_decoration) {
            return mp_decoration->getTotalParticleSurfaceDensity();
        }
        return 0.;
    }

 protected:
    //! Constructs a new object by cloning _other_'s layer and decoration.
    LayerDecorator(const LayerDecorator& other)
        : Layer(other)
    {
        mp_decorated_layer = other.getDecoratedLayer()->clone();
        mp_decoration = other.getDecoration()->clone();
        setName("LayerDecorator");
        registerChild(mp_decorated_layer);
        registerChild(mp_decoration);
        init_parameters();
    }

    Layer *mp_decorated_layer;
    IDecoration *mp_decoration;

 private:
    void print(std::ostream& ostr) const;
};

#endif /* LAYERDECORATOR_H_ */



#ifndef LAYERDECORATOR_H_
#define LAYERDECORATOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LayerDecorator.h
//! @brief  Definition of LayerDecorator class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 22, 2012

#include "Layer.h"
#include "ParticleDecoration.h"
#include "LayerDecoratorDWBASimulation.h"

class LayerDecorator : public Layer
{
public:
    LayerDecorator(const Layer &layer, const IDecoration &decoration);
    virtual ~LayerDecorator();

    /// make layer's clone
    virtual LayerDecorator *clone() const;

    //! set layer thickness in _angstrom_
    virtual void setThickness(double thickness) { mp_decorated_layer->setThickness(thickness); }

    //! return layer thickness in _angstrom_
    virtual double getThickness() const { return mp_decorated_layer->getThickness(); }

    //! @brief set material to the layer
    //! @param p_material   pointer to the material
    virtual void setMaterial(const IMaterial* p_material) { mp_decorated_layer->setMaterial(p_material); }

    //! @brief set material of given thickness to the layer
    //! @param p_material   pointer to the material of layer
    //! @param thickness    thickness of the material in angstrom
    virtual void setMaterial(const IMaterial* p_material, double thickness) {
        mp_decorated_layer->setMaterial(p_material, thickness);
    }

    //! return layer's material
    const virtual IMaterial* getMaterial() const
    {
        return mp_decorated_layer->getMaterial();
    }

    //! return refractive index of the layer's material
    virtual complex_t getRefractiveIndex() const
    {
        return mp_decorated_layer->getRefractiveIndex();
    }

    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

    const Layer* getDecoratedLayer() const { return mp_decorated_layer; }
    const IDecoration* getDecoration() const { return mp_decoration; }

    virtual bool hasDWBASimulation() const { return true; }

    virtual LayerDecoratorDWBASimulation *createDWBASimulation() const {
        return new LayerDecoratorDWBASimulation(this);
    }

    virtual DiffuseDWBASimulation *createDiffuseDWBASimulation() const;

    virtual double getTotalParticleSurfaceDensity() const {
        if (mp_decoration) {
            return mp_decoration->getTotalParticleSurfaceDensity();
        }
        return 0.0;
    }

    virtual IInterferenceFunctionStrategy *createStrategy(const std::vector<IFormFactor *> &form_factors) const {
        if (mp_decoration) {
            return mp_decoration->createStrategy(form_factors);
        }
        throw NullPointerException("No decoration present in LaeyerDecorator.");
    }

protected:
    LayerDecorator(const LayerDecorator &layer);

    Layer *mp_decorated_layer;
    IDecoration *mp_decoration;

private:
    //! print class
    void print(std::ostream &ostr) const;

};

#endif /* LAYERDECORATOR_H_ */

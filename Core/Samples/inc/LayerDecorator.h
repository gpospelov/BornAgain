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

#include "WinDllMacros.h"
#include "Layer.h"
#include "ParticleDecoration.h"
#include "LayerDecoratorDWBASimulation.h"

//! Combines a Layer with an IDecoration.

class BA_CORE_API_ LayerDecorator : public Layer
{
 public:
    //! Constructs LayerDecorator object by cloning _layer_ and _decoration_.
    LayerDecorator(const Layer& layer, const IDecoration& decoration);
    virtual ~LayerDecorator();

    virtual LayerDecorator *clone() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets _thickness_ in nanometers.
    virtual void setThickness(double thickness);

    //! Returns thickness in nanometers.
    virtual double getThickness() const;

    //! Sets _material_.
    virtual void setMaterial(const IMaterial* material);

    //! Sets _material_ and _thickness_ in nanometers.
    virtual void setMaterial(const IMaterial* material, double thickness);

    //! Returns material
    const virtual IMaterial* getMaterial() const;

    //! Returns refractive index.
    virtual complex_t getRefractiveIndex() const;

    virtual void init_parameters();

    const Layer* getDecoratedLayer() const { return mp_decorated_layer; }

    const IDecoration* getDecoration() const { return mp_decoration; }

    virtual bool hasDWBASimulation() const { return true; }

    virtual LayerDecoratorDWBASimulation *createDWBASimulation() const
    { return new LayerDecoratorDWBASimulation(this); }

    virtual DiffuseDWBASimulation *createDiffuseDWBASimulation() const;

    virtual double getTotalParticleSurfaceDensity() const;

 protected:
    //! Constructs a new object by cloning _other_'s layer and decoration.
    LayerDecorator(const LayerDecorator& other);

    Layer *mp_decorated_layer;
    IDecoration *mp_decoration;

 private:
    void print(std::ostream& ostr) const;
};


inline LayerDecorator *LayerDecorator::clone() const
{
    return new LayerDecorator(*this);
}

inline void LayerDecorator::setThickness(double thickness)
{
    mp_decorated_layer->setThickness(thickness);
}

inline double LayerDecorator::getThickness() const
{
    return mp_decorated_layer->getThickness();
}

inline void LayerDecorator::setMaterial(const IMaterial* material)
{
    mp_decorated_layer->setMaterial(material);
}

inline void LayerDecorator::setMaterial(const IMaterial* material, double thickness)
{
    mp_decorated_layer->setMaterial(material, thickness);
}

inline const IMaterial* LayerDecorator::getMaterial() const
{
    return mp_decorated_layer->getMaterial();
}

inline complex_t LayerDecorator::getRefractiveIndex() const
{
    return mp_decorated_layer->getRefractiveIndex();
}

inline double LayerDecorator::getTotalParticleSurfaceDensity() const
{
    if (mp_decoration) {
        return mp_decoration->getTotalParticleSurfaceDensity();
    }
    return 0.;
}


#endif /* LAYERDECORATOR_H_ */



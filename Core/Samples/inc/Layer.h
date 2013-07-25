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

#include "WinDllMacros.h"
#include "ICompositeSample.h"
#include "IMaterial.h"
#include "HomogeneousMaterial.h"
#include "LayerDWBASimulation.h"
#include "ParticleDecoration.h"
#include "LayerDecoratorDWBASimulation.h"

//! A Layer with thickness and pointer to the material

class BA_CORE_API_ Layer : public ICompositeSample
{
 public:
    //! Constructs empty layer.
    Layer();

    //! Constructs layer made of _material_ with _thickness_ in nanometers.
    Layer(const IMaterial* material, double thickness=0);

    virtual ~Layer();

    virtual Layer *clone() const { return new Layer(*this); }

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *p_visitor) const { p_visitor->visit(this); }

    //! Sets layer thickness in nanometers.
    virtual void setThickness(double thickness);

    //! Returns layer thickness in nanometers.
    virtual double getThickness() const { return m_thickness; }

    //! Sets _material_ of the layer.
    virtual void setMaterial(const IMaterial* material);

    //! Sets _material_ and _thickness_.
    virtual void setMaterial(const IMaterial* material, double thickness);

    //! Returns layer's material.
    virtual const IMaterial* getMaterial() const { return mp_material; }

    //! Returns refractive index of the layer's material.
    virtual complex_t getRefractiveIndex() const;

    //! sets particle decoration
    void setDecoration(IDecoration *decoration) { delete mp_decoration; mp_decoration = decoration; }
    void setDecoration(const IDecoration &decoration) { delete mp_decoration; mp_decoration = decoration.clone(); }

    //! returns particle decoration
    const IDecoration* getDecoration() const { return mp_decoration; }

    //! Returns true if decoration is present
    virtual bool hasDWBASimulation() const { return (mp_decoration ? true : false); }

    //! creates and return LayerDWBASimulation in the case of present decoration
    virtual LayerDWBASimulation *createDWBASimulation() const;

    virtual DiffuseDWBASimulation *createDiffuseDWBASimulation() const;

    virtual double getTotalParticleSurfaceDensity() const;

 protected:
    Layer(const Layer& other);

    void init_parameters();

    void print(std::ostream& ostr) const;

    const IMaterial* mp_material;    //!< pointer to the material
    IDecoration *mp_decoration;      //!< particle decoration
    double m_thickness;              //!< layer thickness in nanometers
};


inline complex_t Layer::getRefractiveIndex() const
{
    const HomogeneousMaterial *material = dynamic_cast<const HomogeneousMaterial *>(mp_material);
    return (material ? material->getRefractiveIndex() : complex_t(0,0));
}

inline double Layer::getTotalParticleSurfaceDensity() const
{
    if (mp_decoration) {
        return mp_decoration->getTotalParticleSurfaceDensity();
    }
    return 0.0;
}


#endif // LAYER_H



// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Layer.h
//! @brief     Defines class Layer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYER_H
#define LAYER_H

#include "Materials.h"
#include "ICompositeSample.h"
#include "LayerDWBASimulation.h"
#include "ParticleLayout.h"
#include "SafePointerVector.h"

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
    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Sets layer thickness in nanometers.
    virtual void setThickness(double thickness);

    //! Returns layer thickness in nanometers.
    virtual double getThickness() const { return m_thickness; }

    //! Sets _material_ of the layer.
    virtual void setMaterial(const IMaterial& material);

    //! Sets _material_ and _thickness_.
    virtual void setMaterialAndThickness(const IMaterial& material,
                                         double thickness);

    //! Returns layer's material.
    virtual const IMaterial* getMaterial() const { return mp_material; }

    //! Returns refractive index of the layer's material.
    virtual complex_t getRefractiveIndex() const;

    //! sets particle layout
    virtual void addLayout(const ILayout& decoration);

    //! gets number of layouts present
    size_t getNumberOfLayouts() const {
        return m_layouts.size();
    }

    //! returns particle decoration
    virtual const ILayout* getLayout(size_t i) const {
        if (i>=m_layouts.size()) {
            return 0;
        }
        return m_layouts[i];
    }

    //! Returns true if decoration is present
    virtual bool hasDWBASimulation() const {
        return (m_layouts.size()>0);
    }

    //! creates and returns a LayerDWBASimulation for the given layout
    LayerDWBASimulation *createLayoutSimulation(size_t layout_index) const;

    double getTotalParticleSurfaceDensity(size_t layout_index) const;

    double getTotalAbundance() const;

    void setNumberOfLayers(size_t n_layers) {
        mn_layers = n_layers;
    }

    size_t getNumberOfLayers() const {
        return mn_layers;
    }

protected:
    Layer(const Layer& other);

    void init_parameters();

    void print(std::ostream& ostr) const;

    //! adds particle layout (separate pointer version due to python-bindings)
    virtual void addLayoutPtr(ILayout* layout);

    double m_thickness;       //!< layer thickness in nanometers
    IMaterial* mp_material;   //!< pointer to the material
    SafePointerVector<ILayout> m_layouts; //!< independent layouts in this layer
    size_t mn_layers;
};


inline complex_t Layer::getRefractiveIndex() const
{
    return (mp_material ? mp_material->getRefractiveIndex()
                        : complex_t(1.0,0.0));
}

inline double Layer::getTotalParticleSurfaceDensity(size_t layout_index) const
{
    if (getNumberOfLayouts()==0 || layout_index>=getNumberOfLayouts()) {
        return 0.0;
    }
    return getLayout(layout_index)->getTotalParticleSurfaceDensity();
}


#endif // LAYER_H



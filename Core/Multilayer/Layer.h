// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/Layer.h
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

#include "ISample.h"
#include "Complex.h"
#include "SafePointerVector.h"

class ILayout;
class IMaterial;

//! A layer, with thickness (in nanometer) and material.
//! @ingroup samples

class BA_CORE_API_ Layer : public ISample
{
public:
    Layer(const IMaterial& material, double thickness = 0);

    ~Layer() final;

    Layer* clone() const final { return new Layer(*this); }
    Layer* cloneInvertB() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setThickness(double thickness);
    double getThickness() const { return m_thickness; }

    void setMaterial(const IMaterial& material);
    const IMaterial* getMaterial() const { return mp_material; }

    complex_t getRefractiveIndex() const;
    complex_t getRefractiveIndex2() const; //!< squared refractive index

    void addLayout(const ILayout& decoration);
    size_t getNumberOfLayouts() const { return m_layouts.size(); }
    const ILayout* getLayout(size_t i) const;

    //! Returns true if decoration is present
    bool hasComputation() const { return m_layouts.size()>0; }

    std::vector<const INode*> getChildren() const;

private:
    Layer(const Layer& other);

    void init_parameters();

    IMaterial* mp_material;   //!< pointer to the material
    double m_thickness;       //!< layer thickness in nanometers
    SafePointerVector<ILayout> m_layouts; //!< independent layouts in this layer

    void initialize();
};

#endif // LAYER_H

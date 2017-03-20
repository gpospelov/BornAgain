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
#include "HomogeneousMaterial.h"
#include "SafePointerVector.h"

class ILayout;

//! A layer, with thickness (in nanometer) and material.
//! @ingroup samples

class BA_CORE_API_ Layer : public ISample
{
public:
    Layer(HomogeneousMaterial material, double thickness = 0);

    ~Layer();

    Layer* clone() const override final { return new Layer(*this); }
    Layer* cloneInvertB() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setThickness(double thickness);
    double thickness() const { return m_thickness; }

    const HomogeneousMaterial* material() const override final { return &m_material; }

    void setMaterial(HomogeneousMaterial material);

    complex_t refractiveIndex() const;
    complex_t refractiveIndex2() const; //!< squared refractive index

    void addLayout(const ILayout& decoration);
    size_t numberOfLayouts() const { return m_layouts.size(); }
    const ILayout* layout(size_t i) const;

    //! Returns true if decoration is present
    bool hasComputation() const { return m_layouts.size()>0; }

    std::vector<const INode*> getChildren() const override final;

    void registerThickness(bool make_registered = true);

private:
    Layer(const Layer& other);

    HomogeneousMaterial m_material;   //!< material
    double m_thickness;       //!< layer thickness in nanometers
    SafePointerVector<ILayout> m_layouts; //!< independent layouts in this layer
};

#endif // LAYER_H

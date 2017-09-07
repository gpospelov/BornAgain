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
#include "ZLimits.h"

class ILayout;

//! A layer, with thickness (in nanometer) and material.
//! @ingroup samples

class BA_CORE_API_ Layer : public ISample
{
public:
    enum ELayerType {
        TOPLAYER,
        INTERMEDIATELAYER,
        BOTTOMLAYER,
        ONLYLAYER
    };
    Layer(HomogeneousMaterial material, double thickness = 0);

    ~Layer();

    Layer* clone() const override final;
    Layer* cloneInvertB() const;
    SafePointerVector<Layer> cloneSliced(ZLimits limits, ELayerType layer_type) const;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void setThickness(double thickness);
    double thickness() const { return m_thickness; }

    const HomogeneousMaterial* material() const override final { return &m_material; }
    void setMaterial(HomogeneousMaterial material);

    complex_t refractiveIndex() const;
    complex_t refractiveIndex2() const; //!< squared refractive index

    void addLayout(const ILayout& decoration);
    size_t numberOfLayouts() const { return m_layouts.size(); }
    std::vector<const ILayout*> layouts() const;

    std::vector<const INode*> getChildren() const override final;

    void registerThickness(bool make_registered = true);

    void setNumberOfSlices(unsigned int n_slices) { m_n_slices = n_slices; }
    unsigned int numberOfSlices() const { return m_n_slices; }

    //! Return the potential term that is used in the one-dimensional Fresnel calculations
    complex_t scalarReducedPotential(kvector_t k, double n_ref) const;

#ifndef SWIG
    //! Return the potential term that is used in the one-dimensional Fresnel calculations
    //! in the presence of magnetization
    Eigen::Matrix2cd polarizedReducedPotential(kvector_t k, double n_ref) const;
#endif

    //! Initializes the magnetic B field from a given ambient field strength H
    void initBField(kvector_t h_field, double b_z);

    static constexpr double Magnetic_Permeability = 4e-7 * M_PI;

private:
    Layer(const Layer& other);
    //! Clone the layer without its layouts
    Layer* shallowClone() const;
    //! Clone and offsets the particles in the z-direction
    Layer* cloneWithOffset(double offset) const;

    //! Return the magnetic B-field in this layer
    kvector_t bField() const;

    HomogeneousMaterial m_material;       //!< material
    kvector_t m_B_field;                  //!< cached value of magnetic induction
    double m_thickness;                   //!< layer thickness in nanometers
    SafePointerVector<ILayout> m_layouts; //!< independent layouts in this layer
    unsigned int m_n_slices=1;            //!< number of slices to create for graded layer approach
};

#endif // LAYER_H

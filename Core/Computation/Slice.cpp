// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/Slice.cpp
//! @brief     Implements class Slice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Slice.h"
#include "LayerRoughness.h"

Slice::Slice(double thickness) : m_thickness{thickness}, mP_top_roughness{nullptr} {}

Slice::Slice(double thickness, const LayerRoughness& top_roughness)
    : m_thickness{thickness}, mP_top_roughness{top_roughness.clone()}
{
}

Slice::Slice(const Slice& other) : m_thickness{other.m_thickness}, mP_material{}, mP_top_roughness{}
{
    if (other.mP_material) {
        mP_material.reset(new Material(*other.mP_material));
    }
    if (other.mP_top_roughness) {
        mP_top_roughness.reset(other.mP_top_roughness->clone());
    }
}

Slice::Slice(Slice&& other)
    : m_thickness{other.m_thickness}, mP_material{std::move(other.mP_material)},
      mP_top_roughness{std::move(other.mP_top_roughness)}
{
}

Slice::~Slice() = default;

void Slice::setMaterial(const Material& material)
{
    mP_material.reset(new Material(material));
}

Material Slice::material() const
{
    return *mP_material;
}

double Slice::thickness() const
{
    return m_thickness;
}

const LayerRoughness* Slice::topRoughness() const
{
    return mP_top_roughness.get();
}

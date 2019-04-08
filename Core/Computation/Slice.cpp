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


Slice::Slice(double thickness, Material material)
    : m_thickness{thickness}, m_material{std::move(material)}, mP_top_roughness{nullptr}
{}

Slice::Slice(double thickness, Material material, const LayerRoughness &top_roughness)
    : m_thickness{thickness}, m_material{std::move(material)}
    , mP_top_roughness{top_roughness.clone()}
{}

Slice::~Slice() =default;

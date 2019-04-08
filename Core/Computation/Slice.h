// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/Slice.h
//! @brief     Defines class Slice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SLICE_H
#define SLICE_H

#include "Material.h"
#include <memory>

class LayerRoughness;

//! Data structure containing the data of a single slice, for calculating the Fresnel coefficients.
//!
//! @ingroup algorithms_internal

class Slice
{
public:
    Slice(double thickness, Material material);
    Slice(double thickness, Material material, const LayerRoughness& top_roughness);
    ~Slice();

private:
    double m_thickness;
    Material m_material;
    std::unique_ptr<LayerRoughness> mP_top_roughness;
};

#endif // SLICE_H

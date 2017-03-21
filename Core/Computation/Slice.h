// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/Slice.h
//! @brief     Defines class Slice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SLICE_H
#define SLICE_H

#include <memory>

class HomogeneousMaterial;
class LayerRoughness;

//! Represents a single slice, constructed from the division of a layer into (possibly) multiple
//! slices.
//!
//! @ingroup algorithms_internal

class Slice
{
public:
    Slice(const HomogeneousMaterial& material, double thickness, const LayerRoughness* top_roughness=nullptr);
    ~Slice();

private:
    std::unique_ptr<HomogeneousMaterial> mP_material;
    double m_thickness;
    std::unique_ptr<LayerRoughness> mP_top_roughness;
};

#endif // SLICE_H

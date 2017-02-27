// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/SlicedFormFactorList.cpp
//! @brief     Defines class SlicedFormFactorList.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //


#include "SlicedFormFactorList.h"
#include "MultiLayer.h"
#include "Rotations.h"

namespace {
size_t LayerIndexBottom(const IFormFactor& ff, const MultiLayer& multilayer,
                        double position_offset);
size_t LayerIndexTop(const IFormFactor& ff, const MultiLayer& multilayer,
                        double position_offset);
}

void SlicedFormFactorList::addFormFactor(const IFormFactor& formfactor,
                                         const MultiLayer& multilayer, double position_offset)
{
    size_t layer_index = LayerIndexBottom(formfactor, multilayer, position_offset);
    m_ff_list.emplace_back(std::unique_ptr<IFormFactor>(formfactor.clone()), layer_index);
}

size_t SlicedFormFactorList::size() const
{
    return m_ff_list.size();
}

std::pair<const IFormFactor*, size_t> SlicedFormFactorList::operator[](size_t index) const
{
    if (index >= size())
        throw std::out_of_range("SlicedFormFactorList::operator[] error: "
                                "index out of range");
    return { m_ff_list[index].first.get(), m_ff_list[index].second };
}

namespace {
size_t LayerIndexBottom(const IFormFactor& ff, const MultiLayer& multilayer,
                        double position_offset)
{
    std::unique_ptr<IRotation> P_rot(IRotation::createIdentity());
    double zmin = ff.bottomZ(*P_rot) + position_offset;
    return multilayer.bottomZToLayerIndex(zmin);
}

size_t LayerIndexTop(const IFormFactor& ff, const MultiLayer& multilayer,
                        double position_offset)
{
    std::unique_ptr<IRotation> P_rot(IRotation::createIdentity());
    double zmin = ff.topZ(*P_rot) + position_offset;
    return multilayer.topZToLayerIndex(zmin);
}
}

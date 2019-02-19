// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpacePositionBuilder.cpp
//! @brief     Implements class RealSpacePositionBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpacePositionBuilder.h"
#include "IPositionBuilder.h"

RealSpacePositionBuilder::RealSpacePositionBuilder() : mP_pos_builder{nullptr} {}

RealSpacePositionBuilder::~RealSpacePositionBuilder() = default;

void RealSpacePositionBuilder::visit(const InterferenceFunction1DLattice* p_iff) {}

void RealSpacePositionBuilder::visit(const InterferenceFunction2DLattice* p_iff) {}

void RealSpacePositionBuilder::visit(const InterferenceFunction2DParaCrystal* p_iff) {}

void RealSpacePositionBuilder::visit(const InterferenceFunctionFinite2DLattice* p_iff) {}

void RealSpacePositionBuilder::visit(const InterferenceFunctionRadialParaCrystal* p_iff) {}

void RealSpacePositionBuilder::visit(const InterferenceFunctionNone*)
{
    mP_pos_builder.reset(new RandomPositionBuilder());
}

std::vector<std::vector<double>> RealSpacePositionBuilder::generatePositions(double layer_size,
                                                                             double density) const
{
    if (!mP_pos_builder) {
        return {};
    }
    return mP_pos_builder->generatePositions(layer_size, density);
}

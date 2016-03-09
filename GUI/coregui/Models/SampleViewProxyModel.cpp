// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.cpp
//! @brief     Implements class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleViewProxyModel.h"

int SampleViewProxyModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

bool SampleViewProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    if (!sourceParent.isValid())
        return true;
    return !sourceModel()->data(index, Qt::DisplayRole).isValid();
//    return (type == Constants::MultiLayerType || type == Constants::LayerType || type == Constants::ParticleType
//            || type == Constants::ParticleCompositionType || type == Constants::ParticleCoreShellType
//            || type == Constants::ParticleDistributionType);
}

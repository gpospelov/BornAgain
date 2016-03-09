// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleViewComponents.cpp
//! @brief     Implements class SampleViewComponents
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleViewComponents.h"
#include "widgetbox.h"
#include "SampleDesigner.h"


SampleWidgetBox *SampleViewComponents::createWidgetBox(
        SampleDesignerInterface *core, QWidget *parent)
{
    return new SampleWidgetBox(core, parent);
}

ItemTreeView *SampleViewComponents::createTreeView(
        SampleModel *sampleModel, QWidget *parent)
{
    ItemTreeView *tree_view = new ItemTreeView(parent);
    MySortFilterProxyModel *proxy = new MySortFilterProxyModel(parent);
    proxy->setSourceModel(sampleModel);
    tree_view->setModel(proxy);
    return tree_view;
}


bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    if (!sourceParent.isValid())
        return true;
    return !sourceModel()->data(index, Qt::DisplayRole).isValid();
//    return (type == Constants::MultiLayerType || type == Constants::LayerType || type == Constants::ParticleType
//            || type == Constants::ParticleCompositionType || type == Constants::ParticleCoreShellType
//            || type == Constants::ParticleDistributionType);
}

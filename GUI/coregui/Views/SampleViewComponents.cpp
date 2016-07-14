// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleViewComponents.cpp
//! @brief     Implements class SampleViewComponents
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FilterPropertyProxy.h"
#include "SampleViewComponents.h"


SampleWidgetBox *SampleViewComponents::createWidgetBox(
        SampleDesignerInterface *core, QWidget *parent)
{
    return new SampleWidgetBox(core, parent);
}

ItemTreeView *SampleViewComponents::createTreeView(
        SampleModel *sampleModel, QWidget *parent)
{
    ItemTreeView *tree_view = new ItemTreeView(parent);
    FilterPropertyProxy *proxy = new FilterPropertyProxy(1, parent);
    proxy->setSourceModel(sampleModel);
    tree_view->setModel(proxy);
    tree_view->setAttribute(Qt::WA_MacShowFocusRect, false);
    return tree_view;
}




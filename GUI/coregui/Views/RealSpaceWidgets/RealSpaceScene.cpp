// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceScene.cpp
//! @brief     Implements class RealSpaceScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpaceScene.h"
#include "SampleModel.h"
#include <QDebug>

RealSpaceScene::RealSpaceScene(QObject* parent)
    : QObject(parent)
{

}

void RealSpaceScene::setModel(SampleModel* model)
{
    m_model = model;

}

void RealSpaceScene::onSelectionChanged(const QModelIndex& selected)
{
    if(selected.isValid())
        return;

    m_rootIndex = selected;
}

void RealSpaceScene::updateScene()
{

}

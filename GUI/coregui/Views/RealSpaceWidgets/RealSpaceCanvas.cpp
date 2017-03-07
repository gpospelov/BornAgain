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

#include "RealSpaceCanvas.h"
#include "SampleModel.h"
#include <QDebug>

RealSpaceCanvas::RealSpaceCanvas(QObject* parent)
    : QObject(parent)
{

}

void RealSpaceCanvas::setModel(SampleModel* model)
{
    m_model = model;

}

void RealSpaceCanvas::onSelectionChanged(const QModelIndex& selected)
{
    if(selected.isValid())
        return;

    m_rootIndex = selected;
}

void RealSpaceCanvas::updateScene()
{

}

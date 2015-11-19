// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorCanvas.cpp
//! @brief     Implements class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorCanvas.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskGraphicsProxy.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QModelIndex>

#include "SimulationRegistry.h"
#include <boost/scoped_ptr.hpp>
#include "SampleBuilderFactory.h"
#include "IntensityDataItem.h"
#include "ColorMapPlot.h"

MaskEditorCanvas::MaskEditorCanvas(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene, this))
{
    setObjectName(QStringLiteral("MaskEditorCanvas"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

}

void MaskEditorCanvas::setModel(SessionModel *model, const QModelIndex &rootIndex)
{
    m_scene->setModel(model, rootIndex);
}

void MaskEditorCanvas::setSelectionModel(QItemSelectionModel *model)
{
    m_scene->setSelectionModel(model);
}

MaskGraphicsScene *MaskEditorCanvas::getScene()
{
    return m_scene;
}

MaskGraphicsView *MaskEditorCanvas::getView()
{
    return m_view;
}

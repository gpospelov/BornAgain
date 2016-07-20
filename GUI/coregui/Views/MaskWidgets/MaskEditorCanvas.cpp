// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorCanvas.cpp
//! @brief     Implements class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaskEditorCanvas.h"
#include "MaskGraphicsProxy.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskResultsPresenter.h"
#include "SessionModel.h"
#include <QDebug>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QModelIndex>
#include <QVBoxLayout>


MaskEditorCanvas::MaskEditorCanvas(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene, this))
    , m_resultsPresenter(new MaskResultsPresenter(this))
{
    setObjectName(QStringLiteral("MaskEditorCanvas"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

}

void MaskEditorCanvas::setMaskContext(SessionModel *model, const QModelIndex &maskContainerIndex,
                                      IntensityDataItem *intensityItem)
{
    m_scene->setMaskContext(model, maskContainerIndex, intensityItem);
    m_resultsPresenter->setMaskContext(model, maskContainerIndex, intensityItem);
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

void MaskEditorCanvas::onPresentationTypeRequest(MaskEditorFlags::PresentationType presentationType)
{
    m_resultsPresenter->updatePresenter(presentationType);
    m_scene->onPresentationTypeRequest(presentationType);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.cpp
//! @brief     Implements class ProjectionsEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsEditorCanvas.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "ColorMapLabel.h"
#include <QVBoxLayout>

ProjectionsEditorCanvas::ProjectionsEditorCanvas(QWidget* parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene))
    , m_statusLabel(new ColorMapLabel(0, this))
{
    setObjectName(QStringLiteral("MaskEditorCanvas"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void ProjectionsEditorCanvas::setContext(SessionModel* model,
                                         const QModelIndex& shapeContainerIndex,
                                         IntensityDataItem* intensityItem)
{
    m_scene->setMaskContext(model, shapeContainerIndex, intensityItem);
    m_view->updateSize(m_view->size());
    m_statusLabel->addColorMap(m_scene->colorMap());
}

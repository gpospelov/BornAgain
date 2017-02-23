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
#include "ColorMap.h"
#include "ColorMapLabel.h"
#include "ColorMapEvent.h"
#include "MaskItems.h"
#include <QVBoxLayout>
#include <QItemSelectionModel>
#include <QDebug>

ProjectionsEditorCanvas::ProjectionsEditorCanvas(QWidget* parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene))
    , m_colorMap(nullptr)
    , m_statusLabel(new ColorMapLabel(0, this))
    , m_liveProjection(nullptr)
    , m_model(nullptr)
    , m_intensityDataItem(nullptr)
    , m_selectionModel(nullptr)
    , m_currentActivity(MaskEditorFlags::HORIZONTAL_LINE_MODE)
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
    delete m_selectionModel;
    m_selectionModel = new QItemSelectionModel(model, this);

    m_model = model;
    m_scene->setMaskContext(model, shapeContainerIndex, intensityItem);
    m_scene->setSelectionModel(m_selectionModel);
    m_view->updateSize(m_view->size());

    m_containerIndex = shapeContainerIndex;
    m_intensityDataItem = intensityItem;

    setColorMap(m_scene->colorMap());
}

void ProjectionsEditorCanvas::onEnteringColorMap()
{
    qDebug() << "ProjectionsEditorCanvas::onEnteringColorMap()";
    Q_ASSERT(m_liveProjection == nullptr);
    Q_ASSERT(m_containerIndex.isValid());

    if(m_currentActivity == MaskEditorFlags::HORIZONTAL_LINE_MODE)
        m_liveProjection = m_model->insertNewItem(Constants::HorizontalLineMaskType,
                                               m_containerIndex);
    else if(m_currentActivity == MaskEditorFlags::VERTICAL_LINE_MODE)
        m_liveProjection = m_model->insertNewItem(Constants::VerticalLineMaskType,
                                               m_containerIndex);

    if(m_liveProjection)
        m_liveProjection->setItemValue(MaskItem::P_IS_VISIBLE, false);

}

void ProjectionsEditorCanvas::onLeavingColorMap()
{
    qDebug() << "ProjectionsEditorCanvas::onLeavingColorMap()";
    if (m_liveProjection) {
        m_liveProjection->parent()->takeRow(
                    m_liveProjection->parent()->rowOfChild(m_liveProjection));
        delete m_liveProjection;
        m_liveProjection = nullptr;
    }
}

void ProjectionsEditorCanvas::onPositionChanged(double x, double y)
{
    qDebug() << "ProjectionsEditorCanvas::onPositionChanged()" << x << y;
    if(m_liveProjection) {
        if(m_currentActivity == MaskEditorFlags::HORIZONTAL_LINE_MODE)
            m_liveProjection->setItemValue(HorizontalLineItem::P_POSY, y);
        else if(m_currentActivity == MaskEditorFlags::VERTICAL_LINE_MODE)
            m_liveProjection->setItemValue(VerticalLineItem::P_POSX, x);
    }
}

void ProjectionsEditorCanvas::onResetViewRequest()
{
    m_view->onResetViewRequest();
    m_intensityDataItem->resetView();
}

void ProjectionsEditorCanvas::onActivityModeChanged(MaskEditorFlags::Activity value)
{
    m_currentActivity = value;
    getScene()->onActivityModeChanged(value);
    onLeavingColorMap();
}

void ProjectionsEditorCanvas::setColorMap(ColorMap* colorMap)
{
    Q_ASSERT(colorMap);
    setConnected(false);

    m_colorMap = colorMap;
    setConnected(true);

    m_statusLabel->reset();
    m_statusLabel->addColorMap(colorMap);
}

void ProjectionsEditorCanvas::setConnected(bool isConnected)
{
    if(!m_colorMap)
        return;

    if(isConnected) {
        connect(m_colorMap->colorMapEvent(), SIGNAL(enteringColorMap()),
                this, SLOT(onEnteringColorMap()), Qt::UniqueConnection);
        connect(m_colorMap->colorMapEvent(), SIGNAL(leavingColorMap()),
                this, SLOT(onLeavingColorMap()), Qt::UniqueConnection);
        connect(m_colorMap->colorMapEvent(), SIGNAL(positionChanged(double, double)),
                this, SLOT(onPositionChanged(double, double)), Qt::UniqueConnection);
    }

    else {
        disconnect(m_colorMap->colorMapEvent(), SIGNAL(enteringColorMap()),
                this, SLOT(onEnteringColorMap()));
        disconnect(m_colorMap->colorMapEvent(), SIGNAL(leavingColorMap()),
                this, SLOT(onLeavingColorMap()));
        disconnect(m_colorMap->colorMapEvent(), SIGNAL(positionChanged(double, double)),
                this, SLOT(onPositionChanged(double, double)));
    }
}

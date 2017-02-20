// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorCanvas.h
//! @brief     Defines class ProjectionsEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSEDITORCANVAS_H
#define PROJECTIONSEDITORCANVAS_H

#include "WinDllMacros.h"
#include <QWidget>
#include <QModelIndex>

class MaskGraphicsScene;
class MaskGraphicsView;
class SessionModel;
class IntensityDataItem;
class ColorMap;
class ColorMapLabel;
class SessionItem;

//! Holds a graphics scene to draw projections on top of ColorMap. Being a part
//! of ProjectionEditor, provides interaction logic between graphics scene and ProjectionsWidget.

//! Particularly, it creates temporary ProjectionItem in projection container, when mouse
//! is inside ColorMap viewport.

class ProjectionsEditorCanvas : public QWidget
{
    Q_OBJECT

public:
    ProjectionsEditorCanvas(QWidget* parent = 0);

    void setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                    IntensityDataItem* intensityItem);

public slots:
    void onEnteringColorMap();
    void onLeavingColorMap();
    void onPositionChanged(double x, double y);

private:
    void setColorMap(ColorMap* colorMap);
    void setConnected(bool isConnected);

    MaskGraphicsScene* m_scene;
    MaskGraphicsView* m_view;
    ColorMap* m_colorMap;
    ColorMapLabel* m_statusLabel;    

    SessionItem* m_xProjection;
    SessionModel* m_model;
    QModelIndex m_containerIndex;
};

#endif // PROJECTIONSEDITORCANVAS_H

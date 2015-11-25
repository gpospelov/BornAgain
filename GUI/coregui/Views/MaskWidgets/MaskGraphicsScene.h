// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsScene.h
//! @brief     Defines class MaskGraphicsScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKGRAPHICSSCENE_H
#define MASKGRAPHICSSCENE_H

#include "MaskDrawingContext.h"
#include <QGraphicsScene>
#include <QModelIndex>
#include <QMap>
#include <QSharedPointer>

class SessionModel;
class ParameterizedItem;
class IMaskView;
class ISceneAdaptor;
class MaskGraphicsProxy;
class QItemSelectionModel;
class QItemSelection;
class PolygonView;
class MaskEditorAction;

//! Graphics scene for MaskEditorCanvas to draw masks on top of intensity data widgets.

class BA_CORE_API_ MaskGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MaskGraphicsScene(QObject *parent = 0);

    void setModel(SessionModel *model, const QModelIndex &rootIndex);
    void setSelectionModel(QItemSelectionModel *model);

signals:
    void itemContextMenuRequest(const QPoint &point);

public slots:
    void onActivityModeChanged(MaskEditorFlags::Activity value);
    void onMaskValueChanged(MaskEditorFlags::MaskValue value);
    void onResetViewRequest();

    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
    void cancelCurrentDrawing();

    void resetScene();
    void updateScene();

private slots:
    void onSessionSelectionChanged(const QItemSelection & /* selected */,
                                   const QItemSelection & /* deselected */);
    void onSceneSelectionChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);


private:
    void init_scene();
    void updateViews(const QModelIndex &parentIndex = QModelIndex(), IMaskView *parentView = 0);
    void updateProxyWidget(const QModelIndex &parentIndex);
    void deleteViews(const QModelIndex & itemIndex);
    void removeItemViewFromScene(ParameterizedItem *item);

    bool isValidMouseClick(QGraphicsSceneMouseEvent *event);
    bool isValidForRectangleDrawing(QGraphicsSceneMouseEvent *event);
    bool isValidForEllipseDrawing(QGraphicsSceneMouseEvent *event);
    bool isValidForPolygonDrawing(QGraphicsSceneMouseEvent *event);
    bool isValidForLineDrawing(QGraphicsSceneMouseEvent *event);
    bool isValidForMaskAllDrawing(QGraphicsSceneMouseEvent *event);
    bool isAreaContainsSizeHandles(QGraphicsSceneMouseEvent *event);

    bool isDrawingInProgress() const;
    void setDrawingInProgress(bool value);
    void makeViewAtMousePosSelected(QGraphicsSceneMouseEvent *event);

    IMaskView* addViewForItem(ParameterizedItem *item);

    void processRectangleItem(QGraphicsSceneMouseEvent *event);
    void processEllipseItem(QGraphicsSceneMouseEvent *event);
    void processPolygonItem(QGraphicsSceneMouseEvent *event);
    void processLineItem(QGraphicsSceneMouseEvent *event);
    void processVerticalLineItem(const QPointF &pos);
    void processHorizontalLineItem(const QPointF &pos);
    void processMaskAllItem(QGraphicsSceneMouseEvent *event);

    void setZValues();
    PolygonView *getCurrentPolygon() const;
    void setItemName(ParameterizedItem *itemToChange);

    SessionModel *m_model;
    QItemSelectionModel *m_selectionModel;
    QSharedPointer<ISceneAdaptor> m_adaptor;
    QMap<ParameterizedItem *, IMaskView *> m_ItemToView;
    MaskGraphicsProxy *m_proxy;
    bool m_block_selection;
    QModelIndex m_rootIndex; //! Index in the model corresponding to IntensityDataItem
    ParameterizedItem *m_currentItem;
    QPointF m_currentMousePosition;
    MaskDrawingContext m_context;
};


#endif

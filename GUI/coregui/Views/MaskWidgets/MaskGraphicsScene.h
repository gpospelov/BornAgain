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

#include "MaskEditorActivity.h"
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

//! Graphics scene for MaskEditorCanvas

class MaskGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MaskGraphicsScene(QObject *parent = 0);

    void setModel(SessionModel *model, const QModelIndex &rootIndex);
    void setSelectionModel(QItemSelectionModel *model);

public slots:
    void onActivityModeChanged(MaskEditorActivity::Flags value);
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);
    void deleteSelectedItems();
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

private:
    void init_scene();
    void updateViews(const QModelIndex &parentIndex = QModelIndex(), IMaskView *parentView = 0);
    void updateProxyWidget(const QModelIndex &parentIndex);
    void deleteView(const QModelIndex & itemIndex);

//    void makeSelected(const QModelIndex &parent, int first, int last);

    bool isAllowedToStartDrawing(QGraphicsSceneMouseEvent *event);
    bool isDrawingInProgress() const;
    void setDrawingInProgress(bool value);
    void makeTopViewSelected(QGraphicsSceneMouseEvent *event);

    IMaskView* addViewForItem(ParameterizedItem *item);

    void processRectangleItem(QGraphicsSceneMouseEvent *event);
    void setZValues();

    SessionModel *m_model;
    QItemSelectionModel *m_selectionModel;
    QSharedPointer<ISceneAdaptor> m_adaptor;
    QMap<ParameterizedItem *, IMaskView *> m_ItemToView;
    MaskGraphicsProxy *m_proxy;
    bool m_block_selection;
    MaskEditorActivity::Flags m_activityType;
    QModelIndex m_rootIndex; //! Index in the model corresponding to IntensityDataItem
    ParameterizedItem *m_currentItem;
};


#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/DesignerScene.h
//! @brief     Defines class DesignerScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H

#include "WinDllMacros.h"
#include <QGraphicsScene>
#include <QModelIndex>
#include <QMap>

class InstrumentModel;
class SampleModel;
class SessionItem;
class SessionGraphicsItem;
class QItemSelectionModel;
class IView;
class QItemSelection;
class NodeEditorConnection;
class DesignerMimeData;
class SampleViewAligner;
class NodeEditor;
class SampleViewProxyModel;


//! Main class which represents SessionModel on graphics scene
class BA_CORE_API_ DesignerScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = 0);
    virtual ~DesignerScene();

    void setSampleModel(SampleModel *sampleModel);
    void setInstrumentModel(InstrumentModel *instrumentModel);
    void setSelectionModel(QItemSelectionModel *model, SampleViewProxyModel *proxy);

    SampleModel *getSampleModel() { return m_sampleModel; }

    IView *getViewForItem(SessionItem *item) { return m_ItemToView[item]; }

    NodeEditor *getNodeEditor() { return m_nodeEditor;}

signals:
    void selectionModeChangeRequest(int);

public slots:
    void onSceneSelectionChanged();
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);
    void resetScene();
    void updateScene();

    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);

    void setLayerInterfaceLine(const QLineF &line=QLineF()) { m_layer_interface_line = line; }

    void deleteSelectedItems();

    void onEstablishedConnection(NodeEditorConnection *); // to process signals from NodeEditor
    void removeConnection(NodeEditorConnection *);

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void onSmartAlign();


protected:
    void drawForeground(QPainter* painter, const QRectF& rect);
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:

    IView *addViewForItem(SessionItem *item);
    void updateViews(const QModelIndex &parentIndex = QModelIndex(), IView *parentView = 0);
    void deleteViews(const QModelIndex & parentIndex);
    void alignViews();
    void removeItemViewFromScene(SessionItem *item);
    bool isMultiLayerNearby(QGraphicsSceneDragDropEvent *event);
    void adjustSceneRect();
    bool isAcceptedByMultiLayer(const DesignerMimeData *mimeData, QGraphicsSceneDragDropEvent *event);
    bool isLayerDragged() const;

    SampleModel *m_sampleModel;
    InstrumentModel *m_instrumentModel;
    QItemSelectionModel *m_selectionModel;
    SampleViewProxyModel *m_proxy;
    bool m_block_selection;

    QMap<SessionItem *, IView *> m_ItemToView;
    //!< Correspondance of model's item and scene's view

    QLineF m_layer_interface_line;
    //!< Foreground line representing appropriate interface during layer's movement

    SampleViewAligner *m_aligner;

    NodeEditor *m_nodeEditor;
};


#endif


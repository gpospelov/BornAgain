#ifndef DESIGNERSCENE_H
#define DESIGNERSCENE_H


#include <QGraphicsScene>
#include <QModelIndex>
#include <QMap>

class SessionModel;
class ParameterizedItem;
class ParameterizedGraphicsItem;
class QItemSelectionModel;
class IView;
class QItemSelection;
class NodeEditorConnection;
class DesignerMimeData;


//! Main class which represents SessionModel on graphics scene
class DesignerScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit DesignerScene(QObject *parent = 0);
    virtual ~DesignerScene(){}

    void setSessionModel(SessionModel *model);
    void setSelectionModel(QItemSelectionModel *model);

    SessionModel *getSessionModel() { return m_sessionModel; }

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

protected:
    void drawForeground(QPainter* painter, const QRectF& rect);
    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

private:
    IView *addViewForItem(ParameterizedItem *item);
    void updateViews(const QModelIndex &parentIndex = QModelIndex(), IView *parentView = 0);
    void deleteViews(const QModelIndex & parentIndex);
    void alignViews();
    void removeItemViewFromScene(ParameterizedItem *item);
    bool isMultiLayerNearby(QGraphicsSceneDragDropEvent *event);

    SessionModel *m_sessionModel;
    QItemSelectionModel *m_selectionModel;
    bool m_block_selection;

    QMap<ParameterizedItem *, IView *> m_ItemToView;
    //!< COrrespondance of model's item and scene's view

    QList<IView *> m_orderedViews;
    //!< helper list of views in the order corresponding items appearing in
    //!< the model for alignment purposes

    QLineF m_layer_interface_line;
    //!< foreground line representing appropriate interface during lauer's movement
};


#endif


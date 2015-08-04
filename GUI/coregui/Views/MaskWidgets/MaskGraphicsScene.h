#ifndef MASKGRAPHICSSCENE_H
#define MASKGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QItemSelection>
#include <QModelIndex>

class RectangleItem;
class MaskModel;
class ParameterizedItem;
class QListView;
class QTreeView;
class QItemSelectionModel;
class IView;
class QSelectionModel;

class MaskGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MaskGraphicsScene();
    enum DrawingMode { NONE, RECTANGLE, ELLIPSE, POLYGON };
    void setDrawing(DrawingMode drawingMode);
    void setSelectionModel(QItemSelectionModel *selectionModel);
    void setModel(MaskModel *maskModel);
    void onBringToFront();
    void onSendToBack();

public slots:
    void deleteSelectedItems();
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);
    void onRowsRemoved(const QModelIndex &, int, int);
    void onRowsInserted(const QModelIndex &, int, int);
    void onSceneSelectionChanged();
    void resetScene();
    void updateScene();

signals:
    void itemIsDrawn();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &);

private:
    void setItemName(ParameterizedItem *item);
    void deleteViews(const QModelIndex &parentIndex);
    void removeItemViewFromScene(ParameterizedItem *item);
    void updateViews(const QModelIndex &parentIndex = QModelIndex());
    IView *addViewForItem(ParameterizedItem *item);


    MaskModel *m_maskModel;
    QItemSelectionModel *m_selectionModel;
    QMap<ParameterizedItem *, IView *> m_ItemToView;
    DrawingMode m_drawingMode;
    ParameterizedItem *m_currentItem;
    QPointF m_currentMousePosition;
    QPointF m_lastAddedPoint;
    bool m_block_selection;
    int numberOfPoints();
    bool firstPointContainsMouseClick(QGraphicsSceneMouseEvent *event);
    void sortModelByZValue();
    void setZValues();
};
#endif

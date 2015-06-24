#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainterPath>
#include <QBrush>
#include <QItemSelection>

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

class Rectangle;
class Ellipse;
class Polygon;
class RectangleItem;
class RectangleView;
class MaskModel;
class ParameterizedItem;
class QListView;
class QItemSelectionModel;
class IView;


#include <QModelIndex>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene();
    enum Drawing { NONE, RECTANGLE, ELLIPSE, POLYGON };
    void setDrawing(Drawing drawing);

    void setMaskModel(MaskModel *maskModel);
    void setListView(QListView *listview);

public slots:
    void deleteSelectedItems();
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);
    void onRowsRemoved(const QModelIndex &, int, int);
    void onRowsInserted(const QModelIndex &, int, int);
    void onSceneSelectionChanged();
    void resetScene();
    void updateScene();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &);

private:
    void deleteViews(const QModelIndex &parentIndex);
    void removeItemViewFromScene(ParameterizedItem *item);
    void updateViews(const QModelIndex &parentIndex = QModelIndex());
    QGraphicsItem *addViewForItem(ParameterizedItem *item);


    MaskModel *m_maskModel;
    QListView *m_listView;
    QItemSelectionModel *m_selectionModel;
    QMap<ParameterizedItem *, IView *> m_ItemToView;

    Drawing m_drawing;
    Rectangle *m_rectangle;
    ParameterizedItem *m_rectangleItem;
    RectangleView *m_rectangleView;
    Ellipse *m_ellipse;
    Polygon *m_polygon;
    bool isFinished;
    QPointF m_currentMousePosition;
    QPointF m_lastAddedPoint;
    bool m_block_selection;
};
#endif

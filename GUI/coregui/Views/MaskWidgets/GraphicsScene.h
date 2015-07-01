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
class PolygonView;
class MaskModel;
class ParameterizedItem;
class QListView;
class QTreeView;
class QItemSelectionModel;
class IView;


#include <QModelIndex>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene();
    // FIXME bad naming of enumerator, DrawingMode?
    enum Drawing { NONE, RECTANGLE, ELLIPSE, POLYGON };
    void setDrawing(Drawing drawing);

    // FIXME Why you need TreeView here? You need SelectionModel.
    void setTreeView(QTreeView *treeView);
    void setModel(MaskModel *maskModel);

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
    // FIXME remove variable completely
    QTreeView *m_treeView;
    QItemSelectionModel *m_selectionModel;
    QMap<ParameterizedItem *, IView *> m_ItemToView;
    // FIXME Rename variable to m_drawingMode
    Drawing m_drawing;
    // FIXME I believe that you can replace all these variables with one ParameterizedItem m_currentItem
    ParameterizedItem *m_rectangleItem;
    ParameterizedItem *m_ellipseItem;
    ParameterizedItem *m_polygonItem;
    ParameterizedItem *m_pointItem;
    // FIXME rename variable, is not clear at all what it does. Do you need this variable at all? You have m_drawing
    bool isDrawing;
    QPointF m_currentMousePosition;
    QPointF m_lastAddedPoint;
    bool m_block_selection;
    // FIXME do you need this variables at all? You could just implement methods getNumberOfRectangles() and calculate a number on the flight
    //       It will have whose advantage, that if somebody from outside will remove an item from the model, you will get the number of the fly, without relying on your local variables
    int m_numberOfRectangle;
    int m_numberOfEllipse;
    int m_numberOfPolygon;

};
#endif

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
class QGraphicsItem;
class QGraphicsSceneMouseEvent;

class MaskGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MaskGraphicsScene(QObject *parent = 0);

    //! describes items that are currently being drawn
    enum DrawingMode { NONE, RECTANGLE, ELLIPSE, POLYGON };

    //! set drawing mode
    //! @param drawingMode item that shoulb be drawn
    void setDrawing(DrawingMode drawingMode);

    //! set selection Model
    //! @param selectionModel includes the selected item from the list view
    void setSelectionModel(QItemSelectionModel *selectionModel);

    //! set mask model
    //! @param maskModel contains all models for masking
    void setModel(MaskModel *maskModel);

    //! takes current selected item and put it one row upwards
    void onBringToFront();

    //! takes current selected item and put it one row below
    void onSendToBack();

public slots:
    //! delete current selected items
    void deleteSelectedItems();

    //! removes all items and views
    //! @param parent
    //! @param first child item
    //! @param last child item
    void onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last);

    //! selects selected items from list view on the graphics view
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);

    //! updates scene
    void onRowsRemoved(const QModelIndex &, int, int);

    //! updates scene
    void onRowsInserted(const QModelIndex &, int, int);

    //! selects selected items from graphics view on the list view
    void onSceneSelectionChanged();

    //! resets scene by clearing scene
    void resetScene();

    //! updates views, sets z-values and adds color map
    void updateScene();

signals:
    //! emits signal that current item is drawn (only working if it is uncommented)
    void itemIsDrawn();

protected:
    //! manages mouse press events
    //! @param event contains current mouse press
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse move events
    //! @param event contains current mouse move
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //! manages mouse release events
    //! @param event contains current mouse release
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //! draws dashed line when polygon is drawn
    //! @param painter to draw dashed line
    void drawForeground(QPainter *painter, const QRectF &);

private:
    MaskModel *m_maskModel;                //!< model that contains all mask items
    QItemSelectionModel *m_selectionModel; //!< model that contains all selected items
    QMap<ParameterizedItem *, IView *>
        m_ItemToView;                 //!< map that contains all items as key and all views as value
    DrawingMode m_drawingMode;        //!< current drawing mode
    ParameterizedItem *m_currentItem; //!<current item being drawn
    QPointF m_currentMousePosition;   //!< current mouse position
    QPointF m_lastAddedPoint;         //!< last added point to a polygon
    bool m_block_selection;           //!< blocks selection of items
    QPointF m_currentPoint;           //!< describes the current point of polygon
    QGraphicsItem *m_colorMap;        //!< color map (detector)
    int m_numberOfRectangles;         //!< number of rectangles were ever drawn
    int m_numberOfEllipses;           //!< number of ellipses were ever drawn
    int m_numberOfPolygons;           //!< number of polygon were ever drawn

    //! number of points from polygon
    //! @returns the number of points in polygon else 0
    int numberOfPoints();

    //! sets name to current item
    //! @param item currently drawn item
    void setItemName(ParameterizedItem *item);

    //! delete views
    //! @param parentIndex parameter for parent idex
    void deleteViews(const QModelIndex &parentIndex);

    //! removes item view from scene
    //! @param item to remove
    void removeItemViewFromScene(ParameterizedItem *item);

    //! updating views
    void updateViews(const QModelIndex &parentIndex = QModelIndex());

    //! adds view for item
    //! @param item parameter that gets a view
    IView *addViewForItem(ParameterizedItem *item);

    //! verifies if first point contains the current mouse press
    //! @param current mouse event
    //! @returns true if first point contains mouse click else false
    bool firstPointContainsMouseClick(QGraphicsSceneMouseEvent *event);

    //! sets z-values from views
    void setZValues();

    //! verifies drawing direction
    //! @param event to get current direction
    void drawingDirection(QGraphicsSceneMouseEvent *event);
};
#endif

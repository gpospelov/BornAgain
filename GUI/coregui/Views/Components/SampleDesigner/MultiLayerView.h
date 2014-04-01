#ifndef MULTILAYERVIEW_H
#define MULTILAYERVIEW_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QColor>
#include <QRectF>
#include <QRect>
#include <QGradient>
#include "ConnectableView.h"
#include <QStringList>


class LayerView;
class LayerView2;
class DesignerMimeData;



class MultiLayerView2 : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::MultiLayerType };

    MultiLayerView2(QGraphicsItem *parent = 0);

    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addView(IView *childView);

    virtual void addLayer(LayerView2 *layer, QPointF pos=QPointF());

public slots:
    void updateHeight();

};



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#include "LayerView.h"

class MultiLayerView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::MultiLayerType };

    MultiLayerView(QGraphicsItem *parent = 0);

    int type() const { return Type; }

    //! create top MultiLayer, which will be the dock for all Layer's and MultiLayer's
    static MultiLayerView *createTopMultiLayer();

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(IViewVisitor *visitor) { visitor->visit(this); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addLayer(LayerView *layer, QPointF pos=QPointF());
    void addBottomLayer(LayerView *layer);
    void addMultiLayer(MultiLayerView *layer, QPointF pos=QPointF());

    //! allows droping of object of given type
    void allowDropType(const QString &name);

    void setFixedX() { m_fixed_xpos = x(); m_fixed=true; }
    qreal getFixedX() { return m_fixed_xpos; }

public slots:
    void updateHeight();

signals:
    void LayerMoved();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);

//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    const DesignerMimeData *checkDragEvent(QGraphicsSceneDragDropEvent * event);

    //! returns true if given point is in alowed areas of multilayer
    bool isInDropArea(QPointF pos);

    //! returns true if name of the object match whose the multi layer can handle
    bool isExpectedObject(const QString &name);

private:
    QList<QRectF> m_drop_areas;
    QStringList m_expected_types;
    QStringList m_current_types;
    qreal m_fixed_xpos;
    bool m_fixed;
};




#endif // MULTILAYERVIEW_H

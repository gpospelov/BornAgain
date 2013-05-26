#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include "ISampleView.h"
#include "DesignerHelper.h"
#include <iostream>


//struct MyComplex {

//};



//! graphics representation of Layer
class LayerView : public ISampleRectView
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double thickness READ getThickness WRITE setThickness )
    Q_PROPERTY(complex_t refractive_index READ getRefractiveIndex WRITE setRefractiveIndex )

//    Q_PROPERTY(QColor color READ getColor WRITE setColor )

public:
    LayerView(QGraphicsItem *parent = 0);

//    QRectF boundingRect() const { return rect(); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//    QRect rect() const { return m_rect; }

    void setFixedX() { m_fixed_xpos = x(); m_fixed=true; }
    qreal getFixedX() { return m_fixed_xpos; }

    QString getName() const { return m_name; }
    double getThickness() const { return m_thickness; }
    QColor getColor() const { return m_color; }
    complex_t getRefractiveIndex() const { return m_refractive_index; }

public slots:
    void setName(const QString &name);
    void setThickness(double thickness);
    void setColor(const QColor &color);
    void setRefractiveIndex(const complex_t &index);

signals:
    void LayerMoved();

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
//    QColor m_color;
//    QRect m_rect;
    qreal m_fixed_xpos;
    bool m_fixed;

//    QString m_name;
    double m_thickness;
    complex_t m_refractive_index;
};


inline void LayerView::setName(const QString &name)
{
    if(name != m_name) {
        m_name = name;
    }
}

inline void LayerView::setThickness(double thickness)
{
    if(thickness != m_thickness) {
        m_thickness = thickness;
        m_rect.setHeight(DesignerHelper::nanometerToScreen(m_thickness));
        setPortCoordinates();
        emit heightChanged();
    }
}

inline void LayerView::setColor(const QColor &color)
{
    if(color != m_color) {
        m_color = color;
        update();
    }
}

inline void LayerView::setRefractiveIndex(const complex_t &refractive_index)
{
    if(m_refractive_index != refractive_index) {
        m_refractive_index = refractive_index;
    }
}



#endif // LAYERVIEW_H

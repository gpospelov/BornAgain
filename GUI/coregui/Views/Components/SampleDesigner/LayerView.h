#ifndef LAYERVIEW_H
#define LAYERVIEW_H

#include "ISampleView.h"
#include "DesignerHelper.h"
#include "MaterialBrowser.h"

//! graphics representation of Layer
class LayerView : public ISampleRectView
{
    Q_OBJECT

    Q_PROPERTY(QString name READ getName WRITE setName )
    Q_PROPERTY(double thickness READ getThickness WRITE setThickness )
    Q_PROPERTY(MaterialProperty material READ getMaterialProperty WRITE setMaterialProperty )

public:
    enum { Type = DesignerHelper::LayerType };
    LayerView(QGraphicsItem *parent = 0);

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) { visitor->visit(this); }

    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setFixedX() { m_fixed_xpos = x(); m_fixed=true; }
    qreal getFixedX() { return m_fixed_xpos; }
    double getThickness() const { return m_thickness; }
    MaterialProperty getMaterialProperty() const { return m_materialProperty; }

public slots:
    void setThickness(double thickness);
    void setMaterialProperty(const MaterialProperty &materialProperty);

signals:
    void LayerMoved();

protected:
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
//    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    qreal m_fixed_xpos;
    bool m_fixed;
    double m_thickness;
    MaterialProperty m_materialProperty;
};


inline void LayerView::setThickness(double thickness)
{
    if(thickness != m_thickness) {
        m_thickness = thickness;
        m_rect.setHeight(DesignerHelper::nanometerToScreen(m_thickness));
        setPortCoordinates();
        emit heightChanged();
    }
}


inline void LayerView::setMaterialProperty(const MaterialProperty &materialProperty)
{
    m_materialProperty = materialProperty;
    setColor(materialProperty.getColor());
    update();
}


#endif // LAYERVIEW_H

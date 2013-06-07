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
    LayerView(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setFixedX() { m_fixed_xpos = x(); m_fixed=true; }
    qreal getFixedX() { return m_fixed_xpos; }
    QString getName() const { return m_name; }
    double getThickness() const { return m_thickness; }
    QColor getColor() const { return m_color; }
    MaterialProperty getMaterialProperty() const { return m_materialProperty; }

public slots:
    void setName(const QString &name);
    void setThickness(double thickness);
    void setColor(const QColor &color);
    void setMaterialProperty(const MaterialProperty &materialProperty);

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
    qreal m_fixed_xpos;
    bool m_fixed;
    double m_thickness;
    MaterialProperty m_materialProperty;
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

inline void LayerView::setMaterialProperty(const MaterialProperty &materialProperty)
{
    m_materialProperty = materialProperty;
}


#endif // LAYERVIEW_H

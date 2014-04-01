#include "LayerView.h"
#include "Units.h"
#include "ParticleLayoutView.h"
#include "ParameterizedItem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

#include "DesignerHelper.h"
#include <iostream>




LayerView2::LayerView2(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultLayerWidth(), DesignerHelper::getDefaultLayerHeight()));
    setName(QString("Layer"));
    setToolTip(QString("%1\n%2").arg("Layer").arg("A layer with thickness and material.\nCan be connected with ParticleLayout."));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(false);

    addPort(" ", NodeEditorPort::Input, NodeEditorPort::ParticleFactory);
}


void LayerView2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}


void LayerView2::addView(IView *childView)
{
    qDebug() << "LayerView2::addView() " << m_item->itemName() << childView->getSessionItem()->itemName();
    ParticleLayoutView *layout = dynamic_cast<ParticleLayoutView *>(childView);
    Q_ASSERT(layout);
    connectInputPort(layout);
}


void LayerView2::onPropertyChange(QString propertyName)
{
    Q_ASSERT(m_item);
    if(propertyName == "Thickness") {
        m_rect.setHeight(DesignerHelper::nanometerToScreen(m_item->property("Thickness").toDouble()));
        setPortCoordinates();
        update();
        emit heightChanged();
    }
    IView::onPropertyChange(propertyName);
}


// ----------------------------------------------------------------------------


LayerView::LayerView(QGraphicsItem *parent)
    : ConnectableView(parent)
    , m_fixed_xpos(0)
    , m_fixed(false)
    , m_layer(new Layer())
//    , m_thickness(10*Units::nanometer)
{
    //setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultLayerWidth(), DesignerHelper::getDefaultLayerHeight()));
    setName(QString("Layer"));
    setToolTip(QString("%1\n%2").arg("LayerView").arg("Homogeneous layer"));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(false);

    addPort(" ", NodeEditorPort::Input, NodeEditorPort::ParticleFactory);
    setMaterialProperty(MaterialBrowser::getDefaultMaterialProperty());
}


void LayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}


void LayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // remove selection from child items
    QList<QGraphicsItem *> list = childItems();
    foreach(QGraphicsItem *item, list) {
        item->setSelected(false);
    }

    QGraphicsObject::mousePressEvent(event);
}

void LayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mouseReleaseEvent -> " << x() << " " << y() << std::endl;
    emit LayerMoved();
    QGraphicsObject::mouseReleaseEvent(event);
//    setCursor(Qt::ArrowCursor);
}


// layers are not allowed to move horizontally
QVariant LayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
     if (change == ItemPositionChange && scene() && m_fixed) {
         QPointF newPos = value.toPointF();
         newPos.setX(m_fixed_xpos);
         return newPos;
     }
     return QGraphicsItem::itemChange(change, value);
 }



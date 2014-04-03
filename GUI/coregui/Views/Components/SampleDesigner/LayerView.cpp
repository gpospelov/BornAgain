#include "LayerView.h"
#include "Units.h"
#include "ParticleLayoutView.h"
#include "ParameterizedItem.h"
#include "MultiLayerView.h"
#include "DesignerScene2.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include "DesignerHelper.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>



LayerView::LayerView(QGraphicsItem *parent)
    : ConnectableView(parent)
    , m_requested_parent(0)
      , m_requested_row(-1)

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


void LayerView::addView(IView *childView, int row)
{
    Q_UNUSED(row);
    qDebug() << "LayerView::addView() " << m_item->itemName() << childView->getParameterizedItem()->itemName();
    ParticleLayoutView *layout = dynamic_cast<ParticleLayoutView *>(childView);
    Q_ASSERT(layout);
    connectInputPort(layout);
}


void LayerView::onPropertyChange(QString propertyName)
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


QVariant LayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {

        m_requested_parent = 0;
        m_requested_row = -1;
        QRectF layerRect = mapRectToScene(boundingRect());
        foreach(QGraphicsItem *item, scene()->items()) {
            if(item->type() == DesignerHelper::MultiLayerType) {
                MultiLayerView *multilayer = qgraphicsitem_cast<MultiLayerView *>(item);
                if(multilayer->mapRectToScene(multilayer->boundingRect()).intersects(layerRect)) {
                    //qDebug() << "   XXX " << multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
                    m_requested_parent = multilayer;
                    m_requested_row = multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
                    break;
                }
            }
        }

        if(m_requested_parent) {
            DesignerScene2 *designerScene = dynamic_cast<DesignerScene2 *>(scene());
            QRectF rect = m_requested_parent->getDropArea(m_requested_row);
            designerScene->setLayerDropArea(m_requested_parent->mapRectToScene(rect));
        }
     }
     return QGraphicsItem::itemChange(change, value);
 }


void LayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_drag_start_position = pos();
    }
    QGraphicsItem::mousePressEvent(event);
}


void LayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "LayerView::mouseReleaseEvent()" << parentItem() << m_requested_parent << m_requested_row;

    DesignerScene2 *designerScene = dynamic_cast<DesignerScene2 *>(scene());
    designerScene->setLayerDropArea(QRectF());

    // Simple move of lonely layer across the scene: let it be.
    if(m_requested_parent == 0 && parentItem() == 0) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    Q_ASSERT(designerScene);
    SessionModel *model = designerScene->getSessionModel();

    // Layer was moved on top of MultiLayer but not in the right drop area:
    // returning layer back to starting position.
    if(m_requested_parent && m_requested_row == -1) {
        //qDebug() << "1.1 Layer->MultiLayer, wrong drop area.";
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved to the wrong row of his own MultiLayer: returning back.
    if(m_requested_parent == parentItem() && m_requested_row == model->indexOfItem(getParameterizedItem()).row()) {
        //Debug() << "1.2 Layer->MultiLayer (same), same drop area";
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved from MultiLayer he belong's to, to the empty place of
    // the scene: changing ownership.
    if(parentItem() && !m_requested_parent) {
        //qDebug() << "1.3 Layer->Scene";
        setPos( mapToScene(event->pos()) - event->pos());
        model->moveParameterizedItem(this->getParameterizedItem(), 0);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved either from one MultiLayer to another, or is moved inside
    // one multilayer: changing ownership.
    if(m_requested_parent) {
        //qDebug() << "1.4 MultiLayer->MultiLayer";
        model->moveParameterizedItem(this->getParameterizedItem(), m_requested_parent->getParameterizedItem(), m_requested_row);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // should not be here
    throw GUIHelpers::Error(tr("LayerView::mouseReleaseEvent() -> Loggic error."));
}




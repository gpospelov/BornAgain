#include "ILayerView.h"
#include "DesignerScene.h"
#include "DesignerHelper.h"
#include "MultiLayerView.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


class MultiLayerCandidate
{
public:
    MultiLayerCandidate() : multilayer(0), row(-1), distance(0){}
    MultiLayerView *multilayer;
    int row;
    int distance;
    bool operator< (const MultiLayerCandidate& cmp) const { return cmp.distance <  distance; }
};



ILayerView::ILayerView(QGraphicsItem *parent)
    : ConnectableView(parent)
    , m_requested_parent(0)
    , m_requested_row(-1)
{

}


void ILayerView::onPropertyChange(QString propertyName)
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


QVariant ILayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {

        findMultiLayerCandidate();
        if(m_requested_parent) {
            DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
            QRectF rect = m_requested_parent->getDropAreaRectangle(m_requested_row);
            designerScene->setLayerDropArea(m_requested_parent->mapRectToScene(rect));
        }

//        m_requested_parent = 0;
//        m_requested_row = -1;
//        qDebug() << "ILayerView::itemChange " << getParameterizedItem()->itemName();

//        QRectF layerRect = mapRectToScene(boundingRect());
//        foreach(QGraphicsItem *item, scene()->items()) {
//            if(item->type() == DesignerHelper::MultiLayerType
//                    && item != this
//                    && !childItems().contains(item)
//                    //&& item != this->parentItem()
//                    ) {
//                MultiLayerView *multilayer = qgraphicsitem_cast<MultiLayerView *>(item);
//                if(multilayer->mapRectToScene(multilayer->boundingRect()).intersects(layerRect)) {
//                    qDebug() << "   XXX " << multilayer->getParameterizedItem()->itemName() << multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
//                    m_requested_parent = multilayer;
//                    m_requested_row = multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
//                    break;
//                }
//            }
//        }

//        if(m_requested_parent) {
//            DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
//            QRectF rect = m_requested_parent->getDropAreaRectangle(m_requested_row);
//            designerScene->setLayerDropArea(m_requested_parent->mapRectToScene(rect));
//        }
     }
     return QGraphicsItem::itemChange(change, value);
 }



void ILayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        m_drag_start_position = pos();
    }
    QGraphicsItem::mousePressEvent(event);
}


void ILayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "ILayerView::mouseReleaseEvent()" << getParameterizedItem()->itemName() << QLineF(m_drag_start_position, pos()).length();
    qDebug() << "ILayerView::mouseReleaseEvent()  this:" << this << " parentItem: " << parentItem();
    qDebug() << "ILayerView::mouseReleaseEvent()  requested_parent:" << m_requested_parent << " requested_row:" << m_requested_row;

    DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
    Q_ASSERT(designerScene);
    designerScene->setLayerDropArea(QRectF()); // removing drop area hint from the scene

    if(QLineF(m_drag_start_position, pos()).length() == 0) {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    findMultiLayerCandidate();

    // Simple move of lonely layer across the scene: let it be.
    if(m_requested_parent == 0 && parentItem() == 0) {
        qDebug() << "ILayerView::mouseReleaseEvent() simple move of lonely layer";
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    SessionModel *model = designerScene->getSessionModel();

    // Layer was moved on top of MultiLayer but not in the right drop area:
    // returning layer back to starting position.
    if(m_requested_parent && m_requested_row == -1) {
        qDebug() << "1.1 Layer->MultiLayer, wrong drop area.";
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved to the wrong row of his own MultiLayer: returning back.
    if(m_requested_parent == parentItem() && m_requested_row == model->indexOfItem(getParameterizedItem()).row()) {
        qDebug() << "1.2 Layer->MultiLayer (same), same drop area";
        setPos(m_drag_start_position);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved from MultiLayer he belong's to, to the empty place of
    // the scene: changing ownership.
    if(parentItem() && !m_requested_parent) {
        qDebug() << "1.3 Layer->Scene";
        setPos( mapToScene(event->pos()) - event->pos());
        model->moveParameterizedItem(this->getParameterizedItem(), 0);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // Layer was moved either from one MultiLayer to another, or is moved inside
    // one multilayer: changing ownership.
    if(m_requested_parent) {
        qDebug() << "1.4 ILayerView->MultiLayer";
        model->moveParameterizedItem(this->getParameterizedItem(), m_requested_parent->getParameterizedItem(), m_requested_row);
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    // should not be here
    throw GUIHelpers::Error(tr("LayerView::mouseReleaseEvent() -> Loggic error."));
}


//! returns candidate into which we will move our ILayerView
void ILayerView::findMultiLayerCandidate()
{
    m_requested_parent = 0;
    m_requested_row = -1;
    qDebug() << "ILayerView::getMultiLayerCandidate()";

    QVector<MultiLayerCandidate > candidates;

    QRectF layerRect = mapRectToScene(boundingRect());
    foreach(QGraphicsItem *item, scene()->items()) {
        if(item->type() == DesignerHelper::MultiLayerType
                && item != this
                && !childItems().contains(item)
                )
        {
            MultiLayerView *multilayer = qgraphicsitem_cast<MultiLayerView *>(item);
            if(multilayer->mapRectToScene(multilayer->boundingRect()).intersects(layerRect)) {
                MultiLayerCandidate candidate;
                int row = multilayer->getDropArea(multilayer->mapFromScene(layerRect.center()));
                QRectF droparea = multilayer->mapRectToScene(multilayer->getDropAreaRectangle(row));
                int distance = std::abs(droparea.center().y() - layerRect.center().y());

                candidate.multilayer = multilayer;
                candidate.row = row;
                candidate.distance = distance;
                candidates.push_back(candidate);
            }
        }
    }

    qDebug() << "";
    foreach(MultiLayerCandidate candidate, candidates) {
        qDebug() << "xxx candidates" << candidate.multilayer << candidate.distance << candidate.row;
    }
    qDebug() << " sorting";
    if(candidates.size()) {
        qSort(candidates.begin(), candidates.end());
        m_requested_parent = candidates.front().multilayer;
        m_requested_row = candidates.front().row;
    }
}


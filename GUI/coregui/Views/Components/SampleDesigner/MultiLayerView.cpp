#include "MultiLayerView.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>
#include <iostream>
#include <QDropEvent>
#include <QStyleOptionGraphicsItem>

#include "LayerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"







MultiLayerView2::MultiLayerView2(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setColor(QColor(Qt::blue));
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultMultiLayerHeight()));
    setToolTip(QString("MultiLayer"));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(true);
}

void MultiLayerView2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(m_color);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}






// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


MultiLayerView::MultiLayerView(QGraphicsItem *parent)
    : ConnectableView(parent)
    , m_fixed_xpos(0)
    , m_fixed(false)
{
    setColor(QColor(Qt::blue));
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultMultiLayerHeight()));
    setToolTip(QString("MultiLayer"));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(true);

    m_expected_types << QString("Layer") << QString("MultiLayer");
    allowDropType(QString("Layer"));

    connect(this, SIGNAL(childrenChanged()), this, SLOT(updateHeight()));
    updateHeight();
}


// create top MultiLayer, which will be the dock for all Layer's and MultiLayer's
MultiLayerView *MultiLayerView::createTopMultiLayer()
{
    MultiLayerView *result = new MultiLayerView();
    result->setColor(Qt::lightGray);
    result->allowDropType(QString("MultiLayer"));
    result->setToolTip(QString("LayerDock\nDrag and drop here layer or multi layer"));
    result->setFlag(QGraphicsItem::ItemIsSelectable, false);
    result->setPos(-result->getRectangle().width()/2, 100.0);
    return result;
}



// allows droping of object of given type
void MultiLayerView::allowDropType(const QString &name) {
    if(m_current_types.contains(name)) {
        std::cout << "MultiLayerView::allowDropType -> Info. Name '" << name.toStdString() << "' is already in the list" << std::endl;
        return;
    }
    if(m_expected_types.contains(name)) {
        m_current_types.append(name);
    } else {
        std::cout << "MultiLayerView::allowDropType -> Warning. Can't handle the object with name' '" << name.toStdString() << "', expected names " << std::endl;
        foreach(QString s, m_expected_types) {
            std::cout << s.toStdString() << std::endl;
        }
    }
}



void MultiLayerView::addLayer(LayerView *layer, QPointF pos)
{
    //std::cout << "MultiLayerView::addLayer" << std::endl;
    // adjusting main rectangle othervise item->setPos will not work due to 'LayerView::itemChange'
    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

    int xpos = (DesignerHelper::getDefaultMultiLayerWidth() - layer->boundingRect().width())/2.;
    layer->setPos(xpos, pos.y());
    layer->setFixedX();
    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );
    connect(layer, SIGNAL(heightChanged()), this, SLOT(updateHeight()) );
    //connect(layer, SIGNAL(update()), this, SLOT(updateHeight()) );
    layer->setParentItem(this);
    //emit heightChanged();
}

void MultiLayerView::addBottomLayer(LayerView *layer)
{
    QPointF pos(0, m_rect.height());
    addLayer(layer, pos);
}



void MultiLayerView::addMultiLayer(MultiLayerView *layer, QPointF pos)
{
    std::cout << "MultiLayerView::addMultiLayer" << std::endl;
    // adjusting main rectangle othervise item->setPos will not work due to 'LayerView::itemChange'
    m_rect.setHeight(m_rect.height()+layer->boundingRect().height());

    int xpos = (DesignerHelper::getDefaultMultiLayerWidth() - layer->boundingRect().width())/2.;
    layer->setPos(xpos, pos.y());
    layer->setFixedX();
    connect(layer, SIGNAL(LayerMoved()), this, SLOT(updateHeight()) );
    connect(layer, SIGNAL(heightChanged()), this, SLOT(updateHeight()) );
    //connect(layer, SIGNAL(update()), this, SLOT(updateHeight()) );
    layer->setParentItem(this);
    //emit heightChanged();
}


// adjusts positions of Layers inside MultiLayer, updates total MultiLayer height
// calculates drop areas for new layers
// called when one of Layer is changed
void MultiLayerView::updateHeight()
{
    //std::cout << "MultiLayerView::updateHeight() " << std::endl;
    // drop areas are rectangles covering the area of layer interfaces
    m_drop_areas.clear();

    QList<QGraphicsItem *> list = childItems();
    qSort(list.begin(), list.end(), DesignerHelper::sort_layers);

    int total_height = 0;
    if( childItems().size() > 0) {
        foreach(QGraphicsItem *item, list) {
            item->setY(total_height);
            total_height += item->boundingRect().height();
            m_drop_areas.append(QRectF(0, item->y() - item->boundingRect().height()/4., boundingRect().width(), item->boundingRect().height()/2.));
        }
        m_drop_areas.append(QRectF(0, list.back()->y() +list.back()->boundingRect().height() - list.back()->boundingRect().height()/4., boundingRect().width(), list.back()->boundingRect().height()/2.));
    } else {
        total_height = DesignerHelper::getDefaultMultiLayerHeight();
        m_drop_areas.append(boundingRect());
    }

    m_rect.setHeight(total_height);
    update();
    emit heightChanged();
}


bool MultiLayerView::isInDropArea(QPointF pos)
{
    foreach(QRectF rect, m_drop_areas) {
        //std::cout << " drop areas " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << " point" << pos.x() << " " << pos.y() << std::endl;
        if (rect.contains(pos)) return true;
    }
    return false;
}

bool MultiLayerView::isExpectedObject(const QString &name)
{
    if(m_current_types.contains(name)) return true;
    return false;
}



void MultiLayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(m_color);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}


void MultiLayerView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        std::cout << "MultiLayerView::dragEnterEvent() -> INSIDE " << std::endl;
    }
}


void MultiLayerView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "MultiLayerView::dragLeaveEvent() -> " << std::endl;
}


void MultiLayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "MultiLayerView::dropEvent() -> " << std::endl;

    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
//        ISampleView *layer(0);
//        if(mimeData->getClassName() == QString("Layer") ) layer = new LayerView();
//        if(mimeData->getClassName() == QString("MultiLayer") ) layer = new MultiLayerView();

        if(mimeData->getClassName() == QString("Layer") ) {
            addLayer(new LayerView(), event->pos());
            update();
        } else if(mimeData->getClassName() == QString("MultiLayer") ) {
            addMultiLayer(new MultiLayerView(), event->pos());
            update();

//        if(layer){
//            std::cout << "MultiLayerView::dropEvent() -> adding layer or multilayer" << std::endl;
//            addLayer(layer, event->pos());
//            update();
        } else {
            std::cout << "MultiLayerView::dropEvent() -> Error. Can't create object " << mimeData->getClassName().toStdString() << std::endl;
        }
    }
}


void MultiLayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {
        std::cout << "MultiLayerView::dragMoveEvent() -> pos:" << event->pos().x() << " " << event->pos().y() << std::endl;
        update();

    }
}


void MultiLayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "MultiLayerView::mousePressEvent -> " << x() << " " << y() << std::endl;
    // remove selection from child items
    QList<QGraphicsItem *> list = childItems();
    foreach(QGraphicsItem *item, list) {
        item->setSelected(false);
    }

    QGraphicsObject::mousePressEvent(event);
}


void MultiLayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "MultiLayerView::mouseReleaseEvent -> " << x() << " " << y() << std::endl;
    emit LayerMoved();
    QGraphicsObject::mouseReleaseEvent(event);
}


//void MultiLayerView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    std::cout << "MultiLayerView::mouseMoveEvent -> " << x() << " " << y() << std::endl;
//    QGraphicsObject::mouseMoveEvent(event);
//}


//void MultiLayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    std::cout << "MultiLayerView::mousePressEvent -> " << x() << " " << y() << std::endl;
//    QGraphicsObject::mousePressEvent(event);
//}

//void MultiLayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    std::cout << "MultiLayerView::mouseReleaseEvent -> " << x() << " " << y() << std::endl;
//    QGraphicsObject::mouseReleaseEvent(event);
//}


const DesignerMimeData *MultiLayerView::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    std::cout << "MultiLayerView::checkDragEvent -> "  << std::endl;
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    if(mimeData->hasFormat("bornagain/widget")
            && isExpectedObject(mimeData->getClassName())
            && isInDropArea(event->pos()) ) {
        std::cout << "LayerDockView::checkDragEvent -> yes"  << std::endl;
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
    return mimeData;
}


// multi-layers are not allowed to move horizontally
QVariant MultiLayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
     if (change == ItemPositionChange && scene() && m_fixed) {
         // value is the new position.
         QPointF newPos = value.toPointF();
         newPos.setX(m_fixed_xpos);
         return newPos;
     }
     return QGraphicsItem::itemChange(change, value);
 }


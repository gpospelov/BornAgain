#include "MultiLayerView.h"
#include "ParameterizedItem.h"
#include "DesignerScene.h"
#include "SessionModel.h"
#include "LayerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"
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
#include <QDebug>



MultiLayerView::MultiLayerView(QGraphicsItem *parent)
    : ILayerView(parent)
{
    setColor(QColor(Qt::blue));
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultMultiLayerHeight()));
    setToolTip(QString("MultiLayer"));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(false);
    setAcceptDrops(true);

    connect(this, SIGNAL(childrenChanged()), this, SLOT(updateHeight()));
    updateGeometry();
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


void MultiLayerView::addView(IView *childView, int row)
{
    qDebug() << "MultiLayerView::addView() " << m_item->itemName() << childView->getParameterizedItem()->itemName() << "row" << row;
    ILayerView *layer = dynamic_cast<ILayerView *>(childView);
    Q_ASSERT(layer);

    if(!childItems().contains(layer)) {
        addNewLayer(layer, row);
    } else {
        int previous_row = m_layers.indexOf(layer);
        m_layers.swap(previous_row, row);
        qDebug() << "layer exists, swapping" << previous_row << row;
    }
    updateGeometry();
}


void MultiLayerView::addNewLayer(ILayerView *layer, int row)
{
    qDebug() << "MultiLayerView::addNewLayer(), row" << row;
    m_layers.insert(row, layer);
    int xpos = (DesignerHelper::getDefaultMultiLayerWidth() - layer->boundingRect().width())/2.;
    layer->setX(xpos);
    connect(layer, SIGNAL(heightChanged()), this, SLOT(updateHeight()) );
    connect(layer, SIGNAL(aboutToBeDeleted()), this, SLOT(onLayerAboutToBeDeleted()) );
    layer->setParentItem(this);
}


void MultiLayerView::onLayerAboutToBeDeleted()
{
    qDebug() << "MultiLayerView::onLayerAboutToBeDeleted()";
    ILayerView *layer = qobject_cast<ILayerView *>(sender());
    Q_ASSERT(layer);
    removeLayer(layer);
}


void MultiLayerView::removeLayer(ILayerView *layer)
{
    qDebug() << "MultiLayerView::removeLayer()";
    Q_ASSERT(m_layers.contains(layer));
    disconnect(layer, SIGNAL(heightChanged()), this, SLOT(updateHeight()) );
    m_layers.removeOne(layer);
    updateGeometry();
}


//! Updates geometry of MultiLayerView from current childs geometries
void MultiLayerView::updateGeometry()
{
    updateHeight();
    updateWidth();
    update();
}



void MultiLayerView::updateHeight()
{
    qDebug() << "MultiLayerView::updateHeight()";

    // drop areas are rectangles covering the area of layer interfaces
    m_drop_areas.clear();

    int total_height = 0;
    if(m_layers.size()) {
        foreach(ILayerView *layer, m_layers) {
            //int xpos = (DesignerHelper::getDefaultMultiLayerWidth() - layer->boundingRect().width())/2.;
            //layer->setPos(xpos, total_height);
            layer->setY(total_height);
            layer->update();
            total_height += layer->boundingRect().height();
            m_drop_areas.append(QRectF(0, layer->y() - layer->boundingRect().height()/4., boundingRect().width(), layer->boundingRect().height()/2.));
        }
        m_drop_areas.append(QRectF(0, m_layers.back()->y() +m_layers.back()->boundingRect().height() - m_layers.back()->boundingRect().height()/4., boundingRect().width(), m_layers.back()->boundingRect().height()/2.));
    } else {
        total_height = DesignerHelper::getDefaultMultiLayerHeight();
        m_drop_areas.append(boundingRect());
    }

    m_rect.setHeight(total_height);
    emit heightChanged();
}


//! Updates MultiLayerView width.
//! If list of children contains another MultiLayer, then width of given MultiLayer
//! will be increased
void MultiLayerView::updateWidth()
{
    double max_width(0);
    foreach(ILayerView *layer, m_layers) {
        if(layer->boundingRect().width() > max_width)
            max_width = layer->boundingRect().width();
    }
    if(max_width == 0) {
        max_width = DesignerHelper::getDefaultMultiLayerWidth();
    } else {
        m_rect.setWidth(max_width*1.1);
    }

    foreach(ILayerView *layer, m_layers) {
        int xpos = ((boundingRect().width() - layer->boundingRect().width()))/2.;
        layer->setX(xpos);
        layer->update();
    }

    emit widthChanged();
}


//! Returns index of drop area for given coordinate.
int MultiLayerView::getDropArea(QPointF pos)
{
    int area(-1);
    for(int i=0; i<m_drop_areas.size(); ++i) {
        if( m_drop_areas.at(i).contains(pos) ) {
            area = i;
            break;
        }
    }
    return area;
}


//! Returns true if given coordinate is inside one of drop areas.
bool MultiLayerView::isInDropArea(QPointF pos)
{
    foreach(QRectF rect, m_drop_areas) {
        if (rect.contains(pos)) return true;
    }
    return false;
}


//! Returns drop area rectangle corresponding to given row
QRectF MultiLayerView::getDropAreaRectangle(int row)
{
    if(row>=0 && row < m_drop_areas.size()) {
        return m_drop_areas[row];
    } else {
        return QRectF();
    }
}


void MultiLayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!checkDragEvent(event))
        QGraphicsItem::dragMoveEvent(event);
}


void MultiLayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    std::cout << "MultiLayerView::dropEvent() -> " << std::endl;

    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {

        DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
        if(designerScene) {
            SessionModel *sessionModel = designerScene->getSessionModel();

            qDebug() << "\n XXX" << getDropArea(event->scenePos()) << event->scenePos();
            sessionModel->insertNewItem(
                        mimeData->getClassName(),
                        sessionModel->indexOfItem(this->getParameterizedItem()),
                        getDropArea(event->pos())
                        );
        }
    }
}


const DesignerMimeData *MultiLayerView::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    std::cout << "MultiLayerView::checkDragEvent -> "  << std::endl;
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    int row = getDropArea(event->pos());
    if(mimeData->hasFormat("bornagain/widget")
            && getParameterizedItem()->acceptsAsChild(mimeData->getClassName())
            && row!=-1 ) {

        qDebug() << "MultiLayerView::checkDragEvent -> yes"  << row << getDropAreaRectangle(row);
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
    return mimeData;
}

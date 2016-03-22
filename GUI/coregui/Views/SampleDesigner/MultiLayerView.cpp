// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/MultiLayerView.cpp
//! @brief     Implements class MultiLayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerView.h"
#include "SessionItem.h"
#include "DesignerScene.h"
#include "SampleModel.h"
#include "LayerView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QDebug>



MultiLayerView::MultiLayerView(QGraphicsItem *parent)
    : ILayerView(parent)
{
    setColor(QColor(Qt::blue));

    //setRectangle(QRect(0, 0, DesignerHelper::getDefaultMultiLayerWidth(), DesignerHelper::getDefaultMultiLayerHeight()));
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::MultiLayerType));
    setToolTip(Constants::MultiLayerType);
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
        if(previous_row != row) {
            m_layers.swap(previous_row, row);
        }
    }
    updateGeometry();
}


void MultiLayerView::addNewLayer(ILayerView *layer, int row)
{
    qDebug() << "MultiLayerView::addNewLayer(), row" << row;
    m_layers.insert(row, layer);
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
    disconnect(layer, SIGNAL(aboutToBeDeleted()), this, SLOT(onLayerAboutToBeDeleted()) );
    m_layers.removeOne(layer);
    updateGeometry();
}


//! Updates geometry of MultiLayerView from current childs geometries.
void MultiLayerView::updateGeometry()
{
    updateHeight();
    updateWidth();
}


//! Updates MultiLayer height, sets y-positions of children, defines new drop areas.
void MultiLayerView::updateHeight()
{
    qDebug() << "MultiLayerView::updateHeight()";

    // drop areas are rectangles covering the area of layer interfaces
    m_drop_areas.clear();
    m_interfaces.clear();

    bool is_nested_multilayer(false);
    if( dynamic_cast<MultiLayerView *>(parentItem())) is_nested_multilayer = true;

    int total_height = 0;
    if(m_layers.size()) {
        foreach(ILayerView *layer, m_layers) {
            layer->setY(total_height);
            layer->update();

            qreal drop_area_height = layer->boundingRect().height()*0.5;
            qreal drop_area_ypos = total_height - drop_area_height/2.;
            if(total_height==0 && is_nested_multilayer) {
                drop_area_height = drop_area_height/2.;
                drop_area_ypos = total_height + drop_area_height/2.;
            }

            m_drop_areas.append(QRectF(0, drop_area_ypos, boundingRect().width(), drop_area_height));
            m_interfaces.append(QLineF(m_rect.left(), total_height, m_rect.right(), total_height));
            total_height += layer->boundingRect().height();
        }
        qreal drop_area_height = m_layers.back()->boundingRect().height()*0.5;
        qreal drop_area_ypos = total_height - drop_area_height/2.;
        if(is_nested_multilayer) {
            drop_area_height = drop_area_height/2.;
            drop_area_ypos = total_height - drop_area_height;
        }

        m_drop_areas.append(QRectF(0, drop_area_ypos, boundingRect().width(), drop_area_height));
        m_interfaces.append(QLineF(m_rect.left(), total_height, m_rect.right(), total_height));
    } else {
        total_height = DesignerHelper::getDefaultMultiLayerHeight();
        m_drop_areas.append(boundingRect());
        m_interfaces.append(QLineF(m_rect.left(), m_rect.center().y(), m_rect.right(), m_rect.center().y()));
    }

    m_rect.setHeight(total_height);
    update();
    emit heightChanged();
}


//! Updates MultiLayerView width, sets x-positions of children.
//! If list of children contains another MultiLayer, then width of given MultiLayer
//! will be increased by 12%
void MultiLayerView::updateWidth()
{
    const double wider_than_children(1.15);
    double max_width(0);
    foreach(ILayerView *layer, m_layers) {
        if(layer->boundingRect().width() > max_width)
            max_width = layer->boundingRect().width();
    }
    max_width *= wider_than_children;
    if(max_width == 0) {
        max_width = DesignerHelper::getDefaultMultiLayerWidth();
    }

    m_rect.setWidth(max_width);
    update();

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


//! Returns line representing interface
QLineF MultiLayerView::getInterfaceLine(int row)
{
    if(row>=0 && row < m_interfaces.size()) {
        return m_interfaces[row];
    } else {
        return QLineF();
    }
}

void MultiLayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!checkDragEvent(event))
        QGraphicsItem::dragMoveEvent(event);
}


void MultiLayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (mimeData) {

        DesignerScene *designerScene = dynamic_cast<DesignerScene *>(scene());
        if(designerScene) {
            SampleModel *sampleModel = designerScene->getSampleModel();

            qDebug() << "\n XXX" << getDropArea(event->scenePos()) << event->scenePos();
            sampleModel->insertNewItem(
                        mimeData->getClassName(),
                        sampleModel->indexOfItem(this->getParameterizedItem()),
                        getDropArea(event->pos())
                        );
        }
    }
}


const DesignerMimeData *MultiLayerView::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }

    int row = getDropArea(event->pos());
    if(mimeData->hasFormat("bornagain/widget")
            && getParameterizedItem()->acceptsAsDefaultItem(mimeData->getClassName())
            && row!=-1 ) {

        qDebug() << "MultiLayerView::checkDragEvent -> yes"  << row << getDropAreaRectangle(row);
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
    return mimeData;
}

QVariant MultiLayerView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsItem::itemChange(change, value);
}

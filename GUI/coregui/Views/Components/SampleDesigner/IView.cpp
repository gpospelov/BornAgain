#include "IView.h"
#include "ParameterizedGraphicsItem.h"
#include "MaterialProperties.h"
#include <QString>
#include <QDebug>


IView::IView(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_item(0)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}


void IView::setParameterizedItem(ParameterizedItem *item)
{
    if(item) {
        m_item = item;
        setX(m_item->getRegisteredProperty(ParameterizedGraphicsItem::P_XPOS).toReal());
        setY(m_item->getRegisteredProperty(ParameterizedGraphicsItem::P_YPOS).toReal());
        connect(m_item, SIGNAL(propertyChanged(const QString &)), this, SLOT(onPropertyChange(const QString &)));
    }
}


void IView::addView(IView *childView, int row)
{
    qDebug() << "IView::addView() " << m_item->itemName() << childView->getParameterizedItem()->itemName() << " row:" << row;
}


void IView::onChangedX()
{
    Q_ASSERT(m_item);
    m_item->setRegisteredProperty(ParameterizedGraphicsItem::P_XPOS, x());
}


void IView::onChangedY()
{
    Q_ASSERT(m_item);
    m_item->setRegisteredProperty(ParameterizedGraphicsItem::P_YPOS, y());
}


void IView::onPropertyChange(const QString &propertyName)
{
    if(propertyName == ParameterizedGraphicsItem::P_XPOS) {
        setX(m_item->getRegisteredProperty(ParameterizedGraphicsItem::P_XPOS).toReal());
    } else if(propertyName == ParameterizedGraphicsItem::P_YPOS) {
        setY(m_item->getRegisteredProperty(ParameterizedGraphicsItem::P_YPOS).toReal());
    }
}



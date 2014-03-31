#include "IView.h"
#include "ParameterizedGraphicsItem.h"
#include <QDebug>




IView::IView(QGraphicsItem *parent)
    : QGraphicsObject(parent), m_item(0)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}


void IView::setSessionItem(ParameterizedItem *item)
{
    if(item) {
        m_item = item;
    }
}


void IView::onChangedX()
{
    Q_ASSERT(m_item);
    Q_ASSERT(m_item->property("xpos").isValid());
    m_item->setProperty("xpos", x());
}


void IView::onChangedY()
{
    Q_ASSERT(m_item);
    Q_ASSERT(m_item->property("ypos").isValid());
    m_item->setProperty("ypos", y());
}

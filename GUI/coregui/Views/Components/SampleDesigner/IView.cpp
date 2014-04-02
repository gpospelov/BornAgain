#include "IView.h"
#include "ParameterizedGraphicsItem.h"
#include <QString>
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
        Q_ASSERT(m_item->property("xpos").isValid());
        Q_ASSERT(m_item->property("ypos").isValid());
        setX(m_item->property("xpos").toReal());
        setY(m_item->property("ypos").toReal());
        connect(m_item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChange(QString)));
    }
}


void IView::addView(IView *childView, int row)
{
    qDebug() << "IView::addView() " << m_item->itemName() << childView->getSessionItem()->itemName() << " row:" << row;
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


void IView::onPropertyChange(QString propertyName)
{
    if(propertyName == QStringLiteral("xpos")) {
        setX(m_item->property("xpos").toReal());
    } else if(propertyName == QStringLiteral("ypos")) {
        setY(m_item->property("ypos").toReal());
    }
}



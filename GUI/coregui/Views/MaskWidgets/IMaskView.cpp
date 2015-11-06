// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/IMaskView.h
//! @brief     Implements interface class IMaskView for all masks on graphics scene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMaskView.h"
#include "ParameterizedItem.h"
#include "ISceneAdaptor.h"
#include <QDebug>

IMaskView::IMaskView()
    : m_item(0)
    , m_adaptor(0)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

QRectF IMaskView::boundingRect() const
{
    return m_bounding_rect;
}

void IMaskView::setParameterizedItem(ParameterizedItem *item)
{
    if(m_item != item) {
        if(m_item) {
            disconnect(m_item, SIGNAL(propertyChanged(const QString &)), this,
                    SLOT(onPropertyChange(const QString &)));
            disconnect(m_item, SIGNAL(subItemChanged(const QString &)), this,
                    SLOT(onPropertyChange(const QString &)));

        }

        m_item = item;

        if(m_item) {
            connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
                    SLOT(onPropertyChange(const QString &)));
            connect(m_item, SIGNAL(subItemChanged(const QString &)), this,
                    SLOT(onPropertyChange(const QString &)));
        }
    }
    update_view();
}

ParameterizedItem *IMaskView::getParameterizedItem()
{
    return m_item;
}

void IMaskView::setSceneAdaptor(ISceneAdaptor *adaptor)
{
    qDebug() << "BBB";
    qDebug() << "BBB";
    qDebug() << "IMaskView::setSceneAdaptor()-> setting adapter";
    m_adaptor = adaptor;
    connect(m_adaptor, SIGNAL(update_request()), this, SLOT(update_view()));
    update_view();
}

double IMaskView::par(const QString &property_name) const
{
    return m_item->getRegisteredProperty(property_name).toReal();
}

qreal IMaskView::toSceneX(const QString &property_name) const
{
    Q_ASSERT(m_item);
    qreal result = toSceneX(m_item->getRegisteredProperty(property_name).toReal());
    qDebug() << "IMaskView::toSceneX:" << property_name
             << "propertyValue" << m_item->getRegisteredProperty(property_name).toReal()
             << " toSceneX:" << result;
    return result;
}

qreal IMaskView::toSceneX(qreal value) const
{
    qreal result = value;
    if(m_adaptor) result = m_adaptor->toSceneX(result);
    return result;
}

qreal IMaskView::toSceneY(const QString &property_name) const
{
    Q_ASSERT(m_item);
    qreal result = toSceneY(m_item->getRegisteredProperty(property_name).toReal());
    qDebug() << "IMaskView::toSceneY:" << property_name
             << "propertyValue" << m_item->getRegisteredProperty(property_name).toReal()
             << " toSceneY:" << result;
    return result;
}

qreal IMaskView::toSceneY(qreal value) const
{
    qreal result = value;
    if(m_adaptor) result = m_adaptor->toSceneY(result);
    return result;
}

qreal IMaskView::fromSceneX(qreal value) const
{
    qreal result = value;
    if(m_adaptor) result = m_adaptor->fromSceneX(value);
    return result;
}

qreal IMaskView::fromSceneY(qreal value) const
{
    qreal result = value;
    if(m_adaptor) result = m_adaptor->fromSceneY(value);
    return result;
}

void IMaskView::onChangedX()
{

}

void IMaskView::onChangedY()
{

}

void IMaskView::onPropertyChange(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}

//void IMaskView::update_view()
//{
//    qDebug() << ">>>> IMaskView::update_view() -> ";
//    update_bounding_rect();
//    update();
//}



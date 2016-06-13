// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/IMaskView.cpp
//! @brief     Implements interface class IMaskView for all masks on graphics scene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IMaskView.h"
#include "SessionItem.h"
#include "ISceneAdaptor.h"
#include "MaskItems.h"
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

IMaskView::IMaskView()
    : m_item(0)
    , m_adaptor(0)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

IMaskView::~IMaskView()
{
    if(m_item)
        m_item->mapper()->unsubscribe(this);
}

QRectF IMaskView::boundingRect() const
{
    return m_bounding_rect;
}

void IMaskView::setParameterizedItem(SessionItem *item)
{
    if(m_item == item) {
        return;

    } else {
        if(m_item)
            m_item->mapper()->unsubscribe(this);

        m_item = item;
        if(!m_item) return;

        m_item->mapper()->setOnPropertyChange(
                    [this](const QString &name)
        {
            onPropertyChange(name);
        }, this);
    }
}

SessionItem *IMaskView::getParameterizedItem()
{
    return m_item;
}

const ISceneAdaptor *IMaskView::getAdaptor()
{
    return m_adaptor;
}

void IMaskView::setSceneAdaptor(const ISceneAdaptor *adaptor)
{
    Q_ASSERT(adaptor);

    if(m_adaptor != adaptor) {
        if(m_adaptor) {
            disconnect(m_adaptor, SIGNAL(update_request()), this, SLOT(update_view()));
        }

        m_adaptor = adaptor;
        connect(m_adaptor, SIGNAL(update_request()), this,
                SLOT(update_view()), Qt::UniqueConnection);
        update_view();
    }
}

double IMaskView::par(const QString &property_name) const
{
    return m_item->getItemValue(property_name).toReal();
}

qreal IMaskView::toSceneX(const QString &property_name) const
{
    return toSceneX(m_item->getItemValue(property_name).toReal());
}

qreal IMaskView::toSceneX(qreal value) const
{
    qreal result = value;
    if(m_adaptor) result = m_adaptor->toSceneX(result);
    return result;
}

qreal IMaskView::toSceneY(const QString &property_name) const
{
    return toSceneY(m_item->getItemValue(property_name).toReal());
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

void IMaskView::addView(IMaskView *childView, int row)
{
    Q_UNUSED(row);
    if(childItems().contains(childView)) return;
    childView->setParentItem(this);
}

void IMaskView::onChangedX()
{
}

void IMaskView::onChangedY()
{
}

void IMaskView::onPropertyChange(const QString &propertyName)
{
    qDebug() << "IMaskView::onPropertyChange ->" << propertyName;
    if(propertyName == MaskItem::P_MASK_VALUE) {
        update();
    }

    emit propertyChanged();
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/IView.cpp
//! @brief     Implements class IView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IView.h"
#include "SessionGraphicsItem.h"
#include "ModelMapper.h"
#include <QString>
#include <QDebug>

IView::IView(QGraphicsItem *parent) : QGraphicsObject(parent), m_item(0)
{
    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
}

void IView::setParameterizedItem(SessionItem *item)
{
    if (item) {
        m_item = item;
        setX(m_item->getChildValue(SessionGraphicsItem::P_XPOS).toReal());
        setY(m_item->getChildValue(SessionGraphicsItem::P_YPOS).toReal());
        ModelMapper *mapper = new ModelMapper(this);
        mapper->setItem(item);
        mapper->setOnPropertyChange(
                    [this] (const QString &name)
        {
            if (name == SessionGraphicsItem::P_XPOS) {
                setX(m_item->getChildValue(SessionGraphicsItem::P_XPOS).toReal());
            } else if (name == SessionGraphicsItem::P_YPOS) {
                setY(m_item->getChildValue(SessionGraphicsItem::P_YPOS).toReal());
            }
        });
        connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
                SLOT(onPropertyChange(const QString &)));
        connect(m_item, SIGNAL(subItemChanged(const QString &)), this,
                SLOT(onPropertyChange(const QString &)));
    }
}

void IView::addView(IView *childView, int row)
{
    qDebug() << "IView::addView() " << m_item->itemName()
             << childView->getParameterizedItem()->itemName() << " row:" << row;
}

void IView::onChangedX()
{
    Q_ASSERT(m_item);
    m_item->setChildValue(SessionGraphicsItem::P_XPOS, x());
}

void IView::onChangedY()
{
    Q_ASSERT(m_item);
    m_item->setChildValue(SessionGraphicsItem::P_YPOS, y());
}

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

IMaskView::IMaskView()
    : m_item(0)
    , m_adaptor(0)
{

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

}

ParameterizedItem *IMaskView::getParameterizedItem()
{
    return m_item;
}

void IMaskView::setSceneAdaptor(ISceneAdaptor *adaptor)
{
    m_adaptor = adaptor;
}

qreal IMaskView::toSceneX(const QString &property_name) const
{
    Q_ASSERT(m_item);
    qreal result = m_item->getRegisteredProperty(property_name).toReal();
    if(m_adaptor) result = m_adaptor->toSceneX(result);
    return result;
}

qreal IMaskView::toSceneY(const QString &property_name) const
{
    Q_ASSERT(m_item);
    qreal result = m_item->getRegisteredProperty(property_name).toReal();
    if(m_adaptor) result = m_adaptor->toSceneY(result);
    return result;
}

void IMaskView::onPropertyChange(const QString &propertyName)
{
    Q_UNUSED(propertyName);
}



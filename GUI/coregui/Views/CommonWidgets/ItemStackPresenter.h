// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/CommonWidgets/ItemStackPresenter.h
//! @brief     Declares class ItemStackPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMSTACKPRESENTER_H
#define ITEMSTACKPRESENTER_H

#include "ItemStackWidget.h"
#include <QStackedWidget>
#include <QMap>
#include <QDebug>

class SessionItem;

//! The ItemStackPresenter templated class extends ItemStackWidget so it could operate with
//! SesionItem editor's of specified type, while still keeping signal/slots alive.

template<class T>
class BA_CORE_API_ ItemStackPresenter : public ItemStackWidget
{
public:
    virtual void setItem(SessionItem *item) {
        T *widget = m_itemToWidget[item];

        if(!widget) {
            widget = new T();
            m_stackedWidget->addWidget(widget);
            m_itemToWidget[item] = widget;
            widget->setItem(item);
        }
        m_stackedWidget->setCurrentWidget(widget);
    }

protected:
    virtual void removeWidgetForItem(SessionItem *item) {
        Q_ASSERT(item);

        T *widget = m_itemToWidget[item];
        if(!widget) return;

        qDebug() << "ItemStackPresenter::removeWidgetForItem";

        typename QMap<SessionItem *, T *>::iterator it = m_itemToWidget.begin();
        while(it!=m_itemToWidget.end()) {
            if(it.value() == widget) {
                it = m_itemToWidget.erase(it);
            } else {
                ++it;
            }
        }

        m_stackedWidget->removeWidget(widget);
        delete widget;
    }

private:
    QMap<SessionItem *, T *> m_itemToWidget;
};


#endif

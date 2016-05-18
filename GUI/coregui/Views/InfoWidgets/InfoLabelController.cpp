// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoLabelController.cpp
//! @brief     Implements class InfoLabelController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InfoLabelController.h"
#include "InfoLabelWidget.h"
#include <QAbstractScrollArea>
#include <QEvent>
#include <QRect>
#include <QDebug>

InfoLabelController::InfoLabelController(QObject *parent)
    : QObject(parent)
    , m_label(0)
    , m_area(0)
{

}

void InfoLabelController::setText(const QString &text)
{
    m_text = text;
}

void InfoLabelController::setArea(QAbstractScrollArea *area)
{
    m_area = area;
    m_area->installEventFilter(this);
}

//! Shows/removes a label from the controlled widget

void InfoLabelController::setShown(bool shown)
{
    if(shown) {
        if(!m_label) {
            m_label = new InfoLabelWidget(m_area);
            m_label->setText(m_text);
            updateLabelGeometry();
        }

    } else {
        delete m_label;
        m_label = 0;
    }
}

bool InfoLabelController::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Resize) {
        qDebug() << "InfoLabelController::eventFilter" << m_area->viewport()->width() << m_area->viewport()->height();
//        widget()->setMaximumWidth(viewport()->width());
//        setMaximumHeight(height() - viewport()->height() + widget()->height());
        updateLabelGeometry();
    }

    return QObject::eventFilter(obj, event);
}

void InfoLabelController::updateLabelGeometry()
{
    if(!m_label || !m_area) return;
    qDebug() << "InfoLabelController::updateLabelGeometry()" << m_area->width(), m_area->height();
    m_label->setRectangle(QRect(0, 0, m_area->width(), m_area->height()));
    m_label->setPosition(0, 0);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/CustomEventFilters.cpp
//! @brief     Defines classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "CustomEventFilters.h"
#include <QEvent>
#include <QSpinBox>
#include <QComboBox>
#include <QKeyEvent>

SpaceKeyEater::SpaceKeyEater(QObject *parent)
    : QObject(parent)
{

}

bool SpaceKeyEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        bool res = QObject::eventFilter(obj, event);

        if (keyEvent->key() == Qt::Key_Space) {
            return true; /* Always accept space bar */
        } else {
            return res;
        }
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

// ----------------------------------------------------------------------------

WheelEventEater::WheelEventEater(QObject *parent)
    : QObject(parent)
{

}

bool WheelEventEater::eventFilter(QObject *obj, QEvent *event)
{
    if(QAbstractSpinBox* spinBox = qobject_cast<QAbstractSpinBox*>(obj)) {

        if(event->type() == QEvent::Wheel) {
            if(spinBox->focusPolicy() == Qt::WheelFocus) {
                event->accept();
                return false;
            } else {
                event->ignore();
                return true;
            }
        }
        else if(event->type() == QEvent::FocusIn) {
            spinBox->setFocusPolicy(Qt::WheelFocus);
        }
        else if(event->type() == QEvent::FocusOut) {
            spinBox->setFocusPolicy(Qt::StrongFocus);
        }
    }
    else if(qobject_cast<QComboBox*>(obj)) {
        if(event->type() == QEvent::Wheel) {
            event->ignore();
            return true;
        } else {
            event->accept();
            return false;
        }
    }
    return QObject::eventFilter(obj, event);
}

// ----------------------------------------------------------------------------

bool DeleteEventFilter::eventFilter( QObject *dist, QEvent *event )
{
    Q_UNUSED(dist);
    if( event->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>( event );
        if( keyEvent->key() == Qt::Key_Delete ) {
            emit removeItem();
        }
    }
    return QObject::eventFilter(dist, event);
}


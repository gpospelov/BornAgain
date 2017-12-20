// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/CustomEventFilters.cpp
//! @brief     Defines classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CustomEventFilters.h"
#include <QComboBox>
#include <QKeyEvent>
#include <QString>

SpaceKeyEater::SpaceKeyEater(QObject* parent) : QObject(parent) {}

bool SpaceKeyEater::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
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

WheelEventEater::WheelEventEater(QObject* parent) : QObject(parent) {}

bool WheelEventEater::eventFilter(QObject* obj, QEvent* event)
{
    if (QAbstractSpinBox* spinBox = qobject_cast<QAbstractSpinBox*>(obj)) {

        if (event->type() == QEvent::Wheel) {
            if (spinBox->focusPolicy() == Qt::WheelFocus) {
                event->accept();
                return false;
            } else {
                event->ignore();
                return true;
            }
        } else if (event->type() == QEvent::FocusIn) {
            spinBox->setFocusPolicy(Qt::WheelFocus);
        } else if (event->type() == QEvent::FocusOut) {
            spinBox->setFocusPolicy(Qt::StrongFocus);
        }
    } else if (qobject_cast<QComboBox*>(obj)) {
        if (event->type() == QEvent::Wheel) {
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

bool DeleteEventFilter::eventFilter(QObject* dist, QEvent* event)
{
    Q_UNUSED(dist);
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Delete)
            emit removeItem();
    }
    return QObject::eventFilter(dist, event);
}

// ----------------------------------------------------------------------------

LostFocusFilter::LostFocusFilter(QObject* parent) : QObject(parent) {}

bool LostFocusFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::FocusOut)
        return true;

    return QObject::eventFilter(obj, event);
}

// ----------------------------------------------------------------------------

ShortcodeFilter::ShortcodeFilter(const QString& shortcode, QObject* parent)
    : QObject(parent)
    , m_shortcode(shortcode)
    , m_index(0)
{

}

bool ShortcodeFilter::eventFilter(QObject* obj, QEvent* event)
{
    Q_UNUSED(obj);
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (m_shortcode.at(m_index) == keyEvent->text()) {
            m_index++;
            if (m_index == m_shortcode.length()) {
                emit found();
                m_index = 0;
            }
        } else {
            int right = m_index;
            while (m_index > 0) {
                if (m_shortcode.at(m_index - 1) == keyEvent->text()
                    && m_shortcode.left(m_index - 1)
                           == m_shortcode.mid(right - m_index + 1, m_index - 1))
                    break;
                m_index--;
            }
        }
    }
    return false;
}

RightMouseButtonEater::RightMouseButtonEater(QObject* parent)
    : QObject(parent)
{
}

bool RightMouseButtonEater::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::RightButton) {
            event->ignore();
            return true;
        } else {
            event->accept();
            return false;
        }
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

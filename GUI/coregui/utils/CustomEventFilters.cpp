// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/CustomEventFilters.cpp
//! @brief     Defines classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CustomEventFilters.h"
#include <QEvent>
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

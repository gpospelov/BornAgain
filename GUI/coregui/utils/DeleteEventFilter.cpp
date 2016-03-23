// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/DeleteEventFilter.cpp
//! @brief     Defines classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DeleteEventFilter.h"
#include <QEvent>
#include <QKeyEvent>

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

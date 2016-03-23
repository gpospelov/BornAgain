// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/DeleteEventFilter.cpp
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

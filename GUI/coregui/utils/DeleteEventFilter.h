// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/DeleteEventFilter.h
//! @brief     Declares classes releted to event filtering
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DELETEEVENTFILTERS_H
#define DELETEEVENTFILTERS_H

#include "WinDllMacros.h"
#include <QObject>

class QEvent;

//! Filter out space bar key events, which is special case for dialog windows

class DeleteEventFilter : public QObject
{
    Q_OBJECT
public:
  DeleteEventFilter( QObject *parent = 0 ) : QObject( parent ) {}

protected:
  bool eventFilter( QObject *dist, QEvent *event );

signals:
  void removeItem();
};

#endif

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/CustomEventFilters.h
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

#ifndef CUSTOMEVENTFILTERS_H
#define CUSTOMEVENTFILTERS_H

#include "WinDllMacros.h"
#include <QObject>

//! Filter out space bar key events, which is special case for dialog windows.

class BA_CORE_API_ SpaceKeyEater : public QObject
{
    Q_OBJECT
public:

    SpaceKeyEater(QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};


//! Event filter to install on combo boxes and spin boxes to not
//! to react on wheel events during scrolling of InstrumentComponentWidget.

class BA_CORE_API_ WheelEventEater : public QObject
{
    Q_OBJECT
public:

    WheelEventEater(QObject *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

//! Lisens for press-del-key events

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



#endif // CUSTOMEVENTFILTERS_H
